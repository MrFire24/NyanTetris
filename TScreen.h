#pragma once
#include "TBlock.h"

class TScreen {
private:
    short fieldX = 10;
    short fieldY = 20;
    TBlock*** Field;
public:
    TScreen(short fieldX, short fieldY);

    void draw();

    short getX();
    short getY();

    TBlock* getBlock(short x, short y);
    void putBlock(short x, short y, TBlock* block);
    void delBlock(short x, short y);

    void delLine(short line);
};