#include "TGame.h"
#include "TScreen.h"
#include "TFigure.h"
#include "deltaTime.h"
#include <conio.h>
#include <iostream>
#include <cmath>

#define gotoxy(x,y) printf("\x1b[%d;%dH", (y), (x))

//
TGame::TGame(short ScreenX, short ScreenY) {
	system("cls"); //обязательно для того что - бы в собраном проекте работали escape - последовательности(хз почему так)
	std::cout << "\x1b]0;Tetris v" << GAME_VERSION << "\x07";

	char answer;
	while (true) {
		system("cls");

		std::cout << R"( 
  Controls:
   A - left 		  ^~^  ,
   D - right		 ('Y') )
   W - rotate		 /   \/ 
   S - down 		(\|||/)
   Space - quick down (full down)

   Mouse Click - pause	 /\_/\
   Enter - continue	( o.o )
   C - change color	 > ^ <
	
  (Affects only the quick down function)
  FastMod or SaveMod (F/S): )";

		std::cin >> answer;
		if (answer == 'F') {
			fastMode = true;
			break;
		}
		if (answer == 'S') {
			fastMode = false;
			break;
		}
	}

	system("cls");
	std::cout << "\x1b[s";
	std::cout << "\x1b[?25l";

	Screen = new TScreen(ScreenX, ScreenY);
	Figure = new TFigure(Screen);
}


int Score = 0;
float getSpeed() {
	return pow(log10((float)Score / 750. + 1.), 2.) + 1.;
}

void TGame::start() {
	Screen->draw();
	while (!isGameOver) {
		if (_kbhit()) checkControls();
		deltaTime.updateTime();

		if (deltaTime >= 1. / getSpeed()) {
			deltaTime.resetTime();
			if (!Figure->tryMove(1)) {
				checkLines();
				if (!Figure->tryRespawn()) isGameOver = true;
			}
				
		}
		gotoxy(2 * Screen->getX() + 7, 2);
		std::cout << rgb(250, 250, 250) + "Score: " << Score;
		gotoxy(2 * Screen->getX() + 7, 4);
		std::cout << rgb(250, 250, 250) + "Speed: " << getSpeed();
	}
	while (true);
}

void TGame::checkControls() {
	static char key;
	key = tolower(_getch());

	switch (key) {
	case ('a'):
		Figure->tryMove(0);
		break;
	case ('s'):
		if (!Figure->tryMove(1)) {
			checkLines();
			if (!Figure->tryRespawn()) isGameOver = true;
		}
		else Score++;
		deltaTime.resetTime();
		break;
	case ('d'):
		Figure->tryMove(2);
		break;
	case ('w'):
		Figure->tryRotate();
		break;
	case (' '):
		while (Figure->tryMove(1)) {
			Score++;
			gotoxy(2 * Screen->getX() + 7, 2);
			std::cout << rgb(250, 250, 250) + "Score: " << Score;
			gotoxy(2 * Screen->getX() + 7, 4);
			std::cout << rgb(250, 250, 250) + "Speed: " << getSpeed();
		}
		if (fastMode) {
			checkLines();
			if (!Figure->tryRespawn()) isGameOver = true;
		}
		else  {
			deltaTime.resetTime();
			if (_kbhit()) checkControls();
		}
		break;
	//	/	/	/	/
	case ('c'):
		Figure->Block->setColor(rand(1, 8) * 32, rand(1, 8) * 32, rand(1, 8) * 32);
		Screen->draw();
		break;
	case ('r'):
		//if (!Figure->tryRespawn()) GameOver = true;
		//Score++;
		break;
	default:
		break;
	}
}

void TGame::checkLines() {
	for (short iy = Screen->getY() - 1; iy >= 0; iy--) {
		for (short ix = 0; ix <= Screen->getX(); ix++) {
			if (ix == Screen->getX()) {
				Screen->delLine(iy);
				iy++;
				Score += 100;
			}
			else if (Screen->getBlock(ix, iy) == nullptr) break;
		}
	}
}