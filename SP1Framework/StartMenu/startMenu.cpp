#include "startMenu.h"

const WORD color[] = { 0x0F, 0xF0 };
const unsigned int TitlePosition[] = { 3, 6 };
const unsigned int OffsetMenuPosition[] = { 10, 6 };
const unsigned int OffsetMenu = 2;

MENUSELECT currentState = STARTGAME;

bool selectionMade = false;
vector<string> menuTitle;

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

void initMenuTitle()
{
	ifstream file("Resources/MenuTitle.txt");
	string line;

	while (getline(file, line))
		menuTitle.push_back(line);
}

void startMenu(Console &refCon)
{
	COORD c = { TitlePosition[0], TitlePosition[1] };


	for (int i = 0; i < menuTitle.size(); i++, c.Y++)
	{
		colour(color[0]);
		refCon.writeToBuffer(c, menuTitle[i], color[0]);
	}

	c = refCon.getConsoleSize();

	switch (currentState)
	{
	case STARTGAME:
		c.X = c.X / 2 - OffsetMenuPosition[0];
		c.Y = c.Y / 2 + OffsetMenuPosition[1];
		colour(color[1]);
		refCon.writeToBuffer(c, "  - Start Game -  ", color[1]);
		c.Y += OffsetMenu;
		colour(color[0]);
		refCon.writeToBuffer(c, "   Instructions   ", color[0]);
		c.Y += OffsetMenu;
		colour(color[0]);
		refCon.writeToBuffer(c, "    Quit  Game    ", color[0]);
		break;

	case INSTRUCTION:
		c.X = c.X / 2 - OffsetMenuPosition[0];
		c.Y = c.Y / 2 + OffsetMenuPosition[1];
		colour(color[0]);
		refCon.writeToBuffer(c, "    Start Game    ", color[0]);
		c.Y += OffsetMenu;
		colour(color[1]);
		refCon.writeToBuffer(c, " - Instructions - ", color[1]);
		c.Y += OffsetMenu;
		colour(color[0]);
		refCon.writeToBuffer(c, "    Quit  Game    ", color[0]);
		break;

	case QUITGAME:
		c.X = c.X / 2 - OffsetMenuPosition[0];
		c.Y = c.Y / 2 + OffsetMenuPosition[1];
		colour(color[0]);
		refCon.writeToBuffer(c, "    Start Game    ", color[0]);
		c.Y += OffsetMenu;
		colour(color[0]);
		refCon.writeToBuffer(c, "   Instructions   ", color[0]);
		c.Y += OffsetMenu;
		colour(color[1]);
		refCon.writeToBuffer(c, "  - Quit  Game -  ", color[1]);
		break;
	}
}