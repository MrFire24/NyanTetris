#include "TScreen.h"
#include "DBOperator.h"
#include <iostream>

using std::cout;
using std::endl;

TScreen::TScreen() {
    Field = new TBlock**[FIELD_HEIGHT];
    for (short i = 0; i < FIELD_HEIGHT; i++) {
        Field[i] = new TBlock*[FIELD_WIDTH];
        for (short j = 0; j < FIELD_WIDTH; j++)
            Field[i][j] = nullptr;
    }

    FieldChunk = new ConsoleChunk(2, 1, FIELD_WIDTH * 2, FIELD_HEIGHT);
    DataChunk = new ConsoleChunk(FieldChunk->getPos()[0] + FieldChunk->getSize()[0] + 3, 1, 16, FIELD_HEIGHT);
}

void TScreen::createFrame() {
    gotoxy(1, 1);
    cout << rgb(128, 128, 128);
    for (short iy = -1; iy <= FIELD_HEIGHT; iy++) {
        for (short ix = -1; ix <= FIELD_WIDTH; ix++) {
            if (iy == -1 || iy == FIELD_HEIGHT || ix == -1 || ix == FIELD_WIDTH) cout << "##";
            else cout << "  ";
        }
        cout << endl;
    }
}

void TScreen::draw() {
    while (true) {
        FieldChunk->setCursorPos(1, 1);
        for (short iy = 0; iy < FIELD_HEIGHT; iy++) {
            for (short ix = 0; ix < FIELD_WIDTH; ix++) {
                if (getBlock(ix, iy) != nullptr) {
                    cout << getBlock(ix, iy)->getColor();
                    FieldChunk->print("[]");
                }
                else {
                    cout << rgb(32, 32, 32);
                    FieldChunk->print("<>");
                }
            }
            FieldChunk->nextLine();
        }
    }
}

void TScreen::startDrawing(){
    FieldThread = new std::thread(&TScreen::draw, this);
}

void TScreen::stopDrawing() {
    delete FieldThread;
}

TBlock* TScreen::getBlock(short x, short y) { return Field[y][x]; }

void TScreen::putBlock(short x, short y, TBlock* block) { Field[y][x] = block; }

void TScreen::delBlock(short x, short y) {
    Field[y][x] = nullptr;
}

void TScreen::delLine(short line) {
    delete[](Field[line]);
    for (short iy = line; iy >= 1; iy--) {
        Field[iy] = Field[iy - 1];
    }
    Field[0] = new TBlock * [FIELD_WIDTH];
    for (short i = 0; i < FIELD_WIDTH; i++) Field[0][i] = nullptr;
}

void TScreen::printControls() {
    cout << R"( 
  Controls:
   A - left 		  ^~^  ,
   D - right		 ('Y') )
   W - rotate		 /   \/ 
   S - down 		(\|||/)
   Space - quick down (full down)

   Mouse Click - pause	 /\_/\
   Enter - continue	( o.o )
   C - change color	 > ^ <
	
  (Affects only the quick down function)
  FastMode or SafeMode (F/S): )";
}

bool TScreen::tryPrintHightscores() {
    Table Higthscores = TetrisDB.tryGetHigthscores(7);
    if (Higthscores.data != nullptr) {
        cout << "\n   Higthscores Table (TOP 7):" << endl;
        for (int i = 0; i < Higthscores.row_count; i++) {
            cout << "   " << i + 1 << ". " << Higthscores.data[0][i] << '\t' << Higthscores.data[1][i] << endl;
        }
        return true;
    }
    cout << "\n   Higthscores Table Loading Failed" << endl;
    return false;
}