#include "Puzzle.h"

Console* ptrPuzCon;
double* ptrPuzElapsedTime;
string display;

string confirmUserInput;
string currentUserInput;
int currentRandomAnswer;
int score;
int Minigames;
int Guesses;
bool IsPuzzleFinished;
int Pattern;
int Correct;

void transferUserInput(string input) { confirmUserInput = input; }	// Transfer userInput from game.cpp to here
bool isPuzzleFinished() { return IsPuzzleFinished; }
void isPuzzleFinished(bool input) { IsPuzzleFinished = input; }
void CurrentUserInput(string input) { currentUserInput = input; }
void AddGuesses() { Guesses++; }
int AddScore() { return score; }
void AddScore(int input) { score = input; }

void initPuzPtr(Console &input)
{
	ptrPuzCon = &input;
}

void initCurrentAnswer()	// Run this function once. It will set the current puzzle and current answer
{	// Set which minigame to run first
	srand(time(NULL));
	ptrPuzCon->clearBuffer(0x1F);
	ptrPuzCon->flushBufferToConsole();
	confirmUserInput = "";
	score = 0;
	Minigames = rand();
	Minigames %= GAME_TOTAL;
	IsPuzzleFinished = false;
	Guesses = 0;
	Correct = 0;
	switch (Minigames)	// Checks minigame state and sets the answer according to the minigame state to the currentRandomAnswer variable
	{
	case eGame::GAME_ONE: currentRandomAnswer = rand() % 100 + 1;
		break;
	case eGame::GAME_TWO: currentRandomAnswer = rand() % 26 + 97;
		break;
	case eGame::GAME_THREE: Pattern = rand() % TOTALPATTERNS;
		break;
	case eGame::GAME_FOUR: Pattern = rand() % LOGIC;
		break;
	case eGame::GAME_FIVE: Pattern = rand() % RIDDLES;
		break;
	}// Reset any variable that needs reseting here
}

void Puzzle()	// Function will be called to run in game.cpp (somewhere that is able to connect to render function)
{
	switch (Minigames) // These will transfer to initCurrentAnswer(). Some tweaking is required to make it work.
	{
	case eGame::GAME_ONE: random_number_game();
		break;
	case eGame::GAME_TWO: random_alphabet();
		break;
	case eGame::GAME_THREE: random_pattern();
		break;
	case eGame::GAME_FOUR: logic_game();
		break;
	case eGame::GAME_FIVE: Riddles();
		break;
	}
}

void random_number_game()
{
	// Conditions in this function have to check against confirmUserInput

	COORD c = { 1, 1 };		// Used for display position

	display = "From 1 to " + to_string(LIMIT) + ", guess the number";
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 2 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);// Detect input here

	c = { 1, 10 };	// Change display position

	if (atoi(confirmUserInput.c_str()) > LIMIT)
	{
		display = "Number over the range";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) < currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong, gimme a bigger number";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) > currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong, gimme a smaller number";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer && confirmUserInput != "")
	{
		if (Guesses < 5)
			score += 100;
		else if (Guesses < 10)
			score += 50;
		else
			score += 0;

		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = "Correct! It only took you " + to_string(Guesses) + " times to guess!";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void random_alphabet()
{
	COORD c = { 1, 1 };

	display = "From a to z, guess the letter.";
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 2 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

	c = { 1, 10 };

	if ((confirmUserInput[0] < ASCII || confirmUserInput[0] > ASCIILAST) && confirmUserInput != "")
	{
		display = "Invalid Character";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput[0] < currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong character! The letter is closer to z";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput[0] > currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong character! The letter is closer to a";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput[0] == currentRandomAnswer && confirmUserInput != "")
	{
		if (Guesses < 5)
			score += 100;
		else if (Guesses < 10)
			score += 50;
		else
			score += 0;

		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = "Correct! It only took you " + to_string(Guesses) + " times to guess!";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}
void random_pattern()
{
	string *patterndata = getpatterndata();
	string **getpatterndata = (string **)patterndata;
	COORD c = { 1, 1 };
	display = getpatterndata[10][0];
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 3 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
	for (int i = 0, spacing = 0; i < 5; i++, spacing += 4)
	{
		c = { spacing + 1, 2 };
		display = getpatterndata[Pattern][i];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	c = { 1, 10 };
	if ((confirmUserInput) != getpatterndata[Pattern][5] && confirmUserInput != "")
	{
		display = getpatterndata[10][1];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput == getpatterndata[Pattern][5] && confirmUserInput != "")
	{
		if (Guesses < 5)
			score += 100;
		else if (Guesses < 10)
			score += 50;
		else
			score += 0;

		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = getpatterndata[10][2] + to_string(Guesses) + getpatterndata[10][3];
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}
void logic_game()
{
	string *logicdata = getlogicdata();
	string **getlogicdata = (string **)logicdata;
	COORD c = { 1, 1 };

	for (int i = 0, spacing = 0; i < 5; i++, spacing += 2)
	{
		display = getlogicdata[Pattern][i];
		c = { 1, 1 + spacing };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}

	c = { 1, 12 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
	c = { 1, 15 };
	if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != getlogicdata[15][2])
	{
		display = getlogicdata[15][0];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput != getlogicdata[Pattern][6] && confirmUserInput != getlogicdata[15][2])
	{
		score = 0;
		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 2.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = getlogicdata[Pattern][5];
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
	else if (confirmUserInput == getlogicdata[Pattern][6] && confirmUserInput != getlogicdata[15][2])
	{
		score = 10;
		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = getlogicdata[15][1];
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void Riddles()
{
	string *riddledata = getriddledata();
	string **getriddledata = (string **)riddledata;
	COORD c = { 1, 1 };

	display = getriddledata[Pattern][0];
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 3 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

	c = { 1, 6 };
	if (Guesses >= 5)
	{
		c = { 1, 5 };
		display = getriddledata[Pattern][1];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (Guesses == 10)
	{
		score = 0;
		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = getriddledata[15][2];
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
	if (confirmUserInput == getriddledata[Pattern][2] && confirmUserInput != getriddledata[Pattern][3])
	{
		if (Guesses < 5)
			score += 100;
		else if (Guesses < 10)
			score += 50;
		else
			score += 0;

		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 1.0;

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			display = getriddledata[15][0] + to_string(Guesses) + getriddledata[15][1];
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
	else if (confirmUserInput != getriddledata[Pattern][2] && confirmUserInput != getriddledata[Pattern][3])
	{
		display = getriddledata[15][3];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
}