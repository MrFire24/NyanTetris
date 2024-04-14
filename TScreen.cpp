#include "TScreen.h"
#include <iostream>

TScreen::TScreen(short fieldX, short fieldY) : fieldX(fieldX), fieldY(fieldY) {
    Field = new TBlock**[fieldY];
    for (short i = 0; i < fieldY; i++) {
        Field[i] = new TBlock*[fieldX];
        for (short j = 0; j < fieldX; j++)
            Field[i][j] = nullptr;
    }
}

void TScreen::draw() {
    system("cls");
    for (short iy = -1; iy <= fieldY; iy++) {
        for (short ix = -1; ix <= fieldX; ix++) {
            if (iy == -1 || iy == fieldY || ix == -1 || ix == fieldX) {
                std::cout << rgb(128, 128, 128) + "##";
            }
            else if (getBlock(ix, iy) != nullptr) std::cout << getBlock(ix, iy)->getColor() + "[]";
            else std::cout << rgb(24, 24, 24) + "<>";
        }
        std::cout << std::endl;
    }
}

short TScreen::getX() { return fieldX; }
short TScreen::getY() { return fieldY; }

TBlock* TScreen::getBlock(short x, short y) { return Field[y][x]; }

void TScreen::putBlock(short x, short y, TBlock* block) { Field[y][x] = block; }

void TScreen::delBlock(short x, short y) {
    Field[y][x] = nullptr;
}

void TScreen::delLine(short line) {

    delete[](Field[line]);
    for (short iy = line; iy >= 1; iy--) {
        Field[iy] = Field[iy - 1];
    }
    Field[0] = new TBlock * [fieldX];
    for (short i = 0; i < fieldX; i++) Field[0][i] = nullptr;
}