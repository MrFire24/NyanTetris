#pragma once
#include "Config.h"


class TSillyCat {
private:
    int _mood = 0;
    
    int _mouthPos[2] = { 1 + 4 + FIELD_WIDTH * 2 + 2 + 7, 14 + 5};
    int _eyePos1[2] = { 1 + 4 + FIELD_WIDTH * 2 + 2 + 5, 14 + 4 };
    int _eyePos2[2] = { 1 + 4 + FIELD_WIDTH * 2 + 2 + 9, 14 + 4 };
public:
    TSillyCat();
    void updateFace();
    
    void changeMood(int value);
};

extern TSillyCat SillyCat;