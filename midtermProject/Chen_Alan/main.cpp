/*****************************************************************//**
 * \file   main.cpp
 * \brief
 *
 * \author Alan
 * \date   2025/3/14
 *********************************************************************/
#include<iostream>
#include<conio.h>
#include<string>
#include"Cpp Midtern Project.h"
#include"Global.h"
#include"main.h"

using namespace std;

int main() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 'a';	//Debug
		}
	}

	while (true) {
		string temp = "";

		cout << "Please input game save name, or create a new game!(Enter new to create) ";

		cin >> temp;

		if (!strcmp(temp.c_str(), "new")) {
			int mode = 0;

			cout << "Enter game mode(0 bot, 1 player) ";

			cin >> mode;

			create(mode);

			break;
		}
		else{
			ifstream checkFile;
			checkFile.open(temp + ".txt");

			if (!checkFile.fail()) {
				gameName = temp + ".txt";

				break;
			}
			else {
				cout << "Game not found, please enter a valid game!\n";
			}
		}
	}

	while (true) {
		if (!userInput()) {
			cout << "Game time exceeded!";
		}

		posX = posY = 0;
		player = !player;
	}

	return 0;
}
