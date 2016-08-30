#include "pattern_storage.h"

using namespace std;

int currentrandomanswer;
int currentrandompattern;

const int Pattern2[10][5] = { { 2, 4, 6, 8, 10 },
{ 2, 4, 6, 8, 10 },
{ 2, 6, 12, 20, 30 },
{ 1, 2, 3, 4, 5 },
{ 1, 2, 3, 4, 5 },
{ 2, 3, 4, 5, 6 },
{ 8, 5, 14, 12, 22 },
{ 10, 5, 25, 20, 50 },
{ 2, 1, 4, 2, 16 },
{ 10, 5, 25, 21, 51 } };

const char PatternOperator[10][5] = { { '+', '+', '+', '+', '+' },
{ '*', '*', '*', '*', '*' },
{ '+', '+', '+', '+', '+' },
{ '+', '-', '+', '-', '+' },
{ '-', '-', '-', '-', '-' },
{ '*', '*', '*', '*', '*' },
{ '+', '+', '+', '+', '+' },
{ '+', '+', '+', '+', '+' },
{ '*', '*', '*', '*', '*' },
{ '+', '+', '+', '+', '+' } };

string CreatePattern(int input, int pattern)
{
	string PatternOutput = "";
	currentrandomanswer = input;
	currentrandompattern = pattern;

	for (int i = 4; i >= 0; i--)
	{
		switch (PatternOperator[currentrandompattern][i])
		{
		case '+': PatternOutput += to_string(currentrandomanswer + Pattern2[currentrandompattern][i]) + ", ";
			break;
		case '*':  PatternOutput += to_string(currentrandomanswer * Pattern2[currentrandompattern][i]) + ", ";
			break;
		case '-': PatternOutput += to_string(currentrandomanswer - Pattern2[currentrandompattern][i]) + ", ";
			break;
		}
	}
	return PatternOutput;
}
