#include "StdAfx.h"
#include "File.h"

/**
 * The class destruct.
 *
 * @return void
 */
File::File(void)
{
}

/**
 * Function to setup the screen.
 *
 * @return void
 */
File::~File(void)
{
}

/**
 * Function to Load a new map from text file.
 *
 * @param char *load_room
 * @return void
 */
void File::loadLevel(char *load_room)
{
    ifstream Levels;
    char c = ' ';

    Levels.open(load_room);

    if (!Levels.is_open()) {
        MessageBox(0, TEXT("The map file could not be found."), TEXT("Error"), MB_ICONERROR);
        return;
    } 
    
    room_x = 0;
    room_y = 0;

    while (Levels.get(c)) {
        if (c == '\n') {
            if (room_y < ROOM_Y) {
                room_y ++;
            }

            room_x = 0;
        } else {
            room[room_x][room_y] = c;
            if (room_x < ROOM_X) {
                room_x ++;
            }
        }
    }

    drawRoom();
}