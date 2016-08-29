#include "settingMenu.h"

string display[] = { "     Back    >", "<   Music   >", "< Work In Progress >", "< Work In Progress  " };
bool settingSelectionMade = false;
bool musicSetting = true;
int settingSelection = 0;

bool IsSettingSelectionMade() { return settingSelectionMade; }
void IsSettingSelectionMade(bool input) { settingSelectionMade = input; }
int SettingSelection() { return settingSelection; }
void SettingSelection(int input) { settingSelection += input; }
bool MusicSelection() { return musicSetting; }
void MusicSelection(bool input) { musicSetting = input; }

void settingScreen()
{
	switch (settingSelection)
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

void renderSettingMenu(Console &refCon)
{
	COORD c;

	switch (settingSelection)
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