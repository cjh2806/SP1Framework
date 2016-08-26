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
void SettingSelection(int input);
bool MusicSelection();
void MusicSelection(bool input);
void optionScreen();
void renderOptionMenu(Console &refCon);
void renderMusicSetting(Console &refCon, COORD &c, string str);