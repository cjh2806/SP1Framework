#include "quitMenu.h"

bool quitSelection = false;
bool confirmQuit = false;

bool QuitSelection() { return quitSelection; }
void QuitSelection(bool input) { quitSelection = input; }
bool ConfirmQuit() { return confirmQuit; }
void ConfirmQuit(bool input) { confirmQuit = input; }

void renderQuitMenu(Console &refQuitCon)
{
	COORD c = refQuitCon.getConsoleSize();
	string str = "Are You Quiting?";
	c.X = (c.X / 2) - (str.length() / 2);
	c.Y = c.Y / 2;
	refQuitCon.writeToBuffer(c, str, 0x0F);

	c.X = (refQuitCon.getConsoleSize().X / 2) - 4;
	c.Y += 3;
	(quitSelection) ? (refQuitCon.writeToBuffer(c, "  Y E S >", 0x0F)) : (refQuitCon.writeToBuffer(c, "<  N O   ", 0x0F));

	str = "Use 'Left' and 'Right' keys to change selection. 'Space Bar' to confirm selection.";
	c.X = (refQuitCon.getConsoleSize().X / 2) - (str.length() / 2);
	c.Y = refQuitCon.getConsoleSize().Y - 2;
	refQuitCon.writeToBuffer(c, str, 0x0F);
}