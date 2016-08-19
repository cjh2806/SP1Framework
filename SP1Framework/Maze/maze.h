#include "..\Framework\console.h"
#include <ctime>
#include <stack>


using std::time;
using std::stack;

#define SIZE 53
#define CSIZE 23

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
void bufferMaze(Console &refCon);
void generateMaze();
void Initialize(Cell Level[][CSIZE]);
void GenerateMaze(Cell Level[][CSIZE], int &posX, int &posY, int &goalX, int &goalY);