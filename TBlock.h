#pragma once
#include <string>
#include "Config.h"

std::string rgb(int r, int g, int b);
short rand(short from, short to);

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