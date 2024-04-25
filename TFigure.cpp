#include "TFigure.h"
#include "TBlock.h"
#include "deltaTime.h"
#include <iostream>

TFigure::TFigure(TScreen* Screen) : Screen(Screen) { tryRespawn(); };

short* TFigure::getProcessedBlockPos(short x, short y, short rot) {
    static short ProcessedBlockPos[2];
    switch (rot) {
    case 0:
    default:
        ProcessedBlockPos[0] = - x + 1;
        ProcessedBlockPos[1] = + y - 1;
        break;
    case 1:
        ProcessedBlockPos[0] = - y + 1;
        ProcessedBlockPos[1] = - x + 1;
        break;
    case 2:
        ProcessedBlockPos[0] = + x - 1;
        ProcessedBlockPos[1] = - y + 1;
        break;
    case 3:
        ProcessedBlockPos[0] = + y - 1;
        ProcessedBlockPos[1] = + x - 1;
        break;
    }
    return ProcessedBlockPos;
}

bool TFigure::tryPutOn(short newX, short newY, short newRot) {
    static short* blockPos;
    static short blockX;
    static short blockY;
    for (short iy = 0; iy < 4; iy++) {
        for (short ix = 0; ix < 3; ix++) {
            blockPos = getProcessedBlockPos(ix, iy, newRot);
            blockX = newX + blockPos[0];
            blockY = newY + blockPos[1];
            if (Figures[type][ix][iy]) {
                if (blockX < 0 || blockX >= FIELD_WIDTH || blockY >= FIELD_HEIGHT) return false;
                if (Screen->getBlock(blockX, blockY) != nullptr && Screen->getBlock(blockX, blockY) != Block) return false;
            }
        }
    }

    for (short iy = 0; iy < 4; iy++) {
        for (short ix = 0; ix < 3; ix++) {
            blockPos = getProcessedBlockPos(ix, iy, rotarion);
            blockX = x + blockPos[0];
            blockY = y + blockPos[1];
            if (Figures[type][ix][iy] && Screen->getBlock(blockX, blockY) == Block) Screen->delBlock(blockX, blockY);
        }
    }

    for (short iy = 0; iy < 4; iy++) {
        for (short ix = 0; ix < 3; ix++) {
            blockPos = getProcessedBlockPos(ix, iy, newRot);
            blockX = newX + blockPos[0];
            blockY = newY + blockPos[1];
            if (Figures[type][ix][iy]) Screen->putBlock(blockX, blockY, Block);
        }
    }
    x = newX;
    y = newY;
    rotarion = newRot;
    Screen->draw();
    return true;
}


bool TFigure::tryRespawn() {
    Block = new TBlock();
    type = rand(1, 7) - 1;
    x = FIELD_WIDTH / 2;
    y = 1;
    rotarion = 0;
    deltaTime.resetTime();
    return tryPutOn(x, y, rotarion);
}

bool TFigure::tryRotate() {
    for (short i = 1; i < FigureRotationCount[type]; i++) { 
        if (tryPutOn(x, y, (rotarion + i) % FigureRotationCount[type]))
            return true;
    }
    return false;
}

//dir: 0 = left; 1 = down; 2 = right
bool TFigure::tryMove(short dir) {
    switch (dir){
    case 0: 
        if (tryPutOn(x - 1, y, rotarion)) return true;
        break;
    case 1: 
        if (tryPutOn(x, y + 1, rotarion)) return true;
        break;
    case 2: 
        if (tryPutOn(x + 1, y, rotarion)) return true;
        break;
    }
    return false;
}

