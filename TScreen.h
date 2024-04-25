#pragma once
#include "TBlock.h"

class TScreen {
private:
    TBlock*** Field;
public:
    TScreen();

    void draw();

    TBlock* getBlock(short x, short y);
    void putBlock(short x, short y, TBlock* block);
    void delBlock(short x, short y);

    void delLine(short line);   
};