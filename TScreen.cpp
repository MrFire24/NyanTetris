#include "TScreen.h"
#include "leaderboard.h"
#include <iostream>

using std::cout;
using std::endl;

TScreen::TScreen() : 
    FieldChunk(2, 1, FIELD_WIDTH * 2, FIELD_HEIGHT), 
    DataChunk(FieldChunk.getPos()[0] + FieldChunk.getSize()[0] + 3, 1, 16, FIELD_HEIGHT)
{
    Field = new TBlock**[FIELD_HEIGHT];
    for (short i = 0; i < FIELD_HEIGHT; i++) {
        Field[i] = new TBlock*[FIELD_WIDTH];
        for (short j = 0; j < FIELD_WIDTH; j++)
            Field[i][j] = nullptr;
    }
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
    FieldChunk.setCursorPos(1, 1);
    for (short iy = 0; iy < FIELD_HEIGHT; iy++) {
        for (short ix = 0; ix < FIELD_WIDTH; ix++) {
            if (getBlock(ix, iy) != nullptr) {
                cout << getBlock(ix, iy)->getColor();
                FieldChunk.print("[]");
            }
            else {
                cout << rgb(32, 32, 32);
                FieldChunk.print("<>");
            }
        }
        FieldChunk.nextLine();
    }
}

void TScreen::drawBlock(short x, short y) {
    FieldChunk.setCursorPos(x * 2 + 1, y + 1);
    if (getBlock(x, y) != nullptr) {
        cout << getBlock(x, y)->getColor();
        FieldChunk.print("[]");
    }
    else {
        cout << rgb(32, 32, 32);
        FieldChunk.print("<>");
    }
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

   P - pause/continue  /\_/\
   C - change color   ( o.o )
                       >   <
   PLEASE READ CONTROLS BEFORE STARTING

  Write 'S' to start: )";
}

bool TScreen::tryPrintHightscores() {
    Leaderboard lb("leaderboard.dat");
    lb.load();
    std::vector<PlayerRecord> records = lb.getRecords();
    cout << "\n   Higthscores Table (TOP 7):" << endl;
    for (int i = 0; i < records.size() && i < 7; i++) {
        cout << "   " << i + 1 << ". " << records[i].name << '\t' << records[i].score << endl;
    }
    return true;
    cout << "\n   Higthscores Table Loading Failed or Empty" << endl;
    return false;
}

bool TScreen::tryPrintHightscores(std::vector<PlayerRecord> records) {
    if (!records.empty()) {
        cout << "\n   Higthscores Table (TOP 7):" << endl;
        for (int i = 0; i < records.size() && i < 7; i++) {
            cout << "   " << i + 1 << ". " << records[i].name << '\t' << records[i].score << endl;
        }
        return true;
    }
    cout << "\n   Higthscores Table Loading Failed or Empty" << endl;
    return false;
}

