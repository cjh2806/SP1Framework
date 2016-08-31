#include "../Framework/console.h"
#include <string>
#include "../sound.h"

using std::string;

enum SETTINGSELECT
{
	SET_BACK,
	SET_MUSIC,
	SET_CHARACTER,
	SET_QUITGAME,
	SET_TOTAL
};

bool IsSettingSelectionMade();
void IsSettingSelectionMade(bool input);
int SettingSelection();
bool MusicSelection();
void MusicSelection(bool input);
char* CharacterSelection();
bool IsStartMenu();
void IsStartMenu(bool input);
void SettingSelection(int input);
void CharacterSelection(int input);
void settingScreen();
void renderSettingMenu(Console &refCon);
void renderMusicSetting(Console &refCon, COORD &c, string str);
void renderCharacterSetting(Console &refCon, COORD &c, string str);
void renderKeys(Console &refCon);