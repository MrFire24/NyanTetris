#include "TGame.h"
#include "TScreen.h"
#include "TFigure.h"
#include "deltaTime.h"
#include "DBOperator.h"
#include "Defines.h"
#include "TSoundOperator.h"
#include "TSillyCat.h"
#include <conio.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <thread>

void setUpConsole() {
	std::cout << "\x1b[8;" << SCREEN_HEIGHT << ";" << SCREEN_WIDTH << "t";
	std::cout << "\x1b]0;Tetris v" << GAME_VERSION << "\x07";

	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	fontInfo.dwFontSize.Y = desktop.bottom / SCREEN_HEIGHT * 2 / 3;
	fontInfo.dwFontSize.X = fontInfo.dwFontSize.Y / 2;

	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
}

void printControls() {

}

TGame::TGame() {
	system("cls"); //обязательно для того что - бы в собраном проекте работали escape-последовательности(хз почему так)
	setUpConsole();

	//MessageBox(NULL, L"Error text", L"Error", MB_ICONERROR);


	char answer;
	while (true) {
		clearConsole();

		Screen->tryPrintHightscores();

		Screen->printControls();

		std::cin >> answer;
		if (answer == 'F') {
			fastMode = true;
			break;
		}
		if (answer == 'S' || answer == '\n') {
			fastMode = false;
			break;
		}
	}

	system("cls");
	saveCursorPos();
	hideCursor();

	Screen = new TScreen();
	Figure = new TFigure(Screen);
}

float TGame::getSpeed() {
	return pow(log10((float)Score / 750. + 1.), 2.) + 1.;
}

string removeSpecialCharacter(string s){
	string ans = "";
	for (auto ch : s) if (isalpha(ch))ans += ch;
	return ans;
}

#define nl gotoxy(1 + 4 + FIELD_WIDTH * 2 + 2, 14 + i); i++;
void drawSillyCat() {
	cout << rgb(255, 255, 255);
	int i = 0;
	nl; cout << R"(   _       _   )";
	nl; cout << R"(  / \     / \  )";
	nl; cout << R"( |   \/\\/   | )";
	nl; cout << R"(_\ ___   ___ /_)";
	nl; cout << R"(\  ( U _ U )  /)";
	nl; cout << R"(/_ )" + rgb(255, 60, 100) + "z" + rgb(255, 255, 255) + "   w   " + rgb(255, 60, 100) + "z" + rgb(255, 255, 255) + R"( _\)";
	nl; cout << R"(  \___    __/  )";
	nl; cout << R"(    \     \    )";
	nl; cout << R"(    /_     \   )";
	nl; cout << R"(    /      |   )";
}

void TGame::start() {
	Screen->draw();
	drawSillyCat();
	while (!isGameOver) {
		if (_kbhit()) checkControls();
		deltaTime.updateTime();

		if (deltaTime >= 1. / getSpeed()) {
			deltaTime.resetTime();
			if (!Figure->tryMove(1)) {
				checkLines();
				if (!Figure->tryRespawn()) isGameOver = true;
			}
			SillyCat.updateFace();;
		}
		gotoxy(2 * FIELD_WIDTH + 7, 2);
		std::cout << rgb(250, 250, 250) + "Score: " << Score;
		gotoxy(2 * FIELD_WIDTH + 7, 4);
		std::cout << rgb(250, 250, 250) + "Speed: " << getSpeed();
	}
	SoundOperator.playSound(20, 500, 90, 118);
	showCursor();

	Table Higthscores;

	while (true) {
		clearConsole();
		cout << "\n   Your Score is: " << Score << endl;
		Higthscores = TetrisDB.tryGetHigthscores(7);
		if (Screen->tryPrintHightscores()) break;
		else {
			cout << "   If you want to retry connecting again, write \"R\": " ;
			char input; cin >> input;
			if (input != 'R') break;
		}
	}
	if (Higthscores.data != nullptr) {
		string input;
		for (int i = 0; i < Higthscores.row_count; i++) if (Score > stoi(Higthscores.data[1][i])) {

			cout << "\n\n   Your result is worthy of being \n   recorded in a Higthscores Table!" << endl;
			cout << "   Type your name (max length = 8): ";
			cout << "\x1b[s";
			while (true) {
				cout << "\x1b[u" << "                         " << "\x1b[u";
				cin >> input;
				input = removeSpecialCharacter(input);
				if (input == "" || input.length() > 8) continue;
				else{
					TetrisDB.tryAddHigthscore(input, Score);
					Higthscores = TetrisDB.tryGetHigthscores(7);
					clearConsole();
					Screen->tryPrintHightscores();
					break;
				}
			}
			break;
		}
	}
	//while (true);
}

void TGame::checkControls() {
	static char key;
	key = tolower(_getch());

	switch (key) {
	case ('a'):
		if (Figure->tryMove(0)) {
			SoundOperator.playSound(300, 20, 60, 74);
			SillyCat.changeMood(-1);
		}
		else {
			SoundOperator.playSound(100, 20, 60, 4);
		}
		break;
	case ('s'):
		if (Figure->tryMove(1)) {
			SoundOperator.playSound(350, 20, 60, 74);
			Score++;
		} 
		else {
			checkLines();
			if (!Figure->tryRespawn()) isGameOver = true;
		}
		deltaTime.resetTime();
		break;
	case ('d'):
		if (Figure->tryMove(2)) {
			SoundOperator.playSound(300, 20, 60, 74);
			SillyCat.changeMood(1);
		}
		else {
			SoundOperator.playSound(110, 20, 60, 4);
		}
		break;
	case ('w'):
		if (Figure->tryRotate()) {
			SoundOperator.playSound(350, 30, 80, 78);
		}
		else {
			SoundOperator.playSound(100, 15, 40, 87);
		}
		break;
	case (' '):
		while (Figure->tryMove(1)) {
			SoundOperator.playSound(390, 15, 50, 74);
			Score++;
			gotoxy(2 * FIELD_WIDTH + 7, 2);
			std::cout << rgb(250, 250, 250) + "Score: " << Score;
			gotoxy(2 * FIELD_WIDTH + 7, 4);
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
		Figure->Block->setRandomColor();
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
	for (short iy = FIELD_HEIGHT - 1; iy >= 0; iy--) {
		for (short ix = 0; ix <= FIELD_WIDTH; ix++) {
			if (ix == FIELD_WIDTH) {
				Screen->delLine(iy);
				iy++;
				Score += 100;
				SoundOperator.playSound(700, 25, 127, 95);
				Sleep(100);
				Screen->draw();
			}
			else if (Screen->getBlock(ix, iy) == nullptr) break;
		}
	}
}