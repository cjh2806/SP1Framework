#include "settingMenu.h"

string display[] = { "     back    >", "<   Music   >", "< Work In Progress >", "< Work In Progress  " };
bool optionSelectionMade = false;
bool musicSetting = true;
int optionSelection = 0;

bool IsSettingSelectionMade() { return optionSelectionMade; }
void IsSettingSelectionMade(bool input) { optionSelectionMade = input; }
int SettingSelection() { return optionSelection; }
void SettingSelection(int input) { optionSelection += input; }
bool MusicSelection() { return musicSetting; }
void MusicSelection(bool input) { musicSetting = input; }

void optionScreen()
{
	switch (optionSelection)
	{
		case SETTINGSELECT::SET_MUSIC:
			musicSetting ? (resumeMusic()) : (pauseMusic());
			break;

		case SETTINGSELECT::SET_CHARACTER:
			break;

		case SETTINGSELECT::SET_QUITGAME:
			break;
	}
}

void renderOptionMenu(Console &refCon)
{
	COORD c;

	switch (optionSelection)
	{
		case SETTINGSELECT::SET_BACK:
			c = refCon.getConsoleSize();
			c.X = (c.X / 2) - (display[0].length() / 2);
			c.Y = c.Y / 2;
			refCon.writeToBuffer(c, display[0], 0x0F);
			break;

		case SETTINGSELECT::SET_MUSIC: renderMusicSetting(refCon, c, display[1]);
			break;

		case SETTINGSELECT::SET_CHARACTER:
			c = refCon.getConsoleSize();
			c.X = (c.X / 2) - (display[2].length() / 2);
			c.Y = c.Y / 2;
			refCon.writeToBuffer(c, display[2], 0x0F);
			break;

		case SETTINGSELECT::SET_QUITGAME:
			c = refCon.getConsoleSize();
			c.X = (c.X / 2) - (display[3].length() / 2);
			c.Y = c.Y / 2;
			refCon.writeToBuffer(c, display[3], 0x0F);
			break;
	}
}

void renderMusicSetting(Console &refCon, COORD &c, string str)
{
	c = refCon.getConsoleSize();
	c.X = (c.X / 2) - (str.length() / 2);
	c.Y = c.Y / 2;
	refCon.writeToBuffer(c, str, 0x0F);

	musicSetting ? (str = "\x19  On ") : (str = "\x18  Off");
	c.X = (refCon.getConsoleSize().X / 2) - (str.length() / 2);
	c.Y += 4;
	refCon.writeToBuffer(c, str, 0x0F);
}