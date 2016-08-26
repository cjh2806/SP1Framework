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
	M_OPTION,
	M_QUITGAME
};

MENUSELECT IsCurrentState();
void IsCurrentState(MENUSELECT input);
bool IsSelectionMade();
void IsSelectionMade(bool input);
void initMenuTitle();
void startMenu(Console &conPtr);