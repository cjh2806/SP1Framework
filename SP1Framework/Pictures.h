#include "Framework\console.h"
#include "Framework\timer.h"
#include <fstream>
#include <iostream>
#include <ctime>

#define PICTURES 5

using namespace std;

enum ePICTURES{
	PictureONE,
	PictureTWO,
	PictureTHREE,
	PictureFOUR,
	PictureFIVE
};

void initPicCon(Console &input);
void initPictures();
bool isPicturesFinished();
void isPicturesFinished(int input);
void Picture_Puzzle();
void PictureOne();
void currentUserInput(string input);
string currentUserInput();
void AddScores(int input);
int AddScores();
void TransferUserInput(string input);

void PictureTwo();
void PictureThree();
void PictureFour();
void PictureFive();