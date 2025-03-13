#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>

using namespace std;

char board[8][8];

void initialize();

int main() {
    initialize();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    // initialize
    // board[3][2]
    return 0;
}

void initialize() {
    for (int i = 0; i < 8; i++) {
        board[i] = {'0'};
    }
    board[3][2] = 'w';
    board[3][3] = 'b';
    board[4][2] = 'b';
    board[4][3] = 'w';
}