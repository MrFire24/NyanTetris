#pragma once
#include "TBlock.h"
#include "ConsoleChunk.h"
#include "Config.h"
#include <thread>

class TScreen {
private:
    TBlock*** Field;
    ConsoleChunk* FieldChunk;
    ConsoleChunk* DataChunk;
    std::thread* FieldThread;
    //thread* DataThread;

    void draw();
public:
    TScreen();

    void createFrame();
    void startDrawing();
    void stopDrawing();

    TBlock* getBlock(short x, short y);
    void putBlock(short x, short y, TBlock* block);
    void delBlock(short x, short y);

    void delLine(short line);   

    void printControls();
    bool tryPrintHightscores();
};