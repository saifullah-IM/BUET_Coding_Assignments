package sample;

import java.util.ArrayList;

public class Game {
    private final int boardSize;
    private final int[] dx = {0,0,1,-1};
    private final int[] dy = {-1,1,0,0};
    private final int[] fx = {-1,-1,1,1,0};
    private final int[] fy = {-1,1,-1,1,0};
    private ArrayList<Double> probabilities = new ArrayList<Double>();

    public Game (int boardSize) {
        this.boardSize = boardSize;
        double init_prob = 1.0 / (boardSize * boardSize * 1.0);
        for (int i = 0; i < boardSize * boardSize; i++) probabilities.add(init_prob);
    }

    private void normalize () {
        double sum = 0.0;
        for (int i = 0; i < boardSize * boardSize; i++) sum += probabilities.get(i);
        for (int i = 0; i < boardSize * boardSize; i++) {
            probabilities.set(i, probabilities.get(i) / sum);
        }
    }

    public void updateProbabilities () {
        for (int i = 0; i < boardSize * boardSize; i++) {
            int x = i % boardSize;
            int y = i / boardSize;
            double probability = 0.0;
            for (int j = 0; j < 4; j++) {
                int _x = x + dx[j];
                int _y = y + dy[j];
                if (_x >= 0 && _x < boardSize && _y >= 0 && _y < boardSize) {
                    probability += (25.0 / 110.0) * probabilities.get(_y * boardSize + _x);
                }
            }
            for (int j = 0; j < 5; j++) {
                int _x = x + fx[j];
                int _y = y + fy[j];
                if (_x >= 0 && _x < boardSize && _y >= 0 && _y < boardSize) {
                    probability += (2.0 / 110.0) * probabilities.get(_y * boardSize + _x);
                }
            }
            probabilities.set(i, probability);
        }
        normalize();
    }

    public void updateProbabilities (int revealedPosition, int color) {
        int mid1 = (2 * boardSize) / 3;
        int mid2 = 2 * mid1;
        int reveal_x = revealedPosition % boardSize;
        int reveal_y = revealedPosition / boardSize;
        for (int i = 0; i < boardSize * boardSize; i++) {
            int temp_x = i % boardSize;
            int temp_y = i / boardSize;
            int dist = Math.abs(temp_x - reveal_x) + Math.abs(temp_y - reveal_y);
            if (dist <= mid1) {
                if (color != 1) probabilities.set(i, 0.0);
            }
            else if (dist <= mid2) {
                if (color != 2) probabilities.set(i, 0.0);
            }
            else if (color != 3) probabilities.set(i, 0.0);
        }
        normalize();
    }

    public ArrayList<Double> getProbabilities () {return probabilities;}
}
