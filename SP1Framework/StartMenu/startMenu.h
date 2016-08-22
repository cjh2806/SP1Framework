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
	STARTGAME,
	INSTRUCTION,
	QUITGAME
};

MENUSELECT IsCurrentState();
void IsCurrentState(MENUSELECT input);
bool IsSelectionMade();
void IsSelectionMade(bool input);
void initMenuTitle();
void startMenu(Console &conPtr);