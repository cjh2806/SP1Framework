#include "..\Framework\console.h"
#include <ctime>
#include <string>
#include <stack>


using std::time;
using std::stack;
using std::string;

#define XSIZE 63
#define YSIZE 33

const unsigned int OffsetCoord = 1;

struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

void SetOffsetBuffer(Console &input);
bool IsMazeGenerated();
void IsMazeGenerated(bool input);
bool checkMazeDisplay(COORD input, char aChar, int offX = 0, int offY = 0);
COORD getStartPosition();
void bufferMaze(Console &refCon);
void generateMaze();
void Initialize(Cell Level[][YSIZE]);
void GenerateMaze(Cell Level[][YSIZE], int &posX, int &posY, int &goalX, int &goalY);