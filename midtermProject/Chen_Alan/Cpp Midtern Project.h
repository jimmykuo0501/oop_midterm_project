/*****************************************************************//**
 * \file   Cpp Midtern Project.h
 * \brief  Cpp Midtern Project main part code(Header file).
 *
 * \author Alan
 * \date   2025/3/13
 *********************************************************************/
#pragma once

#include<iostream>
#include<fstream>
#include<conio.h>
#include<ctime>
#include"Global.h"
#include"main.h"

using namespace std;

/**
 * Place the chess on the given possition if it is a valid possition.
 *
 * \param posX
 * \param posY
 * \param player
 * \return
 */
bool playChess(short x, short y, bool player) {
	if (board[y][x] == 'a') {
		board[y][x] = (player) ? 'w' : 'b';
		return true;
	}
	else {
		return false;
	}
}

/**
 * User input state.
 *
 * \return True if success,else false.
 */
bool userInput() {
	time_t gameTime = time(NULL);

	while (time(NULL) - gameTime < 26) {
		if (_kbhit()) {
			switch (_getch()) {
			case 72:	//Up arrow
				if (posY > 0) posY--;
				break;
			case 80:	//Down arrow
				if (posY < 7) posY++;
				break;
			case 75:	//Left arrow
				if (posX > 0) posX--;
				break;
			case 77:	//Right arrow
				if (posX < 7) posX++;
				break;
			case 13:	//Enter
				if (playChess(posX, posY, player))
					return true;
				else
					cout << "Possition invalid!\n";
			}

			system("CLS");
			cout << posX << ' ' << posY << ' ' << ' ' << player << '\n';	//Debug message.
		}
	}

	return false;
}