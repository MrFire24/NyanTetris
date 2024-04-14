#pragma once
#include <string>

std::string rgb(int r, int g, int b);

class TBlock {
private:
    std::string color = rgb(255, 255, 255);
public:
    TBlock();
    TBlock(short r, short g, short b);

    std::string getColor();
    void setColor(short r, short g, short b);
    void del();
};