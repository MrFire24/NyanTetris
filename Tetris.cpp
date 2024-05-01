#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include "TGame.h"
#include "Defines.h"
#include "TSoundOperator.h"

using namespace std;

int main()
{
    srand(time(NULL));
    SoundOperator.playSound(100 + rand(-20, 20), 400, 80, 97);
    TGame* Game;
    while (true) {
        Game = new TGame;
        Game->start();
        cout << "\n  Restart (Y/N): ";
        char input;
        saveCursorPos();
        while (true) {
            loadCursorPos();
            cout << "\x1b[u            \x1b[u";
            cin >> input;
            input = tolower(input);
            if (input == 'y') break;
            if (input == 'n') exit(1);
        }
        delete Game;
    }
    
    
}
