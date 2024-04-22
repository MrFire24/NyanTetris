#pragma once
#include "TScreen.h"
#include "TBlock.h"

class TFigure {
private:
    TScreen* Screen;
    short type;
    short x, y;
    short rotarion = 0;
    //rotarion: 0 = 0deg; 1 = 90deg; 2 = 180deg; 3 = 270deg;

    bool tryPutOn(short newX, short newY, short newRot);
    short* getProcessedBlockPos(short x, short y, short rot);
public:
    TBlock* Block;
    TFigure(TScreen* Screen);

    bool tryRespawn();
    bool tryRotate();
    //dir: 0 = left; 1 = down; 2 = right
    bool tryMove(short dir);
};