#include "TGame.h"
#include "TScreen.h"
#include "TFigure.h"
#include "deltaTime.h"
#include "DBOperator.h"
#include <conio.h>
#include <iostream>
#include <cmath>
#include <windows.h>

void setUpConsole() {
	std::cout << "\x1b[8;" << SCREEN_HEIGHT << ";" << SCREEN_WIDTH << "t";
	std::cout << "\x1b]0;Tetris v" << GAME_VERSION << "\x07";

	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	fontInfo.dwFontSize.Y = desktop.bottom / SCREEN_HEIGHT / 2;
	fontInfo.dwFontSize.X = fontInfo.dwFontSize.Y / 2;

	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	SetConsoleScreenBufferSize(hConsole, { SCREEN_WIDTH, SCREEN_HEIGHT });
}

TGame::TGame() {
	system("cls"); //обязательно для того что - бы в собраном проекте работали escape-последовательности(хз почему так)
	setUpConsole();

	char answer;
	while (true) {
		system("cls");

		Table Higthscores = TetrisDB.tryGetHigthscores(7);
		if (Higthscores.data != nullptr) {
			cout << "\n   Higthscores Table (TOP 7):" << endl;
			for (int i = 0; i < Higthscores.row_count; i++) {
				cout << "   " << i + 1 << ". " << Higthscores.data[0][i] << '\t' << Higthscores.data[1][i] << endl;
			}
		}
		else cout << "\n   Higthscores Table Loading Failed" << endl;

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
  FastMode or SafeMode (F/S): )";

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
	std::cout << "\x1b[s";
	std::cout << "\x1b[?25l";

	Screen = new TScreen();
	Figure = new TFigure(Screen);
}

int Score = 0;
float getSpeed() {
	return pow(log10((float)Score / 750. + 1.), 2.) + 1.;
}

string removeSpecialCharacter(string s){
	string ans = "";
	for (auto ch : s) if (isalpha(ch))ans += ch;
	return ans;
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
		gotoxy(2 * FIELD_WIDTH + 7, 2);
		std::cout << rgb(250, 250, 250) + "Score: " << Score;
		gotoxy(2 * FIELD_WIDTH + 7, 4);
		std::cout << rgb(250, 250, 250) + "Speed: " << getSpeed();
	}
	Table Higthscores;

	while (true) {
		system("cls");
		Higthscores = TetrisDB.tryGetHigthscores(7);
		if (Higthscores.data != nullptr) {
			cout << "\n   Your Score is: " << Score << endl;
			cout << "\n   Higthscores Table (TOP 7):" << endl;
			for (int i = 0; i < Higthscores.row_count; i++) {
				cout << "   " << i + 1 << ". " << Higthscores.data[0][i] << '\t' << Higthscores.data[1][i] << endl;
			}
			break;
		}
		else {
			cout << "   Higthscores Table Loading Failed" << endl;
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
					system("cls");
					if (Higthscores.data != nullptr) {
						cout << "\n   Your Score is: " << Score << endl;
						cout << "\n   Higthscores Table (TOP 7):" << endl;
						for (int i = 0; i < Higthscores.row_count; i++) {
							cout << "   " << i + 1 << ". " << Higthscores.data[0][i] << '\t' << Higthscores.data[1][i] << endl;
						}
					}
					else cout << "   Higthscores Table Loading Failed" << endl;
					break;
				}
			}
			break;
		}
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
			}
			else if (Screen->getBlock(ix, iy) == nullptr) break;
		}
	}
}