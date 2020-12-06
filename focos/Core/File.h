#pragma once
#include "Thread.h"
#include <fstream>

class File : public Thread
{

public:
    File(void);
    ~File(void);

protected:
    void loadLevel(char *load_room);

private:
};
