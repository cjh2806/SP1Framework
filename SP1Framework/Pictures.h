#include "Framework\console.h"
#include "Framework\timer.h"
#include "picture_storage.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>

#define PICTURES 5

using namespace std;


void initPicCon(Console &input);
void initPictures();
bool isPicturesFinished();
void isPicturesFinished(int input);
void Picture_Puzzle();
void currentUserInput(string input);
string currentUserInput();
void AddScores(int input);
int AddScores();
void TransferUserInput(string input);
void splitString(const string &s, char delim, vector<string> &elems);
vector<string> splitString(const string &s, char delim);
void renderPicKey();