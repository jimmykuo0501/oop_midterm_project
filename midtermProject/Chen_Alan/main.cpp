/*****************************************************************//**
 * \file   main.cpp
 * \brief
 *
 * \author Alan
 * \date   2025/3/14
 *********************************************************************/
#include<iostream>
#include<conio.h>
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
		if (!userInput()) {
			cout << "Game time exceeded!";
		}

		posX = posY = 0;
		player = !player;
	}

	return 0;
}
