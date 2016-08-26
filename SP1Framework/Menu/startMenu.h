#include "..\Framework\console.h"
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::getline;
using std::vector;

enum MENUSELECT
{
	M_STARTGAME,
	M_INSTRUCTION,
	M_SETTING,
	M_QUITGAME,
	M_TOTAL
};

bool IsStartSelectionMade();
void IsStartSelectionMade(bool input);
int StartMenuSelection();
void StartMenuSelection(int input);
void initMenuTitle();
void startMenu(Console &conPtr);