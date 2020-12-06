#pragma once
#include "Thread.h"

class Menu : public Thread
{

public:
    Menu(void);
    ~Menu(void);

protected:
    byte menuConsole(void);

private:
    byte menu_x;
    byte menu_y;

    void drawMenu(char *title, char *option_1, char *option_2, char *option_3, char *option_4);
    byte selectOption(byte numOptions, byte &ctrMenu);
    void moveSpot(byte &ctrMenu, byte count);
    void gotoXY(char x, char y);
    byte isKey(void);

};
