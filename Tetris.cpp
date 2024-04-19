#include <iostream>
#include "TGame.h"

int main()
{
    srand(time(NULL));
    TGame Game(FIELD_WIDTH, FIELD_HEIGHT);
    Game.start();
}
