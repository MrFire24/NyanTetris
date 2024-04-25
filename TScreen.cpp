#include "TScreen.h"
#include <iostream>

#define gotoxy(x,y) printf("\x1b[%d;%dH", (y), (x))

TScreen::TScreen() {
    Field = new TBlock**[FIELD_HEIGHT];
    for (short i = 0; i < FIELD_HEIGHT; i++) {
        Field[i] = new TBlock*[FIELD_WIDTH];
        for (short j = 0; j < FIELD_WIDTH; j++)
            Field[i][j] = nullptr;
    }
}

void TScreen::draw() {
    gotoxy(0, 0);
    for (short iy = -1; iy <= FIELD_HEIGHT; iy++) {
        for (short ix = -1; ix <= FIELD_WIDTH; ix++) {
            if (iy == -1 || iy == FIELD_HEIGHT || ix == -1 || ix == FIELD_WIDTH) {
                std::cout << rgb(128, 128, 128) + "##";
            }
            else if (getBlock(ix, iy) != nullptr) std::cout << getBlock(ix, iy)->getColor() + "[]";
            else std::cout << rgb(32, 32, 32) + "<>";
        }
        std::cout << std::endl;
    }
}

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
    Field[0] = new TBlock * [FIELD_WIDTH];
    for (short i = 0; i < FIELD_WIDTH; i++) Field[0][i] = nullptr;
}