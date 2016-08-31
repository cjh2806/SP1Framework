#include "instructions.h"

string instructionManual[7][7];
int instructSelection = 0;

void InstructSelection(int input)
{
	if (instructSelection + input > -1 && instructSelection + input < 7)
		instructSelection += input;
}

void initInstruction()
{
	ifstream instructionFile("Resources/instructionScreen.txt");

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			getline(instructionFile, instructionManual[i][j]);
		}
	}

	instructionFile.close();
}

void instructions(Console &refCon)
{
	COORD c = refCon.getConsoleSize();
	string display;
	c.X = (c.X / 2) - (instructionManual[0][0].length() / 2);
	c.Y = (c.Y / 2) - 5;

	for (int i = 0; i < 7; i++, c.Y++)
	{
		refCon.writeToBuffer(c, instructionManual[instructSelection][i], 0x0F);
	}

	c.X = refCon.getConsoleSize().X / 2;
	c.Y += 2;

	c.X += 4;
	if (instructSelection < 6)
		refCon.writeToBuffer(c, (char)16, 0x0F);

	c.X -= 8;
	if (instructSelection > 0)
		refCon.writeToBuffer(c, (char)17, 0x0F);

	display = "Back";
	c.X = (refCon.getConsoleSize().X / 2) - 2;
	c.Y += 4;
	refCon.writeToBuffer(c, display, 0x0F);

	display = "Use 'Left' and 'Right' keys to switch the pages. 'Space Bar' to select 'Back'.";
	c.X = (refCon.getConsoleSize().X / 2) - (display.length() / 2);
	c.Y = refCon.getConsoleSize().Y - 2;
	refCon.writeToBuffer(c, display, 0x0F);
}