#include "Framework\console.h"
#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

#define LOGIC 3
#define ASCII 97
#define RANGE 26
#define ONE 1
#define LIMIT 100
#define TOTALPATTERNS 10
#define RIDDLES 15
#define GAME rand()
#define GAME_TOTAL 5

using namespace std;

enum eGame {
	GAME_ONE,
	GAME_TWO,
	GAME_THREE,
	GAME_FOUR,
	GAME_FIVE
};

enum ePatterns {
	PatternONE,
	PatternTWO,
	PatternTHREE,
	PatternFOUR,
	PatternFIVE,
	PatternSIX,
	PatternSEVEN,
	PatternEIGHT,
	PatternNINE,
	PatternTEN
};

enum eLogic{
	LogicONE,
	LogicTWO,
	LogicTHREE
};

enum eRiddles{
	RiddleONE,
	RiddleTWO,
	RiddleTHREE,
	RiddleFOUR,
	RiddleFIVE,
	RiddleSIX,
	RiddleSEVEN,
	RiddleEIGHT,
	RiddleNINE,
	RiddleTEN,
	RiddleELEVEN,
	RiddleTWELVE,
	RiddleTHIRTEEN,
	RiddleFOURTEEN,
	RiddleFIFTEEN
};
void initPuzPtr(Console &input);
void initCurrentAnswer();
bool isPuzzleFinished();
void isPuzzleFinished(bool input);
void CurrentUserInput(string input);
void transferUserInput(string input);
void AddGuesses();
int AddScore();
void AddScore(int input);
void Puzzle();
int random_alphabet();
void random_number_game();
int random_pattern();
int Riddles();
int logic_game();