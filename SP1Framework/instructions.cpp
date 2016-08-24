#include "instructions.h"

void instructions(Console &refCon)
{
	COORD c = { 10, 6 };

	INSTRUCTIONSELECT currentState = BACK;

	ifstream endFile("Resources/instructionScreen.txt");
	string endTitle;

	while (getline(endFile, endTitle))
	{
		refCon.writeToBuffer(c, endTitle, 0x0F);
		c.Y += 1;
	}

	c = refCon.getConsoleSize();

	switch (currentState)
	{
	case BACK:
		c.X = c.X / 2 - 10;
		c.Y = c.Y / 2 + 6;
		refCon.writeToBuffer(c, " - Back - ", 0xF0);
		break;
	}
}