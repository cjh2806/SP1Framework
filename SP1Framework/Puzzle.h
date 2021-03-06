#include "Framework\console.h"
#include "Framework\timer.h"
#include "pattern_storage.h"
#include "riddlestorage.h"
#include "logicstorage.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>

#define LOGIC 15
#define ASCII 97
#define RANGE 26
#define ONE 1
#define LIMIT 100
#define TOTALPATTERNS 10
#define RIDDLES 15
#define LOGIC 15
#define GAME_TOTAL 5
#define ASCIILAST 122

using namespace std;

enum eGame {
	GAME_ONE,
	GAME_TWO,
	GAME_THREE,
	GAME_FOUR,
	GAME_FIVE
};


void initPuzPtr(Console &input);
void initCurrentAnswer();
bool isPuzzleFinished();
void isPuzzleFinished(bool input);
bool GameType();
void GameType(bool input);
void CurrentUserInput(string input);
void transferUserInput(string input);
void AddGuesses();
int AddScore();
void AddScore(int input);
int Lives();
void Lives(int input);
void Puzzle();
void random_alphabet();
void random_number_game();
void random_pattern();
void Riddles();
void logic_game();
void splitString(const string &s, char delim, vector<string> &elems);
vector<string> splitString(const string &s, char delim);
void renderPuzKey(Console &refCon);