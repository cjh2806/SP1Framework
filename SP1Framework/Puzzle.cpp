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
{
	// Set which minigame to run first
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
	case eGame::GAME_THREE: currentRandomAnswer = rand() % 100 + 1;
		Pattern = rand();
		break;
	case eGame::GAME_FOUR: Pattern = rand();
		break;
	case eGame::GAME_FIVE: Pattern = rand();
		break;
	}
	// Reset any variable that needs reseting here
}

void Puzzle()	// Function will be called to run in game.cpp (somewhere that is able to connect to render function)
{
	// These will transfer to initCurrentAnswer(). Some tweaking is required to make it work.

	/////////////////////////////////////

	switch (Minigames)		// For debugging
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
	// 

	COORD c = { 1, 1 };		// Used for display position
	//ptrPuzCon->clearBuffer(0x1F);	// Clears console screen

	display = "From 1 to " + to_string(LIMIT) + ", guess the number";
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 2 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

	// Detect input here

	c = { 1, 10 };	// Change display position

	if (atoi(confirmUserInput.c_str()) > LIMIT)
	{
		//cout << "Number over the range" << endl;
		display = "Number over the range";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
	}
	else if (atoi(confirmUserInput.c_str()) < currentRandomAnswer && confirmUserInput != "")
	{
		//cout << "Wrong, gimme a bigger number" << endl;
		display = "Wrong, gimme a bigger number";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		//Guesses++;
	}
	else if (atoi(confirmUserInput.c_str()) > currentRandomAnswer && confirmUserInput != "")
	{
		//cout << "Wrong, gimme a smaller number" << endl;
		display = "Wrong, gimme a smaller number";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		//Guesses++;
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
	srand(time(NULL));
	COORD c = { 1, 1 };
	display = "Enter the next number in the pattern";
	ptrPuzCon->writeToBuffer(c, display, 0x0F);
	c = { 1, 3 };
	ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
	c = { 1, 2 };
	if (Pattern % TOTALPATTERNS == PatternONE)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 2) + ", " + to_string(currentRandomAnswer + 4) + ", " + to_string(currentRandomAnswer + 6) + ", " + to_string(currentRandomAnswer + 8);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != currentRandomAnswer + 10 && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer + 10 && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternTWO)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer * 2) + ", " + to_string(currentRandomAnswer * 4) + ", " + to_string(currentRandomAnswer * 6) + ", " + to_string(currentRandomAnswer * 8);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != currentRandomAnswer * 10 && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer * 10 && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternTHREE)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 2) + ", " + to_string(currentRandomAnswer + 6) + ", " + to_string(currentRandomAnswer + 12) + ", " + to_string(currentRandomAnswer + 20);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != currentRandomAnswer + 30 && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer + 30 && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternFOUR)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 1) + ", " + to_string(currentRandomAnswer - 2) + ", " + to_string(currentRandomAnswer + 3) + ", " + to_string(currentRandomAnswer - 4) + ", " + to_string(currentRandomAnswer + 5);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != currentRandomAnswer - 6 && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer - 6 && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternFIVE)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer - 1) + ", " + to_string(currentRandomAnswer - 2) + ", " + to_string(currentRandomAnswer - 3) + ", " + to_string(currentRandomAnswer - 4);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != currentRandomAnswer - 5 && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == currentRandomAnswer - 5 && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternSIX)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer * 2) + ", " + to_string((currentRandomAnswer * 2) + 1) + ", " + to_string(((currentRandomAnswer * 2) + 1) * 2) + ", " + to_string((((currentRandomAnswer * 2) + 1) * 2) + 2);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != (((((currentRandomAnswer * 2) + 1) * 2) + 2) * 2) && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == (((((currentRandomAnswer * 2) + 1) * 2) + 2) * 2) && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternSEVEN)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 8) + ", " + to_string(currentRandomAnswer + 5) + ", " + to_string(currentRandomAnswer + 14) + ", " + to_string(currentRandomAnswer + 12);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != (currentRandomAnswer + 22) && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == (currentRandomAnswer + 22) && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternEIGHT)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 10) + ", " + to_string(currentRandomAnswer + 5) + ", " + to_string(currentRandomAnswer + 25) + ", " + to_string(currentRandomAnswer + 15);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != (currentRandomAnswer + 15) && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == (currentRandomAnswer + 15) && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternNINE)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer * 2) + ", " + to_string((currentRandomAnswer * 2) / 2) + ", " + to_string(((currentRandomAnswer * 2) / 2) * 4) + ", " + to_string((((currentRandomAnswer * 2) / 2) * 4) / 2);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != (((((currentRandomAnswer * 2) / 2) * 4) / 2) * 6) && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == (((((currentRandomAnswer * 2) / 2) * 4) / 2) * 6) && confirmUserInput != "")
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
	else if (Pattern % TOTALPATTERNS == PatternTEN)
	{
		display = to_string(currentRandomAnswer) + ", " + to_string(currentRandomAnswer + 10) + ", " + to_string(currentRandomAnswer + 5) + ", " + to_string(currentRandomAnswer + 25) + ", " + to_string(currentRandomAnswer + 21);
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) != (currentRandomAnswer + 51) && confirmUserInput != "")
		{
			display = "Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) == (currentRandomAnswer + 51) && confirmUserInput != "")
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
}
void logic_game()
{
	COORD c = { 1, 1 };
	if (Pattern % LOGIC == LogicONE)
	{
		display = "There are 12 pens on the table, you took 3, how many do you have?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) 12";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) 9";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) 0";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) 3";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 4 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong, you took 3 pens so you have 3 pens";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 4 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicTWO)
	{
		display = "If an electric train is traveling from the east to the west, which direction is the smoke traveling?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) East";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) West";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Up";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) None of the above";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 4 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong, an electric train does not produse smoke";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 4 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicTHREE)
	{
		display = "There are 100 birds on a tree, *BANG*, you shot and killed 1 bird. How many birds are left on the tree?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) 0";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) 100";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) 99";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) 1";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 1 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong, if you fired a gun and killed a bird the other birds will fly away";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 1 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicFOUR)
	{
		display = "If you are in a race, what place are you in if you take over the person who is in second place?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) First";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Second";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Third";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Last";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong, if you overtake second, you are now second";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicFIVE)
	{
		display = "1 is 3, 3 is 5, 5 is 4, 7 is 5. What is 9?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) 5";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) 4";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) 6";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) 3";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong, 9 is 4 as there are 4 letters in 9.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicSIX)
	{
		display = "If LOVE is coded as NRZJ, what is FIRE coded as?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) HLVJ";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) GKUI";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) HKVI";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) GLUJ";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! In the code, the first letter is the second alphabet, the second letter is the third alphabet, the third letter is the fourth alphabet and so on after the corresponding letter in the word.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicSEVEN)
	{
		display = "Banks is related to Money in the same way as Transport is the related to ____?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) Traffic";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Goods";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Speed";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Road";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! Bank deals with the transaction of Money. Likewise Transport deals with the movement of Goods.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicEIGHT)
	{
		display = "Find the odd one out.";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) Vapour";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Mist";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Hailstone";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Fog";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 1 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! All except Vapour are different forms of Precipitation.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 1 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicNINE)
	{
		display = "F is the brother of A, C is the daughter of A, K is the sister of F and G is the brother of C then who is the uncle of G?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) C";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) A";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) K";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) None of the above";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! C & J are childern of A and F is the brother of A.So, F is uncle of C & J. ";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicTEN)
	{
		display = "JE, LH, OL, SQ, ?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) WV";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) WX";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) VW";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) XW";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 4 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! The first letter moves forward 2,3,4 ...... steps. The second letter moves forward 3,4,5 ...... steps.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 4 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicELEVEN)
	{
		display = "Words from an artifical language.agnoscrenia means poisonous spider delanocrenia means poisonous snake agnosdeery means brown spider Which word could mean 'black widow spider'?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) deeryclostagnos";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) agnosdelano";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) agnosvitriblunin";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) trymuttiagnos";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 3 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! In this language, the noun appears first and the adjectives follow. Since agnos means spider and should appear first, choices 1 and 4 can be ruled out. Choice 2 can be ruled out because delano means snake.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 3 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicTWELVE)
	{
		display = "Statements: All fishes are grey in colour.Some fishes are heavy.Conclusions : All heavy fishes are grey in colour.All light fishes are not grey in colour. ? ";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) Only conclusion I and II follows.";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Only conclusion I follows.";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Only conclusion II follows.";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Neither conclusion I or II follows";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! Only conclusion I follows.";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicTHIRTEEN)
	{
		display = "What has a head, tail, is brown and has no legs?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) An Apple";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) An Ant";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) A Penny";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) A Stalk of an Apple";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 3 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! A penny has a head and tail and it's also brown";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 3 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicFOURTEEN)
	{
		display = "Adriana's mom had four kids: Marta, Anna, Justina...";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) Cleopatra";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Adriana";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Annabell";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Christina";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };
		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 2 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! Adriana is her mother's child too";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 2 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
	else if (Pattern % LOGIC == LogicFIFTEEN)
	{
		display = "Imagine you're in a dark room that is perfectly empty with nothing in it. There are no windows or doors. What is the easiest way to escape?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		display = "1) Die";
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 4 };
		display = "2) Wait";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 5 };
		display = "3) Dig a hole in the ground with your hands";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 6 };
		display = "4) Stop imagining";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);

		c = { 1, 7 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);
		c = { 1, 10 };

		if (atoi(confirmUserInput.c_str()) > 4 && confirmUserInput != "")
		{
			display = "Answer Invalid! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
		else if (atoi(confirmUserInput.c_str()) != 4 && confirmUserInput != "")
		{
			score = 0;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 2.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Wrong! Just stop imagining and you will leave the room";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		else if (atoi(confirmUserInput.c_str()) == 4 && confirmUserInput != "")
		{
			score = 10;
			IsPuzzleFinished = true;

			clock_t startTime = clock();
			double duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
			double delay = 1.0;

			while (duration < delay)
			{
				duration = (clock() - startTime) / (double)CLOCKS_PER_SEC;

				display = "Correct!";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
	}
}

void Riddles()
{
	COORD c = { 1, 1 };
	if (Pattern % RIDDLES == RiddleONE)
	{
		display = "What is black when you buy it, red when you use it, and gray when you throw it away?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Tip: The word is 8 characters long and is used as energy for cooking";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "charcoal" && confirmUserInput != "")
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
		else if (confirmUserInput != "charcoal" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleTWO)
	{
		display = "If I drink, I die. If I eat, I am fine. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: The word is normally orange in colour and rhymes with dire";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "fire" && confirmUserInput != "")
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
		else if (confirmUserInput != "fire" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleTHREE)
	{
		display = "I'm the part of the bird that's not in the sky. I can swim in the ocean and yet remain dry. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: Every living creature has this during the day but not at night";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "shadow" && confirmUserInput != "")
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
		else if (confirmUserInput != "shadow" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleFOUR)
	{
		display = "I never was, am always to be, No one ever saw me, nor ever will, And yet I am the confidence of all To live and breathe on this terrestrial ball. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's related to day and it's the future";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "tomorrow" && confirmUserInput != "")
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
		else if (confirmUserInput != "tomorrow" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleFIVE)
	{
		display = "I have many feathers to help me fly. I have a body and head, but I'm not alive. It is your strength which determines how far I go. You can hold me in your hand, but I'm never thrown. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's the name of Superhero Show and it is used with a weapon";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "arrow" && confirmUserInput != "")
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
		else if (confirmUserInput != "arrow" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleSIX)
	{
		display = "If I have it, I don't share it. If I share it, I don't have it. What is it?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's something that you want to hide from other and mostly written inside a diary.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "secret" && confirmUserInput != "")
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
		else if (confirmUserInput != "secret" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleSEVEN)
	{
		display = "A little pool with two layers of wall around it. One white and soft and the other dark and hard, amidst a light brown grassy lawn with an outline of a green grass. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's a fruit and can be made into a drink.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "coconut" && confirmUserInput != "")
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
		else if (confirmUserInput != "coconut" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleEIGHT)
	{
		display = "They come out at night without being called, and are lost in the day without being stolen. What are they?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's related to space.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "stars" && confirmUserInput != "")
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
		else if (confirmUserInput != "stars" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleNINE)
	{
		display = "All about, but cannot be seen, Can be captured, cannot be held, No throat, but can be heard. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's related to the weather.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "wind" && confirmUserInput != "")
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
		else if (confirmUserInput != "wind" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleTEN)
	{
		display = "I am a box that holds keys without locks, yet they can unlock your soul. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It's related to music.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "piano" && confirmUserInput != "")
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
		else if (confirmUserInput != "piano" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleELEVEN)
	{
		display = "You are in a cabin and it is pitch black. You have one match on you. Which do you light first, the newspaper, the lamp, the candle or the fire?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: What starts the fire.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "match" && confirmUserInput != "")
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
		else if (confirmUserInput != "match" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleTWELVE)
	{
		display = "Which word, if pronounced right, is wrong, but if pronounced wrong is right?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: The answer is in the riddle.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "wrong" && confirmUserInput != "")
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
		else if (confirmUserInput != "wrong" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleTHIRTEEN)
	{
		display = "Which word is the odd one out : First Second Third Forth Fifth Sixth Seventh Eighth";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: 4";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if ((confirmUserInput == "forth" || confirmUserInput == "4") && confirmUserInput != "")
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
		else if ((confirmUserInput != "forth" || confirmUserInput != "4") && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleFOURTEEN)
	{
		display = "A farmer has 17 sheep and all but 9 die. How many are left?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: All died except 9";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if ((confirmUserInput == "nine" || confirmUserInput == "9") && confirmUserInput != "")
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
		else if ((confirmUserInput != "nine" || confirmUserInput != "9") && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
	else if (Pattern % RIDDLES == RiddleFIFTEEN)
	{
		display = "You will always find me in the past. I can be created in the present, But the future can never taint me. What am I?";
		ptrPuzCon->writeToBuffer(c, display, 0x0F);
		c = { 1, 3 };
		ptrPuzCon->writeToBuffer(c, currentUserInput, 0x0F);

		COORD c = { 1, 6 };
		if (Guesses >= 5)
		{
			COORD c = { 1, 5 };
			display = "Hint: It 'was' a phase in time.";
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

				display = "That's too bad! You used up all of your ten attempts";
				ptrPuzCon->writeToBuffer(c, display, 0x0F);
				ptrPuzCon->flushBufferToConsole();
			}
		}
		if (confirmUserInput == "history" && confirmUserInput != "")
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
		else if (confirmUserInput != "history" && confirmUserInput != "")
		{
			display = "Wrong Answer! Try again";
			ptrPuzCon->writeToBuffer(c, display, 0x0F);
		}
	}
}