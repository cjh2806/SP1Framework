#include "Highscore.h"
using namespace std;

int Highscore(int Score)
{
	int Highscore;
	ifstream InputFile;
	InputFile.open("highscore.text");
	InputFile >> Highscore;
	InputFile.close();
	if (Score > Highscore)
	{
		ofstream OutputFile;
		OutputFile.open("highscore.text");
		OutputFile << Score << endl;
		OutputFile.close();

	}
	return Highscore;
}