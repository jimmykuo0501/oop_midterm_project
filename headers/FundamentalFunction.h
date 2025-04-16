//
// Created by Miller on 2025/3/31.
//

#ifndef FUNDAMENTALFUNCTION_H
#define FUNDAMENTALFUNCTION_H

#include <vector>
#include <iostream>
#include <fstream>

#define BOARDLENGTH 8

using namespace std;

class FundamentalFunction {
public:

    FundamentalFunction();

    char board[BOARDLENGTH][BOARDLENGTH]{};

    char** getBoard() {
        // let board -> char** (strictly)
        return reinterpret_cast<char**>(board);
    }

    // Initialize the board
    void initialize();

    // Show all place that user can take
    void showPlayPlace(bool);

    // Consider whether the step is available.
    void dedect(int xPos, int yPos, int moveX, int moveY, bool isWhiteTurn);

    // output the checkerboard in current time.
    void display() const;

    /*get x and y position, chess color and according to rule of black white chess to turn
      over the other color chess in each line.*/
    void turnOver(int, int, bool);

    static bool checkWin(bool);

    std::pair<int, int> AIPlayChess();

private:
    int targetX{};
    int targetY{};
};


#endif //FUNDAMENTALFUNCTION_H
