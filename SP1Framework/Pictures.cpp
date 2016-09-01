#include "Pictures.h"

Console* ptrPicCon;
double* ptrPicElapsedTime;
string Display;
string Display2;

string ConfirmUserInput;
string CurrentUserInput;

int Scores;
int Pictures;
bool IsPictureFinished;


void initPicCon(Console &input) { ptrPicCon = &input; }
void TransferUserInput(string input) { ConfirmUserInput = input; }	// Transfer userInput from game.cpp to here
bool isPicturesFinished() { return IsPictureFinished; }
void isPicturesFinished(bool input) { IsPictureFinished = input; }
string currentUserInput() { return CurrentUserInput; }
void currentUserInput(string input) { CurrentUserInput = input; }
int AddScores() { return Scores; }
void AddScores(int input) { Scores = input; }


void initPictures()	// Run this function once. It will set the current puzzle and current answer
{
	// Set which minigame to run first
	srand((unsigned)time(NULL));
	ConfirmUserInput = "";
	CurrentUserInput = "0";
	Scores = 0;
	Pictures = rand() % PICTURES;
	IsPictureFinished = false;
}

void Picture_Puzzle()
{
	COORD c = { 1, 6 };
	string *Picturedata = getPicturedata();
	string **getpicturedata = (string **)Picturedata;
	ifstream endFile(getpicturedata[Pictures][0]);
	string PicDisplay[5][29];

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 29; a++)
			getline(endFile, PicDisplay[i][a]);
	}

	for (int i = 0; i < 29; i++)
	{
		if (!getline(endFile, PicDisplay[4][i]))
			PicDisplay[4][i] = "";
	}

	int curSelection = atoi(CurrentUserInput.c_str());

	for (int i = 0; i < 29; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[curSelection][i], 0x0F);
	}

	c.Y += 2;
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c.Y += 2;
	renderPicKey();

	if (ConfirmUserInput != getpicturedata[Pictures][2] && ConfirmUserInput != "")
	{
		c.X = (ptrPicCon->getConsoleSize().X / 2) - 35;
		Scores = 0;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 2.0;
		Display = getpicturedata[Pictures][1];
		vector<string> tempDisplay = splitString(Display, '\n');

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			for (unsigned int i = 0; i < tempDisplay.size(); i++)
			{
				ptrPicCon->writeToBuffer(c, tempDisplay[i], 0x0F);
				c.Y += 1;
			}

			c.Y -= tempDisplay.size();
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (ConfirmUserInput == getpicturedata[Pictures][2] && ConfirmUserInput != "")
	{
		c.X = (ptrPicCon->getConsoleSize().X / 2) - 7;
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 2.0;
		Display = getpicturedata[Pictures][3];

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
}

void renderPicKey()
{
	COORD c;
	string str = "Use 'Left' and 'Right' keys to change selections, 'Enter' to confirm selection.";
	c.X = (ptrPicCon->getConsoleSize().X / 2) - (str.length() / 2 );
	c.Y = ptrPicCon->getConsoleSize().Y - 2;
	ptrPicCon->writeToBuffer(c, str, 0x0F);
}