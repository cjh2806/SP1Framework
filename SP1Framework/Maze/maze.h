#include "..\Framework\console.h"
#include <ctime>
#include <stack>


using std::time;
using std::stack;

#define YSIZE 53
#define XSIZE 23

const unsigned int OffsetCoord = 1;
const unsigned int OffsetBuffer = 1;

struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

bool IsMazeGenerated();
void IsMazeGenerated(bool input);
Cell getMazeData(int a, int b);
COORD getStartPosition();
void bufferMaze(Console &refCon);
void generateMaze();
void Initialize(Cell Level[][XSIZE]);
void GenerateMaze(Cell Level[][XSIZE], int &posX, int &posY, int &goalX, int &goalY);