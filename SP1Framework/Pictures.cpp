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
	srand(time(NULL));
	ConfirmUserInput = "";
	CurrentUserInput = "0";
	Scores = 0;
	Pictures = rand() % PICTURES;
	IsPictureFinished = false;
}

void Picture_Puzzle()
{
	COORD c = { 1, 1 };
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

	int test = atoi(CurrentUserInput.c_str());
	string test2 = CurrentUserInput;
	for (int i = 0; i < 29; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[/*atoi(CurrentUserInput.c_str()) - 1*/test][i], 0x0F);
	}
	c = { 1, 34 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 35 };
	if (ConfirmUserInput != getpicturedata[Pictures][2] && ConfirmUserInput != "")
	{
		c.X = (ptrPicCon->getConsoleSize().X / 2) - 35;
		Scores = 0;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 2.0;
		Display = getpicturedata[Pictures][1];
		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			vector<string> tempDisplay = splitString(Display, '\n');
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
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = getpicturedata[Pictures][3];
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}