#include "Highscore.h"
using namespace std;

int Highscore(int Score)
{
	int Highscore;
	ifstream InputFile;
	InputFile.open("highscore.txt");
	InputFile >> Highscore;
	InputFile.close();
	if (Score > Highscore)
	{
		ofstream OutputFile;
		OutputFile.open("highscore.txt");
		OutputFile << Score << endl;
		OutputFile.close();

	}
	return Highscore;
}