#include "TBlock.h"

std::string rgb(int r, int g, int b) {
    r = std::min(r, 255); r = std::max(r, 0);
    g = std::min(g, 255); g = std::max(g, 0);
    b = std::min(b, 255); b = std::max(b, 0);
    return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

TBlock::TBlock() {}
TBlock::TBlock(short r, short g, short b) : color(rgb(r, g, b)) {}

std::string TBlock::getColor() {
    return color;
}

void TBlock::setColor(short r, short g, short b) {
    color = rgb(r, g, b);
}

void TBlock::del() {
    delete this;
}