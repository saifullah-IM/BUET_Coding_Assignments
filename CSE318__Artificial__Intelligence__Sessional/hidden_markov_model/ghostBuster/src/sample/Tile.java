package sample;

import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Tile extends Rectangle {
    String[] colors = new String[10];
    public Tile (int color, int x, int y) {
        colors[0] = "FFFFCC"; // default
        colors[1] = "FF0000"; // red
        colors[2] = "FF8000"; // orange
        colors[3] = "00FF00"; // green
        colors[4] = "FFFF00"; // yellow -- means selected
        colors[5] = "0000CC"; // blue -- where ghost is

        setWidth(Main.tile_width);
        setHeight(Main.tile_height);
        setStroke(Color.BLACK);
        setStrokeWidth(2.5);
        relocate(x * Main.tile_width, y * Main.tile_height);
        setColor(color);
    }

    public void setColor(int color) {
        setFill(Color.valueOf(colors[color]));
    }
}
