#include "..\Framework\console.h"
#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using std::getline;

enum MENUSELECT
{
	STARTGAME,
	QUITGAME
};

MENUSELECT IsCurrentState();
void IsCurrentState(MENUSELECT input);
bool IsSelectionMade();
void IsSelectionMade(bool input);
void startMenu(Console &conPtr);