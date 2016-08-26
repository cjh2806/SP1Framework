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
	Pictures = rand();
	Pictures %= PICTURES;
	IsPictureFinished = false;
}

void Picture_Puzzle()
{
	switch (Pictures)
	{
	case ePICTURES::PictureONE: PictureOne();
		break;
	case ePICTURES::PictureTWO: PictureTwo();
		break;
	case ePICTURES::PictureTHREE: PictureThree();
		break;
	case ePICTURES::PictureFOUR: PictureFour();
		break;
	case ePICTURES::PictureFIVE: PictureFive();
		break;
	}
}

void PictureOne()
{
	COORD c = { 1, 1 };

	ifstream endFile("Transport.txt");
	string PicDisplay[5][13];

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 13; a++)
			getline(endFile, PicDisplay[i][a]);
	}

	for (int i = 0; i < 13; i++)
	{
		if (!getline(endFile, PicDisplay[4][i]))
			PicDisplay[4][i] = "";
	}

	int test = atoi(CurrentUserInput.c_str());
	string test2 = CurrentUserInput;
	for (int i = 0; i < 13; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[/*atoi(CurrentUserInput.c_str()) - 1*/test][i], 0x0F);
	}
	c = { 1, 16 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 17 };
	if (atoi(ConfirmUserInput.c_str()) != 3 && ConfirmUserInput != "")
	{
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Wrong Answer! 4) is a car, 1) is a Plane, 2) is a Train & 3) is a Boat";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (atoi(ConfirmUserInput.c_str()) == 3 && ConfirmUserInput != "")
	{
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Correct";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}

void PictureTwo()
{
	COORD c = { 1, 1 };

	ifstream endFile("Car.txt");
	string PicDisplay[5][26];

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 26; a++)
			getline(endFile, PicDisplay[i][a]);
	}

	for (int i = 0; i < 26; i++)
	{
		if (!getline(endFile, PicDisplay[4][i]))
			PicDisplay[4][i] = "";
	}

	int test = atoi(CurrentUserInput.c_str());
	string test2 = CurrentUserInput;
	for (int i = 0; i < 26; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[/*atoi(CurrentUserInput.c_str()) - 1*/test][i], 0x0F);
	}
	c = { 1, 28 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 29 };
	if (atoi(ConfirmUserInput.c_str()) != 2 && ConfirmUserInput != "")
	{
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Wrong Answer!Toyota has earned the most revenue among the 4 other brands, with Hyundai at 4) coming in at 2nd";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (atoi(ConfirmUserInput.c_str()) == 2 && ConfirmUserInput != "")
	{
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Correct";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}

void PictureThree()
{
	COORD c = { 1, 1 };

	ifstream endFile("Flag.txt");
	string PicDisplay[5][22];

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 22; a++)
			getline(endFile, PicDisplay[i][a]);
	}

	for (int i = 0; i < 22; i++)
	{
		if (!getline(endFile, PicDisplay[4][i]))
			PicDisplay[4][i] = "";
	}

	int test = atoi(CurrentUserInput.c_str());
	string test2 = CurrentUserInput;
	for (int i = 0; i < 22; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[/*atoi(CurrentUserInput.c_str()) - 1*/test][i], 0x0F);
	}

	c = { 1, 24 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 25 };
	if (atoi(ConfirmUserInput.c_str()) != 0 && ConfirmUserInput != "")
	{
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Wrong Answer!1) Vietnam is communist country 2) Japan is not a communist country 3) Turkey is not a communist country 4) Switzerland is not a communist country";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (atoi(ConfirmUserInput.c_str()) == 0 && ConfirmUserInput != "")
	{
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Correct";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}

void PictureFour()
{
	COORD c = { 1, 1 };

	ifstream endFile("Food.txt");
	string PicDisplay[5][27];

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 27; a++)
			getline(endFile, PicDisplay[i][a]);
	}

	for (int i = 0; i < 27; i++)
	{
		if (!getline(endFile, PicDisplay[4][i]))
			PicDisplay[4][i] = "";
	}

	int test = atoi(CurrentUserInput.c_str());
	string test2 = CurrentUserInput;
	for (int i = 0; i < 27; i++, c.Y++)
	{
		ptrPicCon->writeToBuffer(c, PicDisplay[/*atoi(CurrentUserInput.c_str()) - 1*/test][i], 0x0F);
	}
	c = { 1, 29 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 30 };
	if (atoi(ConfirmUserInput.c_str()) != 3 && ConfirmUserInput != "")
	{
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Wrong Answer! 1) Dominos is from the US along with 2) McDonalds, 3) A & W is from Canada while 4) Mos Burger is from Japan";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (atoi(ConfirmUserInput.c_str()) == 3 && ConfirmUserInput != "")
	{
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Correct";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}

void PictureFive()
{
	COORD c = { 1, 1 };

	ifstream endFile("Football.txt");
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
	c = { 1, 31 };
	ptrPicCon->writeToBuffer(c, PicDisplay[4][0], 0x0F);
	c = { 1, 32 };
	if (atoi(ConfirmUserInput.c_str()) != 1 && ConfirmUserInput != "")
	{
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Wrong Answer! 1) Real Madrid is from Spain, 2) Juventus is from Italy, 3) Liverpool is from England and 4) Borussia Dortmund is from Germany";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}
	else if (atoi(ConfirmUserInput.c_str()) == 1 && ConfirmUserInput != "")
	{
		Scores = 50;
		IsPictureFinished = true;
		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			Display = "Correct";
			ptrPicCon->writeToBuffer(c, Display, 0x0F);
			ptrPicCon->flushBufferToConsole();
		}
	}

	endFile.close();
	//c = { 1,45 };
	//ptrPicCon->writeToBuffer(c, CurrentUserInput, 0x0F);
}