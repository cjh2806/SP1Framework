#include "endMenu.h"

void endMenu(Console &refCon)
{
	COORD c = { 10, 6 };

	ifstream endFile("Resources/endMenu.txt");
	string endTitle;

	while (getline(endFile, endTitle))
	{
		refCon.writeToBuffer(c, endTitle, 0x0F);
		c.Y += 1;
	}

	c = refCon.getConsoleSize();

	c.X = c.X / 2 - 10;
	c.Y = c.Y / 2 + 6;
	refCon.writeToBuffer(c, " -  Press ESC to quit  - ", 0xF0);
}