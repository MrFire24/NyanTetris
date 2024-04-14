#pragma once
#include "TScreen.h"
#include "TFigure.h"

class TGame {
private:
	TScreen* Screen;
	TFigure* Figure;

	bool isGameOver = false;
	
public:
	TGame(short ScreenX, short ScreenY);

	void start();
	void checkControls();
	void checkLines();
};