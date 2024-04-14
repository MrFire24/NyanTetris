#include <iostream>
#include "TGame.h"

int main()
{
    srand(time(NULL));
    TGame Game(9, 20);
    Game.start();
}
