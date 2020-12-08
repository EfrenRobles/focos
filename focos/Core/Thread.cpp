#include "StdAfx.h"
#include "Thread.h"

/**
 * The class destruct.
 *
 * @return void
 */
Thread::Thread(void)
{
    puzzle *result = new puzzle;
    puzzle *base = new puzzle;
}

/**
 * Function to setup the screen.
 *
 * @return void
 */
Thread::~Thread(void)
{
}

/**
 * Function to solve the puzzle.
 *
 * @return void
 */
void Thread::solvePuzzle(void)
{
    initPuzzle();
    launchPuzzle();
    resultPuzzle();
}

/**
 * Function to initialize the thread for the puzzle.
 *
 * @return void
 */
void Thread::initPuzzle(void)
{
    base.bulb = 250;
    result.bulb = 250;

    copyMatrix(room, base.room);
    base_room_x = room_x;
	base_room_y = room_y;

}

/**
 * Function to launch the thread for the puzzle.
 *
 * @return void
 */
void Thread::launchPuzzle(void)
{
    byte logicCount = 0;

    while (logicCount < 9) {

        Puzzle *puz = new Puzzle();
        puz->initPuzzle(w_hnd, r_hnd, base_room_x, base_room_y, base.room);
        puz->resolveStep(logicCount);

        if (result.bulb > puz->getBulb()) {
            copyMatrix(puz->getRoom(), result.room);
            result.bulb = puz->getBulb();
        }
        logicCount ++;
    }
    //delete puz;
}

/**
 * Function to launch the thread for the puzzle.
 *
 * @return void
 */
void Thread::resultPuzzle(void)
{
    copyMatrix(result.room, room);
    room_x = base_room_x;
	room_y = base_room_y;

    drawRoom();
}
