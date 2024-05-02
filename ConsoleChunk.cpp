#include "ConsoleChunk.h"
#include <iostream>

#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x));

ConsoleChunk::ConsoleChunk(int posx, int posy, int sizex, int sizey) : _PosX(posx), _PosY(posy), _SizeX(sizex), _SizeY(sizey) {}

int* ConsoleChunk::getPos() {
	int* pos = new int[2];
	pos[0] = _PosX;
	pos[1] = _PosY;
	return pos;
}

int* ConsoleChunk::getSize() {
	int* size = new int[2];
	size[0] = _SizeX;
	size[1] = _SizeY;
	return size;
}

int* ConsoleChunk::getCursorPos() {
	int* pos = new int[2];
	pos[0] = _CursorPosX;
	pos[1] = _CursorPosY;
	return pos;
}


void ConsoleChunk::setCursorPos(int x, int y) {
	_CursorPosX = x;
	_CursorPosY = y;
}

void ConsoleChunk::setCursorX(int x) { setCursorPos(x, _CursorPosY); }
void ConsoleChunk::setCursorY(int y) { setCursorPos(_CursorPosX, y); }

/*
void ConsoleChunk::moveCursor(int x, int y) {
	_CursorPosX += x;
	_CursorPosY += y;
};
*/

void ConsoleChunk::prevLine(int count) { 
	for (int i = 0; i < count; i++) {
		if (_CursorPosY <= _SizeY) setCursorPos(1, _CursorPosY - 1);
		else break;
	}
}
void ConsoleChunk::nextLine(int count) {
	for (int i = 0; i < count; i++) {
		if (_CursorPosY <= _SizeY) setCursorPos(1, _CursorPosY + 1);
		else break;
	}
}

void ConsoleChunk::print(std::string text) {
	for (auto i:text) {
		if (_CursorPosX > _SizeX) {
			nextLine();
			if (_CursorPosY == _SizeY + 1) break;
		}
		gotoxy(_PosX + _CursorPosX, _PosY + _CursorPosY);
		std::cout << i;
		_CursorPosX++;
	}
}