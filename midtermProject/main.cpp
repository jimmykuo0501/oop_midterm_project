#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

char board[8][8];

/**
 * Initialize the board
 *
 */
void initialize();

/**
 *  Show all place that user can take
 * \param isWhiteTurn. Who should play next (true is white turn, false is black turn)
 */
void showPlayPlace(bool);

/**
 * Consider whether the step is available.
 * \param x posititon, y position, delta x, delta y, whose turn.
 */
void dedect(int, int, int, int, bool);

int main() {
    initialize();
    for (auto &i: board) {
        for (char j: i) {
            cout << j << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    showPlayPlace(true);
    for (auto &i: board) {
        for (char j: i) {
            cout << j << " ";
        }
        cout << '\n';
    }
    return 0;
}

void initialize() {
    for (auto &i: board) {
        for (char &j: i) {
            j = {'s'};
        }
    }
    board[3][3] = 'w';
    board[3][4] = 'b';
    board[4][3] = 'b';
    board[4][4] = 'w';
}

void showPlayPlace(const bool isWhiteTurn) {
    // a mean available place
    const vector<vector<int> > dedection = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

    int locate = 0;
    while (locate < 64) {
        const int xPos = locate % 8;
        const int yPos = locate / 8;
        if (board[xPos][yPos] == 'w') {
            for (const vector<int> &dir : dedection) {
                dedect(xPos, yPos, dir[0], dir[1], isWhiteTurn);
            }
        }
        locate++;
    }
}

void dedect(int xPos, int yPos, const int moveX, const int moveY, const bool isWhiteTurn) {
    bool found = false;
    if (isWhiteTurn) {
        while (true) {
            xPos += moveX;
            yPos += moveY;
            if (xPos < 0 || xPos > 7 || yPos < 0 || yPos > 7) {
                break;
            } else if (board[yPos][xPos] == 'b') {
                found = true;
            } else if (board[yPos][xPos] == 's' && found) {
                board[yPos][xPos] = 'a';
                break;
            } else {
                break;
            }
        }
    } else {
        while (true) {
            xPos += moveX;
            yPos += moveY;
            if (board[yPos][xPos] == 'w') {
                found = true;
            } else if (board[yPos][xPos] == 's' && found) {
                board[yPos][xPos] = 'a';
            } else {
                break;
            }
        }
    }
}
