// focos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Core/Room.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Room *room = new Room();
	room->runConsole();
	
	return 0;
}
