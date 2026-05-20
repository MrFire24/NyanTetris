#pragma once
#include "TBlock.h"
#include "ConsoleChunk.h"
#include "leaderboard.h"
#include "Config.h"
#include <thread>
#include <vector>

class TScreen {
private:
    TBlock*** Field;
    ConsoleChunk FieldChunk;
    ConsoleChunk DataChunk;
    
public:
    TScreen();

    void createFrame();
    void draw();
    void redrawBlock(short x, short y);
    void local_draw(short x, short y);

    TBlock* getBlock(short x, short y);
    void putBlock(short x, short y, TBlock* block);
    void delBlock(short x, short y);

    void delLine(short line);   

    void printControls();
    bool tryPrintHightscores();
    bool tryPrintHightscores(std::vector<PlayerRecord> records);
};