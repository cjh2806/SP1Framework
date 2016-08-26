#include "startMenu.h"

const WORD color[] = { 0x0F, 0xF0 };
const unsigned int OffsetMenu = 3;

bool startSelectionMade = false;
vector<string> menuTitle;

string MenuSelections[] = { "     Start Game    >", "<   Instructions   >", "<     Settings     >", "<    Quit  Game     " };
int startMenuSelection = 0;

bool IsStartSelectionMade() { return startSelectionMade; }
void IsStartSelectionMade(bool input) { startSelectionMade = input; }
int StartMenuSelection() { return startMenuSelection; }
void StartMenuSelection(int input) { startMenuSelection += input; }

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

	colour(color[0]);

	for (unsigned int i = 0; i < menuTitle.size(); i++, c.Y++)
		refCon.writeToBuffer(c, menuTitle[i], color[0]);

	c.X = refCon.getConsoleSize().X;

	c.X = refCon.getConsoleSize().X;

	c.X = (c.X / 2) - (MenuSelections[0].length() / 2);
	c.Y += OffsetMenu;
	refCon.writeToBuffer(c, MenuSelections[startMenuSelection], color[0]);
	
	string display = "Use 'Left' & 'Right' keys to switch between selections, 'Space Bar' to confirm your selection.";
	c.X = (refCon.getConsoleSize().X / 2) - (display.length() / 2);
	c.Y = refCon.getConsoleSize().Y - 2;
	refCon.writeToBuffer(c, display, color[0]);
}