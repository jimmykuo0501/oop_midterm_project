//
// Created by Miller on 2025/3/31.
//

#include "../headers/FundamentalFunction.h"

#include <algorithm>

FundamentalFunction::FundamentalFunction() = default;

/**
 * Initialize the board
 * This function haven't any input and return value.
 */
void FundamentalFunction::initialize() {
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
 * @param isWhiteTurn. Who should play next (true is white turn, false is black turn)
 */
void FundamentalFunction::showPlayPlace(const bool isWhiteTurn) {
    // a mean available place
    const vector<vector<int> > directions = {
        {-1, -1}, {0, -1}, {1, -1}, {1, 0},
        {1, 1}, {0, 1}, {-1, 1}, {-1, 0}
    };

    // change available point back to 's'
    for (auto &i: board) {
        for (char &j: i) {
            if (j == 'a') {
                j = 's';
            }
        }
    }

    // Loop through all cells on the board
    for (int y = 0; y < BOARDLENGTH; y++) {
        for (int x = 0; x < BOARDLENGTH; x++) {
            // If the current player is white (isWhiteTurn == true), look from white pieces
            // If the current player is black (isWhiteTurn == false), look from black pieces
            char targetPiece = isWhiteTurn ? 'w' : 'b';

            // Only check from pieces of the current player's color
            if (board[y][x] == targetPiece) {
                // Check in all 8 directions
                for (const vector<int> &dir: directions) {
                    dedect(x, y, dir[0], dir[1], isWhiteTurn);
                }
            }
        }
    }
}

/**
 * Consider whether the step is available.
 * \param xPos, yPos, moveX, moveY, whose turn.
 */
void FundamentalFunction::dedect(int xPos, int yPos, const int moveX, const int moveY, const bool isWhiteTurn) {
    bool found = false;
    int newX = xPos;
    int newY = yPos;

    if (isWhiteTurn) {
        while (true) {
            newX += moveX;
            newY += moveY;

            if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
                break;
            }
            if (board[newY][newX] == 'b') {
                found = true;
            } else if (board[newY][newX] == 's' && found) {
                board[newY][newX] = 'a';
                break;
            } else {
                break;
            }
        }
    } else {
        while (true) {
            newX += moveX;
            newY += moveY;

            if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
                break;
            }
            if (board[newY][newX] == 'w') {
                found = true;
            } else if (board[newY][newX] == 's' && found) {
                board[newY][newX] = 'a';
                break;
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
void FundamentalFunction::display() const {
    cout << "-----------------\n";

    for (auto i: board) {
        for (int j = 0; j < 8; j++) {
            cout << "|";

            if (i[j] == 's') {
                cout << " ";
            } else if (i[j] == 'w') {
                cout << "W";
            } else if (i[j] == 'b') {
                cout << "B";
            } else if (i[j] == 'a') {
                cout << "A";
            }
        }

        cout << "|\n-----------------\n";
    }
}

/**
 *  get x and y position, chess color and according to rule of black white chess to turn
 *  over the other color chess in each line.
 *
 * \param xPos this variable is to get chess x position.
 * \param yPos this variable is to get chess y position.
 * \param isWhiteTurn this variable is to check this chess color.
 */


void FundamentalFunction::turnOver(int xPos, int yPos, bool isWhiteTurn) {
    //cout << "*" << board[yPos][xPos] << endl;
    // searching centered on the white chess.
    if (isWhiteTurn) {
        // find the line of following eligible from the eight direstion of current chess.
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((yPos + i) >= 0 && (yPos + i) < 8 && (xPos + j) >= 0 && (xPos + j) < 8) {
                    if (board[yPos + i][xPos + j] == 'b') {
                        int findPointX = j, findPointY = i;
                        int findLine = 0;

                        // search one by one to find the chess is eligibility.
                        while (board[yPos + findPointY][xPos + findPointX] == 'b') {
                            findPointX += j;
                            findPointY += i;
                            if ((yPos + findPointY) < 0 || (yPos + findPointY) >= 8 || (xPos + findPointX) < 0 || (
                                    xPos + findPointX) >= 8) {
                                findLine = 0;
                                break;
                            }
                            if (board[yPos + findPointY][xPos + findPointX] == 's' || board[yPos + findPointY][
                                    xPos + findPointX] == 'a') {
                                findLine = 0;
                                break;
                            }

                            if (board[yPos + findPointY][xPos + findPointX] == 'w') {
                                findLine = 1;
                                break;
                            }
                        }

                        // turn over the black chess between two white chess in one line.
                        if (findLine) {
                            int startPointY = yPos;
                            int startPointX = xPos;
                            while (startPointY != (yPos + findPointY) || startPointX != (xPos + findPointX)) {
                                board[startPointY][startPointX] = 'w';
                                startPointY += i;
                                startPointX += j;
                            }
                            board[yPos + findPointY][xPos + findPointX] = 'w';
                        }
                    }
                }
            }
        }
    }
    // searching centered on the black chess.
    else {
        // find the line of following eligible from the eight direstion of current chess.
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((yPos + i) >= 0 && (yPos + i) < 8 && (xPos + j) >= 0 && (xPos + j) < 8) {
                    if (board[yPos + i][xPos + j] == 'w') {
                        int findPointX = j, findPointY = i;
                        int findLine = 0;

                        // search one by one to find the chess is eligibility.
                        while (board[yPos + findPointY][xPos + findPointX] == 'w') {
                            findPointX += j;
                            findPointY += i;
                            if ((yPos + findPointY) < 0 || (yPos + findPointY) >= 8 || (xPos + findPointX) < 0 || (
                                    xPos + findPointX) >= 8) {
                                findLine = 0;
                                break;
                            }

                            if (board[yPos + findPointY][xPos + findPointX] == 's' || board[yPos + findPointY][
                                    xPos + findPointX] == 'a') {
                                findLine = 0;
                                break;
                            }

                            if (board[yPos + findPointY][xPos + findPointX] == 'b') {
                                findLine = 1;
                                break;
                            }
                        }

                        // turn over the black chess between two white chess in one line.
                        if (findLine) {
                            int startPointY = yPos;
                            int startPointX = xPos;
                            //cout << startPointX << " " << startPointY << " " << xPos + findPointX << " " << yPos + findPointY << endl;
                            while (startPointY != (yPos + findPointY) || startPointX != (xPos + findPointX)) {
                                board[startPointY][startPointX] = 'b';
                                startPointY += i;
                                startPointX += j;
                                //cout << startPointX << " " << startPointY << endl;
                            }
                            board[yPos + findPointY][xPos + findPointX] = 'b';
                        }
                    }
                }
            }
        }
    }
}

