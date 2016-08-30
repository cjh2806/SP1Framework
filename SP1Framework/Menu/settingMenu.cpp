#include "settingMenu.h"

string display[] = { "        Back        >", "<       Music       >", "< Character  Avatar ", "<       Quit         " };
bool settingSelectionMade = false;
bool musicSetting = true;
bool isStartMenu = true;
char characterAvatar[] = { 1, 2, 3, 4, 5, 6, '!', '@', '#', '$' };
int characterSelection = 7;
char characterSetting = characterAvatar[characterSelection];
int settingSelection = 0;

bool IsSettingSelectionMade() { return settingSelectionMade; }
void IsSettingSelectionMade(bool input) { settingSelectionMade = input; }
int SettingSelection() { return settingSelection; }
bool MusicSelection() { return musicSetting; }
void MusicSelection(bool input) { musicSetting = input; }
char* CharacterSelection() { return &characterSetting; }
bool IsStartMenu() { return isStartMenu; }
void IsStartMenu(bool input) { isStartMenu = input; }

void SettingSelection(int input)
{
	if (settingSelection + input > -1 && settingSelection + input < ((isStartMenu) ? (sizeof(display) / sizeof(display[0]) - 1) : (sizeof(display) / sizeof(display[0]))))
		settingSelection += input;
}

void CharacterSelection(int input)
{
	if (characterSelection + input < sizeof(characterAvatar) && characterSelection + input > -1)
		characterSelection += input;
}

void settingScreen()
{
	switch (settingSelection)
	{
	case SETTINGSELECT::SET_MUSIC: musicSetting ? (resumeMusic()) : (pauseMusic());
		break;
	case SETTINGSELECT::SET_CHARACTER: characterSetting = characterAvatar[characterSelection];
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
	case SETTINGSELECT::SET_CHARACTER: renderCharacterSetting(refCon, c, display[2]);
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

	c.X = (refCon.getConsoleSize().X / 2);

	if (musicSetting)
	{
		c.Y += 6;
		refCon.writeToBuffer(c, (char)31, 0x0F);
		str = " O N ";
		c.Y -= 2;
	}
	else
	{
		c.Y += 2;
		refCon.writeToBuffer(c, (char)30, 0x0F);
		str = "O F F";
		c.Y += 2;
	}

	c.X = c.X - (str.length() / 2);
	refCon.writeToBuffer(c, str, 0x0F);
}

void renderCharacterSetting(Console &refCon, COORD &c, string str)
{
	c = refCon.getConsoleSize();
	c.X = (c.X / 2) - (str.length() / 2);
	c.Y = c.Y / 2;
	refCon.writeToBuffer(c, str + ((isStartMenu) ? "" : ">"), 0x0F);

	c.X = (refCon.getConsoleSize().X / 2);
	c.Y += 6;
	if (characterSelection < sizeof(characterAvatar)-1)
		refCon.writeToBuffer(c, (char)31, 0x0F);

	c.Y -= 4;
	if (characterSelection > 0)
		refCon.writeToBuffer(c, (char)30, 0x0F);

	c.Y += 2;
	refCon.writeToBuffer(c, characterSetting, 0x0F);
}