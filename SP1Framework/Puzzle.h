#include "Framework\timer.h"
#include <iostream>

#define ASCII 97
#define RANGE 26
#define ONE 1
#define LIMIT 100
#define TOTALPATTERNS 10
#define RIDDLES 15
#define GAME rand()
#define GAME_TOTAL 5

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

int Puzzle();
int random_alphabet();
int random_number_game();
int random_pattern();
int Riddles();
int logic_game();