bool FundamentalFunction::checkWin(bool isWhiteTurn) {
    return true;
}

std::pair<int, int> FundamentalFunction::AIPlayChess() {
    /*
    showPlayPlace(true); // false = 白棋（AI）

    struct AIPlaySpace {
        int x;
        int y;
        int distanceWithEdge;
    };

    AIPlaySpace choose[64] = {-1};
    int chooseLength = 0;
    auto board = getBoard();

    // AI is White
    showPlayPlace(true);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 'a') {
                int minI = i;
                if ((8 - i) < minI) {
                    minI = (8 - i);
                }
                int minJ = j;
                if ((8 - j) < minJ) {
                    minJ = (8 - j);
                }
                if (minI < minJ) {
                    choose[chooseLength].distanceWithEdge = minI;
                } else {
                    choose[chooseLength].distanceWithEdge = minJ;
                }
                choose[chooseLength].x = i;
                choose[chooseLength].y = j;
                chooseLength++;
            }
        }
    }

    for (int i = 0; i < chooseLength; i++) {
        for (int j = 0; j < chooseLength; j++) {
            if (choose[i].distanceWithEdge > choose[j].distanceWithEdge) {
                int temp = choose[i].distanceWithEdge;
                choose[i].distanceWithEdge = choose[j].distanceWithEdge;
                choose[j].distanceWithEdge = temp;
            }
        }
    }

    return std::make_pair(choose[0].x, choose[0].y);
    */
    // 找到所有標記為 'a' 的可用移動位置
    std::vector<std::pair<int, int>> availableMoves;

    for (int y = 0; y < BOARDLENGTH; y++) {
        for (int x = 0; x < BOARDLENGTH; x++) {
            if (board[y][x] == 'a') {
                availableMoves.push_back({x, y});
            }
        }
    }

    // 如果沒有可用移動，返回 (-1, -1)
    if (availableMoves.empty()) {
        return {-1, -1};
    }

    // 優先選擇四個角點位置
    for (const auto& [x, y] : availableMoves) {
        if ((x == 0 && y == 0) || (x == 0 && y == 7) ||
            (x == 7 && y == 0) || (x == 7 && y == 7)) {
            return {x, y};
            }
    }

    // 其次選擇邊緣位置
    for (const auto& [x, y] : availableMoves) {
        if (x == 0 || x == 7 || y == 0 || y == 7) {
            return {x, y};
        }
    }

    // 最後隨機選擇一個可用位置
    int randomIndex = rand() % availableMoves.size();
    return availableMoves[randomIndex];
}

//     struct AIPlaySpace {
//         int x;
//         int y;
//         int distanceWithEdge;
//     };
//
//     std::vector<AIPlaySpace> choices;
//     int bestX = -1, bestY = -1;
//
//     // Find all available moves (AI is white)
//     this->showPlayPlace(true);
//
//     // Collect all available positions
//     for (int y = 0; y < BOARDLENGTH; y++) {
//         for (int x = 0; x < BOARDLENGTH; x++) {
//             if (this->board[y][x] == 'a') {
//                 // Calculate edge distance (lower is better)
//                 int distToEdgeY = std::min(y, BOARDLENGTH - 1 - y);
//                 int distToEdgeX = std::min(x, BOARDLENGTH - 1 - x);
//                 int distanceWithEdge = std::min(distToEdgeX, distToEdgeY);
//
//                 // Add to choices
//                 choices.push_back({x, y, distanceWithEdge});
//             }
//         }
//     }
//
//     // Sort by edge distance (prefer moves closer to edges)
//     std::sort(choices.begin(), choices.end(),
//               [](const AIPlaySpace& a, const AIPlaySpace& b) {
//                   return a.distanceWithEdge < b.distanceWithEdge;
//               });
//
//     // If we have choices, make the best one
//     if (!choices.empty()) {
//         // Choose the move closest to an edge
//         bestX = choices[0].x;
//         bestY = choices[0].y;
//
//         // Place the white piece
//         board[bestY][bestX] = 'w';
//     }
//
//     return std::make_pair(bestX, bestY);
// }
