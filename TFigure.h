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

    const bool Figures[7][3][4]{
  {
    {1, 1, 0, 0},
    {1, 1, 0, 0}, //0
    {0, 0, 0, 0}
  },
  {
    {0, 0, 0, 0},
    {1, 1, 1, 0}, //1
    {0, 0, 1, 0}
  },
  {
    {0, 0, 1, 0},
    {1, 1, 1, 0}, //2
    {0, 0, 0, 0}
  },
  {
    {0, 0, 0, 0},
    {1, 1, 0, 0}, //3
    {0, 1, 1, 0}
  },
  {
    {0, 1, 1, 0},
    {1, 1, 0, 0}, //4
    {0, 0, 0, 0}
  },
  {
    {0, 0, 0, 0},
    {1, 1, 1, 1}, //5
    {0, 0, 0, 0}
  },
  {
    {0, 1, 0, 0},
    {1, 1, 0, 0}, //6
    {0, 1, 0, 0}
  }
    };

    const int8_t FigureRotationCount[7] = { 1, 4, 4, 2, 2, 2, 4 };
public:
    TBlock* Block;
    TFigure(TScreen* Screen);

    bool tryRespawn();
    bool tryRotate();
    //dir: 0 = left; 1 = down; 2 = right
    bool tryMove(short dir);
};