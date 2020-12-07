#include "StdAfx.h"
#include "Puzzle.h"

/**
 * The class construct.
 *
 * @return void
 */
Puzzle::Puzzle(void)
{
}

/**
 * The class destruct.
 *
 * @return void
 */
Puzzle::~Puzzle(void)
{
}


/**
 * Function to apply the first logic to resolve the puzzle.
 *
 * @return void
 */
void Puzzle::resolve_step_1(void)
{
    while (true) {
        step_1();
        drawRoom();

        if (spaces_in_darkness < 2) {
            break;
        }

        copyMatrix(room, puzzle_room);
        step_2();
        drawRoom();

        if (spaces_in_darkness < 2) {
            break;
        }

        step_3();
        drawRoom();

        if (spaces_in_darkness < 2) {
            break;
        }
    }
    
    step_4();
    drawRoom();
}

#pragma region Step 1 ---------------------------------------------------

/**
 * Function to apply the first logic to resolve the puzzle.
 *
 * @return void
 */
void Puzzle::step_1(void)
{
    for (byte y = 0; y <= room_y; y ++) {
        for (byte x = 0; x < room_x; x ++) {
            if (room[x][y] == ROOM_GROUND) {
                seekSome(x, y);
            }
        }
    }
}

/**
 * Function to seek if the place is safe to put a bulb.
 *
 * @param byte x
 * @param byte y
 * @return void
 */
void Puzzle::seekSome(byte x, byte y)
{
    byte number_ways = 0;

    number_ways = seekXPlus(x, y, number_ways);  // ->
    number_ways = seekXMinus(x, y, number_ways); // <-
    number_ways = seekYPlus(x, y, number_ways);  // ¡
    number_ways = seekYMinus(x, y, number_ways); // !

    if (number_ways > 1) {
        room[x][y] = ROOM_BULB;
        setBulb(x, y, ROOM_LIGHT);
        return;
    }
}

/**
 * Function to check the dark places in the right of the bulb.
 *
 * @param byte x
 * @param byte y
 * @param number_ways y
 * @return void
 */
byte Puzzle::seekXPlus(byte x, byte y, byte number_ways)
{
    for (char ground_x = x + 1; ground_x <= room_x; ground_x ++) {

        if (room[ground_x][y] == ROOM_WALL) {
            break;
        }

        if (room[ground_x][y] == ROOM_GROUND) {
            number_ways ++;
            break;
        }
    }

    return number_ways;
}


/**
 * Function to check the dark places in the left of the bulb.
 *
 * @param byte x
 * @param byte y
 * @param number_ways y
 * @return void
 */
byte Puzzle::seekXMinus(byte x, byte y, byte number_ways)
{
    for (char ground_x = x - 1; ground_x >= 0; ground_x --) {
        if (room[ground_x][y] == ROOM_WALL) {
            break;
        }

        if (room[ground_x][y] == ROOM_GROUND) {
            number_ways ++;
            break;
        }
    }

    return number_ways;
}

/**
 * Function to check the dark places below of the bulb.
 *
 * @param byte x
 * @param byte y
 * @param number_ways y
 * @return void
 */
byte Puzzle::seekYPlus(byte x, byte y, byte number_ways)
{
    for (char ground_y = y + 1; ground_y <= room_y; ground_y ++) {

        if (room[x][ground_y] == ROOM_WALL) {
            break;
        }

        if (room[x][ground_y] == ROOM_GROUND) {
            number_ways ++;
            break;
        }
    }

    return number_ways;
}

/**
 * Function to check the dark places above of the bulb.
 *
 * @param byte x
 * @param byte y
 * @param number_ways y
 * @return void
 */
byte Puzzle::seekYMinus(byte x, byte y, byte number_ways)
{
    for (char ground_y = y - 1; ground_y >= 0; ground_y --) {

        if (room[x][ground_y] == ROOM_WALL) {
            break;
        }

        if (room[x][ground_y] == ROOM_GROUND) {
            number_ways ++;
            break;
        }
    }

    return number_ways;
}
#pragma endregion

