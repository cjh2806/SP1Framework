#include "startMenu.h"

const WORD color[] = { 0x0F, 0xF0 };
const unsigned int OffsetMenu = 3;

MENUSELECT currentState = STARTGAME;

bool selectionMade = false;
vector<string> menuTitle;
string SelectedMenu[] = { "  - Start Game -  ", " - Instructions - ", "  - Quit  Game -  " };
string UnselectedMenu[] = { "    Start Game    ", "   Instructions   ", "    Quit  Game    " };

MENUSELECT IsCurrentState() { return currentState; }
void IsCurrentState(MENUSELECT input) { currentState = input; }
bool IsSelectionMade() { return selectionMade; }
void IsSelectionMade(bool input) { selectionMade = input; }

void initMenuTitle()
{
	ifstream file("Resources/MenuTitle.txt");
	string line;

	while (getline(file, line))
		menuTitle.push_back(line);

	file.close();
}

void startMenu(Console &refCon)
{
	COORD c = { ((refCon.getConsoleSize().X / 2) - (menuTitle[0].length() / 2)),
		((refCon.getConsoleSize().Y / 2) - menuTitle.size()) };

	for (int i = 0; i < menuTitle.size(); i++, c.Y++)
	{
		colour(color[0]);
		refCon.writeToBuffer(c, menuTitle[i], color[0]);
	}

	c.X = refCon.getConsoleSize().X;

	switch (currentState)
	{
		case STARTGAME:
			c.X = (c.X / 2) - (SelectedMenu[0].length() / 2);
			c.Y += OffsetMenu;
			colour(color[1]);
			refCon.writeToBuffer(c, SelectedMenu[0], color[1]);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[1], color[0]);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[2], color[0]);
			break;

		case INSTRUCTION:
			c.X = (c.X / 2) - (SelectedMenu[0].length() / 2);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[0], color[0]);
			c.Y += OffsetMenu;
			colour(color[1]);
			refCon.writeToBuffer(c, SelectedMenu[1], color[1]);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[2], color[0]);
			break;

		case QUITGAME:
			c.X = (c.X / 2) - (SelectedMenu[0].length() / 2);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[0], color[0]);
			c.Y += OffsetMenu;
			colour(color[0]);
			refCon.writeToBuffer(c, UnselectedMenu[1], color[0]);
			c.Y += OffsetMenu;
			colour(color[1]);
			refCon.writeToBuffer(c, SelectedMenu[2], color[1]);
			break;
	}
	
	string display = "Use 'Up' & 'Down' keys to switch between selections, 'Space Bar' to confirm your selection.";
	c = refCon.getConsoleSize();
	c = { ((c.X / 2) - (display.length() / 2)), (c.Y - 2) };
	refCon.writeToBuffer(c, display, color[0]);
}