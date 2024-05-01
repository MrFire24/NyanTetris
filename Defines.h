#pragma once
#include <iostream>

#define saveCursorPos() std::cout << "\x1b[s";
#define loadCursorPos() std::cout << "\x1b[u";
#define clearConsole() std::cout << "\033[H\033[J";
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x));
#define hideCursor() std::cout << "\x1b[?25l";
#define showCursor() std::cout << "\x1b[?25h";
