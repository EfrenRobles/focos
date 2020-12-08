#pragma once
#include "Core.h"

class Puzzle : public Core
{

public:
    Puzzle(void);
    ~Puzzle(void);

    void resolveStep(byte option);
    void initPuzzle(HANDLE w, HANDLE r, byte x, byte y, char puzzle_room[ROOM_X][ROOM_Y]);
    char(&Puzzle::getRoom(void))[ROOM_X][ROOM_Y];
    byte getBulb(void);
    byte getDark(void);

protected:

private:
    char puzzle_room[ROOM_X][ROOM_Y];

    void logicSelector(byte option);

    void step_a(void);
    void step_b(void);
    void step_c(void);
    void step_d(void);

    void step_e(void);
    void step_f(void);
    void step_g(void);
    void step_h(void);


    void seekSome(byte x, byte y);
    byte seekXPlus(byte x, byte y, byte number_ways);
    byte seekXMinus(byte x, byte y, byte number_ways);
    byte seekYPlus(byte x, byte y, byte number_ways);
    byte seekYMinus(byte x, byte y, byte number_ways);

    void step_2(void);
    bool isBulb(char seek_x, char seek_y, char x, char y);
    void seekBulb(byte x, byte y);

    void step_3(void);

    void step_4(void);
    void setBulb(byte x, byte y, ROOM ground);


};
