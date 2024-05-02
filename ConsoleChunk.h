#pragma once
#include <string>

class ConsoleChunk {
private:
	int _PosX, _PosY;
	int _SizeX, _SizeY;
	int _CursorPosX = 1, _CursorPosY = 1;
public:
	ConsoleChunk(int posx, int posy, int sizex, int sizey);

	int* getPos();
	int* getSize();
	int* getCursorPos();
	
	void setCursorPos(int x, int y);
	void setCursorX(int x);
	void setCursorY(int y);

	void moveCursor(int x, int y);

	void print(std::string text);
	void prevLine(int count = 1);
	void nextLine(int count = 1);
	
};