/**
 * Function to check if the dark place and the bulb would be exchanged.
 *
 * @return void
 */
void Puzzle::step_2(void)
{
    for (byte y = 0; y <= room_y; y ++) {
        for (byte x = 0; x < room_x; x ++) {
            if (puzzle_room[x][y] == ROOM_GROUND) {
                seekBulb(x, y);
            }
        }
    }
}

/**
 * Function to seek for a bulb from a dark place.
 *
 * @param byte x
 * @param byte y
 * @return void
 */
void Puzzle::seekBulb(byte x, byte y)
{
    if (isBulb(x - 1, y - 1, x, y)) { // ¡ <--
        return;
    }

    if (isBulb(x + 1, y - 1, x ,y)) { // ¡ -->
        return;
    }

    if (isBulb(x - 1, y + 1, x ,y)) { // ! <--
        return;
    }

    if (isBulb(x + 1, y + 1, x, y)) { // ! -->
        return;
    }
}

/**
 * Function to check if this place has a bulb
 *
 * @param byte seek_x
 * @param byte seek_y
 * @param byte x
 * @param byte y
 * @return void
 */
bool Puzzle::isBulb(char seek_x, char seek_y, char x, char y)
{
    bool wall_found = true;

    if (!(seek_x < room_x && seek_y < room_y)) {
        return false;
    }
     
    if (!(seek_x >= 0 && seek_y >= 0)) {
        return false;
    }

    if (room[x][seek_y] != ROOM_WALL) {
        wall_found = false;
    }

    if (wall_found && room[seek_x][y] == ROOM_WALL) {
        return false;
    }

    if (room[seek_x][seek_y] == ROOM_BULB) {
        setBulb(seek_x, seek_y, ROOM_GROUND);
        room[seek_x][seek_y] = ROOM_GROUND;
        room[x][y] = ROOM_BULB;
        return true;
    }

    return false;
}


/**
 * Function to illuminate the dark places
 *
 * @return void
 */
void Puzzle::step_3(void)
{
    for (byte y = 0; y <= room_y; y ++) {
        for (byte x = 0; x < room_x; x ++) {
            if (room[x][y] == ROOM_BULB) {
                setBulb(x, y, ROOM_LIGHT);
            }
        }
    }
}

/**
 * Function to seek a dark place to set a bulb
 *
 * @return void
 */
void Puzzle::step_4(void)
{
    for (byte y = 0; y <= room_y; y ++) {
        for (byte x = 0; x < room_x; x ++) {
            if (room[x][y] == ROOM_GROUND) {
                room[x][y] = ROOM_BULB;
                setBulb(x, y, ROOM_LIGHT);
            }
        }
    }
}


/**
 * Function to set places with illumination or darkness  
 *
 * @param char x
 * @param char y
 * @param ROOM ground
 * @return void
 */
void Puzzle::setBulb(byte x, byte y, ROOM ground)
{
    for (char bulb_y = y + 1; bulb_y <= room_y; bulb_y ++) {
        if (room[x][bulb_y] == ROOM_WALL) {
            break;
        }

        room[x][bulb_y] = ground;
    }

    for (char bulb_y = y - 1; bulb_y >= 0; bulb_y --) {
        if (room[x][bulb_y] == ROOM_WALL) {
            break;
        }

        room[x][bulb_y] = ground;
    }


    for (char bulb_x = x + 1; bulb_x <= room_x; bulb_x ++) {
        if (room[bulb_x][y] == ROOM_WALL) {
            break;
        }

        room[bulb_x][y] = ground;
    }

    for (char bulb_x = x - 1; bulb_x >= 0; bulb_x --) {
        if (room[bulb_x][y] == ROOM_WALL) {
            break;
        }

        room[bulb_x][y] = ground;
    }
}