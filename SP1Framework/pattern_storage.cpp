#include "pattern_storage.h"

using namespace std;

string** pattern;

string* getpatterndata()
{
	return (string *)pattern;
}
void pattern_Storage()
{
	int currentrandomanswer = rand() % 101 + 1;
	string Pattern[11][6] = { { to_string(currentrandomanswer), to_string(currentrandomanswer + 2), to_string(currentrandomanswer + 4), to_string(currentrandomanswer + 6), to_string(currentrandomanswer + 8), to_string(currentrandomanswer + 10) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer * 2), to_string(currentrandomanswer * 4), to_string(currentrandomanswer * 6), to_string(currentrandomanswer * 8), to_string(currentrandomanswer * 10) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer + 2), to_string(currentrandomanswer + 6), to_string(currentrandomanswer + 12), to_string(currentrandomanswer + 20), to_string(currentrandomanswer + 30)},
	{ to_string(currentrandomanswer), to_string(currentrandomanswer + 1), to_string(currentrandomanswer - 2), to_string(currentrandomanswer + 3), to_string(currentrandomanswer - 4), to_string(currentrandomanswer + 5) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer - 1), to_string(currentrandomanswer - 2), to_string(currentrandomanswer - 3), to_string(currentrandomanswer - 4), to_string(currentrandomanswer - 5) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer * 2), to_string(currentrandomanswer * 2 + 1), to_string((currentrandomanswer * 2 + 1) * 2), to_string((currentrandomanswer * 2 + 1) * 2 + 1), to_string(((currentrandomanswer * 2 + 1) *  2 + 2) * 2) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer + 8), to_string(currentrandomanswer + 5), to_string(currentrandomanswer + 14), to_string(currentrandomanswer + 12), to_string(currentrandomanswer + 22) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer + 10), to_string(currentrandomanswer + 5), to_string(currentrandomanswer + 25), to_string(currentrandomanswer + 20), to_string(currentrandomanswer + 50) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer * 2), to_string(currentrandomanswer), to_string(currentrandomanswer * 4), to_string(currentrandomanswer * 2), to_string(currentrandomanswer * 16) },
	{ to_string(currentrandomanswer), to_string(currentrandomanswer + 10), to_string(currentrandomanswer + 5), to_string(currentrandomanswer + 25), to_string(currentrandomanswer + 21), to_string(currentrandomanswer + 51) },
	{ "Enter the next number in the pattern", "Try again", "Correct! It only took you ", " times to guess!" } };

	pattern = new string*[11];

	for (int i = 0; i < 11; i++)
	{
		pattern[i] = new string[6];

		for (int j = 0; j < 6; j++)
		{
			pattern[i][j] = Pattern[i][j];
		}
	}
}