#pragma once
#include "Core.h"

class Puzzle : public Core
{

public:
    Puzzle(void);
    ~Puzzle(void);

protected:
    void resolve_step_1(void);

private:
    char puzzle_room[ROOM_X][ROOM_Y];

    void step_1(void);
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
