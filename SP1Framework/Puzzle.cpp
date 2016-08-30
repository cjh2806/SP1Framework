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
bool Gametype;
int Pattern;
int Correct;

void transferUserInput(string input) { confirmUserInput = input; }
bool isPuzzleFinished() { return IsPuzzleFinished; }
void isPuzzleFinished(bool input) { IsPuzzleFinished = input; }
bool GameType() { return Gametype; }
void GameType(bool input) { Gametype = input; }
void CurrentUserInput(string input) { currentUserInput = input; }
void AddGuesses() { Guesses++; }
int AddScore() { return score; }
void AddScore(int input) { score = input; }
void initPuzPtr(Console &input) { ptrPuzCon = &input; }

void initCurrentAnswer()	// Run this function once. It will set the current puzzle and current answer
{
	// Set which minigame to run first
	// Reset any variable that needs reseting in here
	srand((unsigned)time(NULL));
	ptrPuzCon->clearBuffer(0x1F);
	ptrPuzCon->flushBufferToConsole();
	confirmUserInput = "";
	score = 0;
	Minigames = rand();
	Minigames %= GAME_TOTAL;
	IsPuzzleFinished = false;
	Gametype = false;
	Guesses = 0;
	Correct = 0;

	switch (Minigames)	// Checks minigame state and sets the answer according to the minigame state to the currentRandomAnswer variable
	{
	case eGame::GAME_ONE: currentRandomAnswer = rand() % 100 + 1;
		Gametype = true;
		break;
	case eGame::GAME_TWO: currentRandomAnswer = rand() % 26 + 97;
		break;
	case eGame::GAME_THREE:
		Pattern = rand() % TOTALPATTERNS;
		currentRandomAnswer = rand() % 101 + 1;
		Gametype = true;
		break;
	case eGame::GAME_FOUR: Pattern = rand() % LOGIC;
		Gametype = true;
		break;
	case eGame::GAME_FIVE: Pattern = rand() % RIDDLES;
		break;
	}
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

	COORD c;		// Used for display position

	display = "From 1 to " + to_string(LIMIT) + ", guess the number";
	c.X = (ptrPuzCon->getConsoleSize().X / 2) - (display.length() / 2);
	c.Y = (ptrPuzCon->getConsoleSize().Y / 2) - 5;
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c.Y += 3;
	ptrPuzCon->writeToBuffer(c, "Input: " + currentUserInput, 0x0F);// Detect input here

	if (atoi(confirmUserInput.c_str()) > LIMIT)
	{
		display = "Number over the range";
		c.X = (ptrPuzCon->getConsoleSize().X / 2) - (display.length() / 2);
		c.Y += 3;
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) < currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong, gimme a bigger number";
		c.X = (ptrPuzCon->getConsoleSize().X / 2) - (display.length() / 2);
		c.Y += 3;
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) > currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong, gimme a smaller number";
		c.X = (ptrPuzCon->getConsoleSize().X / 2) - (display.length() / 2);
		c.Y += 3;
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
		double delay = 2.0;
		display = "Correct! It only took you " + to_string(Guesses) + " times to guess!";

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void random_alphabet()
{
	COORD c;

	display = "From a to z, guess the letter.";
	c.X = (ptrPuzCon->getConsoleSize().X / 2) - (display.length() / 2);
	c.Y = (ptrPuzCon->getConsoleSize().Y / 2) - 5;
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c.Y += 3;
	ptrPuzCon->writeToBuffer(c, "Input: " + currentUserInput, 0x0F);

	if ((confirmUserInput[0] < ASCII || confirmUserInput[0] > ASCIILAST) && confirmUserInput != "")
	{
		display = "Invalid Character";
		c.Y += 3;
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput[0] < currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong character! The letter is closer to z";
		c.Y += 3;
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (confirmUserInput[0] > currentRandomAnswer && confirmUserInput != "")
	{
		display = "Wrong character! The letter is closer to a";
		c.Y += 3;
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
		double delay = 2.0;
		c.Y += 3;
		display = "Correct! It only took you " + to_string(Guesses) + " times to guess!";

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void random_pattern()
{
	COORD c = ptrPuzCon->getConsoleSize();
	display = "Enter the next number in the pattern";
	c.X = (c.X / 2) - (display.length() / 2);
	c.Y = (c.Y / 2) - 5;
	ptrPuzCon->writeToBuffer(c, display, 0x0F);

	c.Y += 3;
	COORD d = c;

	display = CreatePattern(currentRandomAnswer, Pattern);

	ptrPuzCon->writeToBuffer(d, display + "__", 0x0F);

	c.Y += 3;
	ptrPuzCon->writeToBuffer(c, "Input: " + currentUserInput, 0x0F);

	c.Y += 3;
	if (atoi(confirmUserInput.c_str()) != currentRandomAnswer && confirmUserInput != "")
	{
		display = "Try again";
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
		double delay = 2.0;
		display = "Correct! It only took you " + to_string(Guesses) + " times to guess!";

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void logic_game()
{
	string *logicdata = getlogicdata();
	string **getlogicdata = (string **)logicdata;
	COORD c;
	c.Y = (ptrPuzCon->getConsoleSize().Y / 2) - 7;

	for (int i = 0; i < 5; i++)
	{
		display = getlogicdata[Pattern][i];

		if (i == 0)
		{
			vector<string> tempDisplay = splitString(display, '\n');
			c.X = (ptrPuzCon->getConsoleSize().X / 2) - (tempDisplay[0].length() / 2);
			for (unsigned int i = 0; i < tempDisplay.size(); i++)
			{
				ptrPuzCon->writeToBuffer(c, tempDisplay[i], 0x0F);
				c.Y += 1;
			}
		}
		else
		{
			c.Y += 2;
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}

	c.Y += 3;
	ptrPuzCon->writeToBuffer(c, "Input: " + currentUserInput, 0x0F);
	c.Y += 2;

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
		display = getlogicdata[Pattern][5];
		vector<string> tempDisplay = splitString(display, '\n');
		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			for (unsigned int i = 0; i < tempDisplay.size(); i++)
			{
				ptrPuzCon->writeToBuffer(c, tempDisplay[i], 0x0F);
				c.Y += 1;
			}

			c.Y -= tempDisplay.size();
			ptrPuzCon->flushBufferToConsole();
		}
	}
	else if (confirmUserInput == getlogicdata[Pattern][6] && confirmUserInput != getlogicdata[15][2])
	{
		score = 10;
		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 2.0;
		display = getlogicdata[15][1];

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}
}

void Riddles()
{
	string *riddledata = getriddledata();
	string **getriddledata = (string **)riddledata;
	COORD c;

	display = getriddledata[Pattern][0];
	c.Y = (ptrPuzCon->getConsoleSize().Y / 2) - 5;
	vector<string> tempDisplay = splitString(display, '\n');
	c.X = (ptrPuzCon->getConsoleSize().X / 2) - (tempDisplay[0].length() / 2);
	for (unsigned int i = 0; i < tempDisplay.size(); i++)
	{
		ptrPuzCon->writeToBuffer(c, tempDisplay[i], 0x0F);
		c.Y += 1;
	}
	c.Y += 2;
	ptrPuzCon->writeToBuffer(c, "Input: " + currentUserInput, 0x0F);

	c.Y += 3;

	if (Guesses >= 5)
	{
		//c = { 1, 5 };
		display = getriddledata[Pattern][1];
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (Guesses == 10)
	{
		score = 0;
		IsPuzzleFinished = true;

		clock_t startTime = clock();
		double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		double delay = 3.0;
		display = getriddledata[15][2];

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

			ptrPuzCon->writeToBuffer(c, display, 0x0F);
			ptrPuzCon->flushBufferToConsole();
		}
	}

	c.Y += 3;

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
		double delay = 2.0;
		display = getriddledata[15][0] + to_string(Guesses) + getriddledata[15][1];

		while (duration < delay)
		{
			duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

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

void splitString(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

vector<string> splitString(const string &s, char delim) {
	vector<string> elems;
	splitString(s, delim, elems);
	return elems;
}