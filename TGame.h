#pragma once
#include "TScreen.h"
#include "TFigure.h"

class TGame {
private:
	TScreen* Screen;
	TFigure* Figure;

	bool isGameOver = false;
	bool fastMode;
public:
	TGame();

	void start();
	void checkControls();
	void checkLines();
};