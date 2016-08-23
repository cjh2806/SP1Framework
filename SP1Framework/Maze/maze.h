#include "..\Framework\console.h"
#include <ctime>
#include <stack>


using std::time;
using std::stack;

#define YSIZE 53
#define XSIZE 23

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
void Initialize(Cell Level[][XSIZE]);
void GenerateMaze(Cell Level[][XSIZE], int &posX, int &posY, int &goalX, int &goalY);