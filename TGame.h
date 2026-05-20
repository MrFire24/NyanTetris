#pragma once
#include "TScreen.h"
#include "TFigure.h"

class TGame {
private:
	TScreen* Screen;
	TFigure* Figure;

	int Score = 0;

	bool isGameOver = false;

	const float getSpeed();
	void printControls();
	void checkControls();
	void checkLines();
	void rewriteScores();
public:
	TGame();

	void start();
};