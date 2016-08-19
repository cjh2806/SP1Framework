#include "startMenu.h"

MENUSELECT currentState = STARTGAME;

bool selectionMade = false;

MENUSELECT IsCurrentState()
{
	return currentState;
}

void IsCurrentState(MENUSELECT input)
{
	currentState = input;
}

bool IsSelectionMade()
{
	return selectionMade;
}

void IsSelectionMade(bool input)
{
	selectionMade = input;
}

void startMenu(Console &refCon)
{
	COORD c = { 3, 6 };

	ifstream file("Resources/MenuTitle.txt");
	string menuTitle;

	while (getline(file, menuTitle))
	{
		refCon.writeToBuffer(c, menuTitle, 0x0F);
		c.Y += 1;
	}

	c = refCon.getConsoleSize();

	switch (currentState)
	{
	case STARTGAME:
		c.X = c.X / 2 - 10;
		c.Y = c.Y / 2 + 6;
		refCon.writeToBuffer(c, " - Start  Game - ", 0xF0);
		c.Y += 2;
		refCon.writeToBuffer(c, "    Quit Game    ", 0x0F);
		break;

	case QUITGAME:
		c.X = c.X / 2 - 10;
		c.Y = c.Y / 2 + 6;
		refCon.writeToBuffer(c, "   Start  Game   ", 0x0F);
		c.Y += 2;
		refCon.writeToBuffer(c, " -  Quit Game  - ", 0xF0);
		break;
	}
}