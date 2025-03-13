/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author Cheng-Jui,Kuo. (B11115063), 
 * \date   2025/3/14~
 *********************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

char board[8][8];

// Initialize the board
void initialize();

// Show all place that user can take
void showPlayPlace(bool);

// Consider whether the step is available.
void dedect(int, int, int, int, bool);

// output the checkerboard in current time.
void display();

/*get x and y position, chess color and according to rule of black white chess to turn 
  over the other color chess in each line.*/
void turnOver(int ,int ,bool);

int main() {
    initialize();
    display();
    cout << endl;
    showPlayPlace(true);
    display();

    // demo
    int row = 3, col = 0;
    turnOver(col, row, false);
    display();
    return 0;
}

/**
 * Initialize the board
 * This function haven't any input and return value.
 */
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

/**
 *  Show all place that user can take
 * \param isWhiteTurn. Who should play next (true is white turn, false is black turn)
 */
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

/**
 * Consider whether the step is available.
 * \param x posititon, y position, delta x, delta y, whose turn.
 */
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

/**
 * display function: output the checkerboard in current time.
 * This function haven't any input and return value.
 */
void display()
{
    cout << "-----------------\n";

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "|";

            if (board[i][j] == 's')
            {
                cout << " ";
            }
            else if (board[i][j] == 'w')
            {
                cout << "¡³";
            }
            else if (board[i][j] == 'b')
            {
                cout << "¡´";
            }
            else if (board[i][j] == 'a')
            {
                cout << "¡·";
            }
        }

        cout << "|\n-----------------\n";
    }
}

/**
 *  get x and y position, chess color and according to rule of black white chess to turn 
 *  over the other color chess in each line.
 * 
 * \param xPos, this variable is to get chess x position.
 * \param yPos, this variable is to get chess y position.
 * \param isWhiteTurn, this variable is to check this chess color.
 */
void turnOver(int xPos, int yPos, bool isWhiteTurn)
{
    // searching centered on the white chess.
    if (isWhiteTurn)
    {
        // find the line of following eligible from the eight direstion of current chess.
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (board[yPos + i][xPos + j] == 'b')
                {
                    int findPointx=j, findPointy=i;
                    int findLine=0;

                    // search one by one to find the chess is eligibility.
                    while (board[yPos + findPointy][xPos + findPointx] == 'b')
                    {
                        findPointx += j;
                        findPointy += i;

                        if (board[yPos + findPointy][xPos + findPointx] == 's')
                        {
                            findLine = 0;
                            break;
                        }

                        if (board[yPos + findPointy][xPos + findPointx] == 'w')
                        {
                            findLine = 1;
                            break;
                        }
                    }

                    // turn over the black chess between two white chess in one line.
                    if (findLine)
                    {
                        int minTurnOverI, maxTurnOverI, minTurnOverJ, maxTurnOverJ;
                        if ((yPos + i) >= (yPos + findPointy))
                        {
                            maxTurnOverI = yPos + i;
                            minTurnOverI = yPos + findPointy;
                        }
                        else {
                            maxTurnOverI = yPos + findPointy;
                            minTurnOverI = yPos + i;
                        }
                        if ((xPos + j) >= (xPos + findPointx))
                        {
                            maxTurnOverJ = xPos + j;
                            minTurnOverJ = xPos + findPointx;
                        }
                        else {
                            maxTurnOverJ = xPos + findPointx;
                            minTurnOverJ = xPos + j;
                        }

                        for (int turnOverI = minTurnOverI; turnOverI <= maxTurnOverI; turnOverI++)
                        {
                            for (int turnOverJ = minTurnOverJ; turnOverJ <= maxTurnOverJ; turnOverJ++)
                            {
                                board[turnOverI][turnOverJ] = 'w';
                            }
                        }

                        board[yPos][xPos] = 'w';
                    }
                }
            }
        }
    }
    // searching centered on the black chess.
    else {
        // find the line of following eligible from the eight direstion of current chess.
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (board[yPos + i][xPos + j] == 'w')
                {
                    int findPointx = j, findPointy = i;
                    int findLine = 0;

                    // search one by one to find the chess is eligibility.
                    while (board[yPos + findPointy][xPos + findPointx] == 'w')
                    {

                        findPointx += j;
                        findPointy += i;

                        if (board[yPos + findPointy][xPos + findPointx] == 's')
                        {
                            findLine = 0;
                            break;
                        }

                        if (board[yPos + findPointy][xPos + findPointx] == 'b')
                        {
                            findLine = 1;
                            break;
                        }
                    }

                    // turn over the white chess between two black chess in one line.
                    if (findLine)
                    {
                        int minTurnOverI, maxTurnOverI, minTurnOverJ, maxTurnOverJ;
                        if ((yPos + i) >= (yPos + findPointy))
                        {
                            maxTurnOverI = yPos + i;
                            minTurnOverI = yPos + findPointy;
                        }
                        else {
                            maxTurnOverI = yPos + findPointy;
                            minTurnOverI = yPos + i;
                        }
                        if ((xPos + j) >= (xPos + findPointx))
                        {
                            maxTurnOverJ = xPos + j;
                            minTurnOverJ = xPos + findPointx;
                        }
                        else {
                            maxTurnOverJ = xPos + findPointx;
                            minTurnOverJ = xPos + j;
                        }

                        for (int turnOverI = minTurnOverI; turnOverI <= maxTurnOverI; turnOverI++)
                        {
                            for (int turnOverJ = minTurnOverJ; turnOverJ <= maxTurnOverJ; turnOverJ++)
                            {
                                board[turnOverI][turnOverJ] = 'b';
                            }
                        }

                        board[yPos][xPos] = 'b';
                    }
                }
            }
        }
    }
}
