#include "Framework\timer.h"
#include "Framework\console.h"
#include <fstream>
#include <iostream>

#define PICTURES 5

enum ePICTURES{
	PictureONE,
	PictureTWO,
	PictureTHREE,
	PictureFOUR,
	PictureFIVE
};

std::string getFileContents(std::ifstream&);
int Picture_Puzzle();