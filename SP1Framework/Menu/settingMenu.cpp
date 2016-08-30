#include "settingMenu.h"

string display[] = { "     Back    >", "<   Music   >", "< Work In Progress >", "< Work In Progress  " };
bool settingSelectionMade = false;
bool musicSetting = true;
char characterAvatar[] = { 1, 2, 3, 4, 5, 6, '!', '@', '#', '$' };
char characterSetting;
int characterSelection = 7;
int settingSelection = 0;

const int characterSelectionLimit = sizeof(characterAvatar);

bool IsSettingSelectionMade() { return settingSelectionMade; }
void IsSettingSelectionMade(bool input) { settingSelectionMade = input; }
int SettingSelection() { return settingSelection; }
void SettingSelection(int input) { settingSelection += input; }
bool MusicSelection() { return musicSetting; }
void MusicSelection(bool input) { musicSetting = input; }
char* CharacterSelection() { return &characterSetting; }
int CharacterSelectionLimit() { return characterSelectionLimit; }

void CharacterSelection(int input)
{
	if (characterSelection + input < characterSelectionLimit && characterSelection + input > -1)
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

	//char test = (char)16;
	musicSetting ? (str = "\x19  On ") : (str = "\x18  Off");
	c.X = (refCon.getConsoleSize().X / 2) - (str.length() / 2);
	c.Y += 4;
	refCon.writeToBuffer(c, str, 0x0F);
}

void renderCharacterSetting(Console &refCon, COORD &c, string str)
{
	c = refCon.getConsoleSize();
	c.X = (c.X / 2) - (str.length() / 2);
	c.Y = c.Y / 2;
	refCon.writeToBuffer(c, str, 0x0F);

	c.X = (refCon.getConsoleSize().X / 2);
	c.Y += 6;
	if (characterSelection < characterSelectionLimit - 1)
		refCon.writeToBuffer(c, (char)31, 0x0F);

	c.Y -= 4;
	if (characterSelection > 0)
		refCon.writeToBuffer(c, (char)30, 0x0F);

	c.Y += 2;
	refCon.writeToBuffer(c, characterSetting, 0x0F);
}