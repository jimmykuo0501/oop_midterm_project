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
#include<string>
#include<ctime>
#include"Global.h"
#include"main.h"

using namespace std;

//Functions in this header file.
bool playChess();
bool userInput();
bool create(int mode);
bool save(int posX, int posY, bool player);

/**
 * Place the chess on the given possition if it is a valid possition.
 *
 * \param posX Selected possition's x cordinate.
 * \param posY Selected possition's y cordinate.
 * \param player Current player(Black:false	White:ture).
 * \return True if success, else false.
 */
bool playChess() {
	if (board[posY][posX] == 'a') {
		board[posY][posX] = (player) ? 'w' : 'b';
		save(posX, posY, player);
		return true;
	}
	else {
		return false;
	}
}

/**
 * User input state(25sec of play time limit).
 *
 * \return True if success, else false.
 */
bool userInput() {
	time_t gameTime = time(NULL);	//Record start time.

	while (time(NULL) - gameTime < 26) {
		if (_kbhit()) {
			switch (_getch()) {
			case 119:
			case 87:
			case 72:	//Up arrow
				if (posY > 0) posY--;
				break;
			case 115:
			case 83:
			case 80:	//Down arrow
				if (posY < 7) posY++;
				break;
			case 65:
			case 97:
			case 75:	//Left arrow
				if (posX > 0) posX--;
				break;
			case 68:
			case 100:
			case 77:	//Right arrow
				if (posX < 7) posX++;
				break;
			case 13:	//Enter
				if (playChess())
					return true;
				else
					cout << "Possition invalid!\n";
			}

			system("CLS");

			cout << "Game:" << gameName << '\n';

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					cout << board[i][j] << ' ';	//Debug
				}
				cout << '\n';
			}

			cout << posX << ' ' << posY << ' ' << ' ' << player << '\n';	//Debug message.
		}
	}

	return false;
}

bool save(int posX, int posY, bool player) {
	ofstream game;
	game.open(gameName, ios::app);	//Open game with append mode.

	//Check if game.txt file is opened.
	if (game.fail()) {
		return false;
	}
	else {	//Record.
		game << time(NULL) << '-' << posX << '-' << posY << '-' << ((player) ? 'w' : 'b') << '\n';

		game.close();

		return true;
	}
}

/**
 * Create a game.
 *
 * \param mode 0.Player vs Player, 1.Player vs Bot.
 * \return True if create success, else false.
 */
bool create(int mode) {
	ofstream game;
	gameName = to_string(time(NULL))+".txt";	//Set the game name based on system time.
	game.open(gameName);

	//Check if game.txt is opened
	if (game.fail())
		return false;

	//Write the properties of this game into txt file.
	game << "Game:" << gameName << '\n';
	if (mode)
		game << "player-player" << '\n';
	else
		game << "player-bot" << '\n';

	game << "-------------------------" << '\n';

	game.close();

	return true;
}
