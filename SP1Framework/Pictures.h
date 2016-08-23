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
int Picture_Puzzle();
string getFileContents(ifstream&);