#include "Framework\console.h"
#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using std::getline;

enum INSTRUCTIONSELECT
{
	BACK
};

void instructions(Console &refCon);