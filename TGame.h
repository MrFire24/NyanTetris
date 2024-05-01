#pragma once
#include "TScreen.h"
#include "TFigure.h"

class TGame {
private:
	TScreen* Screen;
	TFigure* Figure;

	int Score = 0;

	bool isGameOver = false;
	bool fastMode;

	float getSpeed();
	void printControls();
	void checkControls();
	void checkLines();
public:
	TGame();

	void start();
};