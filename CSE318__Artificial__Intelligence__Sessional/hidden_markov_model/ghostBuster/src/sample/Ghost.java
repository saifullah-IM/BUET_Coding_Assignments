package sample;

import java.util.Random;

public class Ghost {

    private int x;
    private int y;
    private final int boardSize;
    private final int[] dx = {0,0,1,-1};
    private final int[] dy = {-1,1,0,0};
    private final int[] fx = {-1,-1,1,1,0};
    private final int[] fy = {-1,1,-1,1,0};
    Random random;

    public Ghost(int boardSize) {
        this.boardSize = boardSize;
        random = new Random();
        int var = random.nextInt(boardSize * boardSize);
        x = var % boardSize;
        y = var / boardSize;
    }

    public void nextStep() {
        while (true) {
            int var = random.nextInt(110);
            int _x, _y;
            if (var < 100) {
                _x = x + dx[var % 4];
                _y = y + dy[var % 4];
            }
            else {
                _x = x + fx[var % 5];
                _y = y + fy[var % 5];
            }
            if (_x >= 0 && _x < boardSize && _y >= 0 && _y < boardSize) {
                x = _x;
                y = _y;
                break;
            }
        }
    }

    public int getPosition () {return y * boardSize + x;}
    public int getColor (int revealedPosition) {
        int mid1 = (2 * boardSize) / 3;
        int mid2 = 2 * mid1;
        int reveal_x = revealedPosition % boardSize;
        int reveal_y = revealedPosition % boardSize;
        int dist = Math.abs(x - reveal_x) + Math.abs(y - reveal_y);
        if (dist <= mid1) return 1;
        else if (dist <= mid2) return 2;
        else return 3;
    }
}
