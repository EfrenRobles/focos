#pragma once
#include "Puzzle.h"

class Thread : public Puzzle
{

public:

    Thread(void);
    ~Thread(void);

protected:
    void solvePuzzle(void);

private:

    byte base_room_x;
	byte base_room_y;

    struct puzzle
    {
        char room[ROOM_X][ROOM_Y];
        byte bulb;
        byte dark;
    } result, base;

    void initPuzzle(void);
    void launchPuzzle(void);
    void resultPuzzle(void);

};
