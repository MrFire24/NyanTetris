#pragma once
#include <string>
#include "Config.h"
#include "Defines.h"

short rand(short from, short to);
std::string rgb(int r, int g, int b);
//from 0 to 1536
std::string brighRGB(int color);
std::string randomBRGB();

class TBlock {
private:
    std::string color = rgb(255, 255, 255);
public:
    TBlock();
    TBlock(short r, short g, short b);
    ~TBlock();

    std::string getColor();
    void setColor(short r, short g, short b);
    void setRandomColor();
};