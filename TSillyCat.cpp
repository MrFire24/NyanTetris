#include "TSillyCat.h"
#include "Defines.h"
#include "TBlock.h"


TSillyCat SillyCat;

TSillyCat::TSillyCat() {
}

void TSillyCat::updateFace() {
	//return;
	std::cout << rgb(255, 255, 255);
	if (_mood >= 2) {
		gotoxy(_mouthPos[0] - 1, _mouthPos[1]);	std::cout << " vv";
		gotoxy(_eyePos1[0], _eyePos1[1]);		std::cout << ">";
		gotoxy(_eyePos2[0], _eyePos2[1]);		std::cout << "<";
	}
	else if (_mood == 1) {
		gotoxy(_mouthPos[0] - 1, _mouthPos[1]);	std::cout << " vv";
		gotoxy(_eyePos1[0], _eyePos1[1]);		std::cout << "U";
		gotoxy(_eyePos2[0], _eyePos2[1]);		std::cout << "U";
	}
	else if (_mood == 0) {
		gotoxy(_mouthPos[0] - 1, _mouthPos[1]);	std::cout << " w ";
		gotoxy(_eyePos1[0], _eyePos1[1]);		std::cout << "U";
		gotoxy(_eyePos2[0], _eyePos2[1]);		std::cout << "U";
	}
	else if (_mood == -1) {
		gotoxy(_mouthPos[0] - 1, _mouthPos[1]);	std::cout << " - ";
		gotoxy(_eyePos1[0], _eyePos1[1]);		std::cout << "O";
		gotoxy(_eyePos2[0], _eyePos2[1]);		std::cout << "O";
	}
	else if (_mood <= -2) {
		gotoxy(_mouthPos[0] - 1, _mouthPos[1]);	std::cout << " ^ ";
		gotoxy(_eyePos1[0], _eyePos1[1]);		std::cout << "O";
		gotoxy(_eyePos2[0], _eyePos2[1]);		std::cout << "O";
	}

	if (_mood > 0) _mood--;
	else if (_mood < 0) _mood++;
}

void TSillyCat::changeMood(int value) {
	_mood += value;
}