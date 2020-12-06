#pragma once
#include "File.h"

class Menu : public File
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
    byte isKey(void);

};
