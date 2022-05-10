package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.layout.GridPane;

import java.util.ArrayList;

public class Main extends Application {

    private Stage window;
    public int ghostCount = 1;
    public int boardSize = 9;
    public static int tile_height = 75;
    public static int tile_width = 120;
    private Game game;
    private Ghost ghost;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        window = primaryStage;
        window.setTitle("GhostBuster");

        Scene initialScene = getInitialScene();

        window.setScene(initialScene);
        window.show();
    }

    public Scene getInitialScene() {
        GridPane grid = new GridPane();
        grid.setPadding(new Insets(10, 10, 10, 10));
        grid.setVgap(8);
        grid.setHgap(10);

        Label ghostLabel = new Label("Number of Ghosts (between 1 and 3)");
        GridPane.setConstraints(ghostLabel, 0, 0);

        TextField ghostInput = new TextField("1");
        GridPane.setConstraints(ghostInput, 1, 0);

        Label boardLabel = new Label("Board Size (between 9 and 16)");
        GridPane.setConstraints(boardLabel, 0, 1);

        TextField boardInput = new TextField("9");
        GridPane.setConstraints(boardInput, 1, 1);

        Button startButton = new Button("Start Game");
        startButton.setOnAction(e -> getInput(ghostInput, boardInput));
        GridPane.setConstraints(startButton, 1, 2);

        grid.getChildren().addAll(ghostLabel, ghostInput, boardLabel, boardInput, startButton);

        return new Scene(grid, 400, 250);
    }

    private void getInput (TextField ghostInput, TextField boardInput) {
        int correctCount = 0;

        try {
            ghostCount = Integer.parseInt(ghostInput.getText());
            System.out.println("GhostCount " + ghostCount);
            if (ghostCount <= 3) correctCount++;
        } catch (NumberFormatException e) {
            System.out.println("Error getting ghost count" + ghostInput.getText());
        }

        try {
            boardSize = Integer.parseInt(boardInput.getText());
            System.out.println("BoardSize " + boardSize);
            if (boardSize <= 16) correctCount++;
        } catch (NumberFormatException e) {
            System.out.println("Error getting board size" + boardInput.getText());
        }

        if (correctCount == 2) {
            System.out.println("Going to game window");
            tile_height = (int) Math.floor(700.0 / (boardSize * 1.0));
            tile_width = (int) Math.floor(1100.0 / (boardSize * 1.0));
            ghost = new Ghost(boardSize);
            game = new Game(boardSize);
            window.setScene(getGameScene());
        }
        else {
            System.out.println("Please, enter integer values following the constraints.");
            showAlert("Wrong Input!", "Please, enter integer values following the constraints.");
        }
    }

    public void showAlert(String title, String message) {
        Stage alertWindow = new Stage();

        alertWindow.initModality(Modality.APPLICATION_MODAL);
        alertWindow.setTitle(title);
        alertWindow.setMinWidth(350);

        Label label = new Label();
        label.setText(message);
        Button closeButton = new Button("Ok");
        closeButton.setOnAction(e -> alertWindow.close());

        VBox layout = new VBox(10);
        layout.getChildren().addAll(label, closeButton);
        layout.setAlignment(Pos.CENTER);

        Scene scene = new Scene(layout);
        alertWindow.setScene(scene);
        alertWindow.showAndWait();
    }

    private ArrayList<Tile> tiles = new ArrayList<Tile>();
    private ArrayList<Text> texts = new ArrayList<Text>();
    private Group tileGroup = new Group();
    private Group textGroup = new Group();

    public Scene getGameScene () {
        Pane root = new Pane();
        root.setPrefSize(boardSize * tile_width + 150, boardSize * tile_height + 10);
        root.getChildren().add(tileGroup);
        root.getChildren().add(textGroup);

        for (int y = 0; y < boardSize; y++) {
            for (int x = 0; x < boardSize; x++) {
                Tile tile = new Tile(0, x, y);
                tiles.add(tile);
                final int _x = x;
                final int _y = y;
                tile.setOnMouseClicked(e -> selectTile(_y * boardSize + _x));
                tileGroup.getChildren().add(tile);
            }
        }

        double init_prob = 1.0 / (boardSize * boardSize * 1.0);
        for (int y = 0; y < boardSize; y++) {
            for (int x = 0; x < boardSize; x++) {
                Text text = new Text(String.format("%.6f", init_prob));
                text.relocate(x * tile_width + 10, y * tile_height + (tile_height * 1.0) / 2.0);
                texts.add(text);
                final int _x = x;
                final int _y = y;
                text.setOnMouseClicked(e -> selectTile(_y * boardSize + _x));
                textGroup.getChildren().add(text);
            }
        }

        Button nextButton = new Button("Next TimeStamp");
        nextButton.relocate(1120, 200);
        nextButton.setOnAction(e -> nextStep());

        Button revealButton = new Button("Reveal");
        revealButton.relocate(1120, 350);
        revealButton.setOnAction(e -> revealHandle());

        Button catchButton = new Button("Catch");
        catchButton.relocate(1120, 500);
        catchButton.setOnAction(e -> catchHandle());

        root.getChildren().addAll(nextButton, revealButton, catchButton);
        return new Scene(root);
    }

    private int selectedTileNumber = -1;
    private void selectTile (int tileNumber) {
        if (selectedTileNumber != -1) {
            tiles.get(selectedTileNumber).setColor(0);
        }
        selectedTileNumber = tileNumber;
        tiles.get(selectedTileNumber).setColor(4);
    }

    public void changeValue(int tileNumber, double value) {
        texts.get(tileNumber).setText(String.format("%.6f", value));
    }

    private void nextStep() {
        if (selectedTileNumber != -1) {
            tiles.get(selectedTileNumber).setColor(0);
            selectedTileNumber = -1;
        }
        ghost.nextStep();
        game.updateProbabilities();
        ArrayList<Double> probabilities = game.getProbabilities();
        for (int i = 0; i < boardSize * boardSize; i++) changeValue(i, probabilities.get(i));
    }

    private void revealHandle () {
        if (selectedTileNumber == -1) {
            showAlert("None selected!", "Please, select a position first!");
            return;
        }
        int color = ghost.getColor(selectedTileNumber);
        tiles.get(selectedTileNumber).setColor(color);
        game.updateProbabilities(selectedTileNumber, color);
        ArrayList<Double> probabilities = game.getProbabilities();
        for (int i = 0; i < boardSize * boardSize; i++) changeValue(i, probabilities.get(i));
    }

    private void catchHandle () {
        if (selectedTileNumber == -1) {
            showAlert("None selected!", "Please, select a position first!");
            return;
        }
        int ghostPosition = ghost.getPosition();
        tiles.get(ghostPosition).setColor(5);
        for (int i = 0; i < boardSize * boardSize; i++) {
            if (i == ghostPosition) changeValue(i, 1.0);
            else changeValue(i, 0.0);
        }
        if (ghostPosition == selectedTileNumber) {
            showAlert("Congratulations!", "You found the ghost!");
        }
        else {
            showAlert("Sorry!", "You failed to find the ghost!");
        }
    }
}
