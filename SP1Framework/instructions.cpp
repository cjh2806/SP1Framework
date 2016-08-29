#include "instructions.h"

void instructions(Console &refCon)
{
	COORD c = refCon.getConsoleSize();
	c.X = (c.X / 2) - 24;
	c.Y = (c.Y / 2) - 5;

	ifstream endFile("Resources/instructionScreen.txt");
	string endTitle;

	while (getline(endFile, endTitle))
	{
		refCon.writeToBuffer(c, endTitle, 0x0F);
		c.Y += 1;
	}

	c.X = (refCon.getConsoleSize().X / 2) - 2;
	c.Y += 3;
	refCon.writeToBuffer(c, "Back", 0x0F);
}