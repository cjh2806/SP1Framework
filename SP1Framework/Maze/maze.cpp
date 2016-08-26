#include "maze.h"

bool isMazeGenerated = false;
Cell Level[XSIZE][YSIZE];
COORD StartPosition;
int OffsetBuffer[2];

void SetOffsetBuffer(Console &input)
{
	OffsetBuffer[0] = (input.getConsoleSize().X / 2) - (XSIZE / 2);
	OffsetBuffer[1] = (input.getConsoleSize().Y / 2) - (YSIZE / 2);
}

bool IsMazeGenerated() { return isMazeGenerated; }
void IsMazeGenerated(bool input) { isMazeGenerated = input; }

bool checkMazeDisplay(COORD input, char aChar, int offX, int offY)
{
	input.X = input.X - OffsetBuffer[0] + offX;
	input.Y = input.Y - OffsetBuffer[1] + offY;

	if (Level[input.X][input.Y].display == aChar)
		return true;
	else
		return false;
}

COORD getStartPosition()
{
	StartPosition.X += OffsetBuffer[0];
	StartPosition.Y += OffsetBuffer[1];

	return StartPosition;
}

void bufferMaze(Console &refCon)
{
	COORD c;

	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < YSIZE; j++)
		{
			c.X = i + OffsetBuffer[0];
			c.Y = j + OffsetBuffer[1];

			if (Level[i][j].display == '*')
				refCon.writeToBuffer(c, Level[i][j].display, 0xFF);
			else if (Level[i][j].display == 'E')
				refCon.writeToBuffer(c, Level[i][j].display, 0xDD);
			else
				refCon.writeToBuffer(c, Level[i][j].display, 0x0F);
		}
	}
}

void generateMaze()
{
	int posX = 0;
	int posY = 0;
	int goalX = 0;
	int goalY = 0;

	Initialize(Level);
	GenerateMaze(Level, posX, posY, goalX, goalY);
}

void Initialize(Cell Level[][YSIZE])
{
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < YSIZE; j++)
		{
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}

	for (int i = 1; i < XSIZE - 1; i++)
	{
		for (int j = 1; j < YSIZE - 1; j++)
		{	// Border Cells have fewer accessible walls
			Level[1][j].top_wall = false;
			Level[XSIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][YSIZE - 2].right_wall = false;
		}
	}
}

void GenerateMaze(Cell Level[][YSIZE], int &posX, int &posY, int &goalX, int &goalY)
{
	srand((unsigned)time(NULL));				        					// Pick random start cell
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (XSIZE - 1);						// Generate a random odd number between 1 and YSIZE
	int randomY = ((2 * rand()) + 1) % (YSIZE - 1);						// Generate a random odd number between 1 and YSIZE
	posX = randomX;                       						// Save player's initial X position
	posY = randomY;                      						// Save player's initial Y position
	int visitedCells = 1;
	int totalCells = ((XSIZE - 1) / 2)*((YSIZE - 1) / 2);
	int percent = 0;
	stack<int> back_trackX, back_trackY; 						// Stack is used to trace the reverse path

	Level[randomX][randomY].display = 'S';						// Set S as the start cell
	Level[randomX][randomY].visited = true;						// Set start cell as visited;
	StartPosition = { randomX, randomY };

	while (visitedCells < totalCells)
	{
		if (((Level[randomX - 2][randomY].visited == false) && (Level[randomX][randomY].top_wall == true && Level[randomX - 2][randomY].bot_wall == true)) ||
			((Level[randomX + 2][randomY].visited == false) && (Level[randomX][randomY].bot_wall == true && Level[randomX + 2][randomY].top_wall == true)) ||
			((Level[randomX][randomY - 2].visited == false) && (Level[randomX][randomY].left_wall == true && Level[randomX][randomY - 2].right_wall == true)) ||
			((Level[randomX][randomY + 2].visited == false) && (Level[randomX][randomY].right_wall == true && Level[randomX][randomY + 2].left_wall == true)))
		{
			random = (rand() % 4) + 1;		// Pick a random wall 1-4 to knock down

			// GO UP
			if ((random == 1) && (randomX > 1)) {
				if (Level[randomX - 2][randomY].visited == false) {	// If not visited
					Level[randomX - 1][randomY].display = ' ';	// Delete display
					Level[randomX - 1][randomY].visited = true;	// Mark cell as visited
					Level[randomX][randomY].top_wall = false;	// Knock down wall

					back_trackX.push(randomY); 			// Push X for back track
					back_trackY.push(randomX);			// Push Y for back track

					randomX -= 2;					// Move to next cell
					Level[randomX][randomY].visited = true;		// Mark cell moved to as visited
					Level[randomX][randomY].display = ' ';		// Update path
					Level[randomX][randomY].bot_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}
			// GO DOWN
			else if ((random == 2) && (randomX < XSIZE - 2)) {
				if (Level[randomX + 2][randomY].visited == false) {	// If not visited
					Level[randomX + 1][randomY].display = ' ';	// Delete display
					Level[randomX + 1][randomY].visited = true;	// Mark cell as visited
					Level[randomX][randomY].bot_wall = false;	// Knock down wall

					back_trackX.push(randomY); 			// Push X for back track
					back_trackY.push(randomX);			// Push Y for back track

					randomX += 2;					// Move to next cell
					Level[randomX][randomY].visited = true;		// Mark cell moved to as visited
					Level[randomX][randomY].display = ' ';		// Update path
					Level[randomX][randomY].top_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}
			// GO RIGHT
			else if ((random == 3) && (randomY < YSIZE - 2)) {
				if (Level[randomX][randomY + 2].visited == false) {	// If not visited
					Level[randomX][randomY + 1].display = ' ';	// Delete display
					Level[randomX][randomY + 1].visited = true;	// Mark cell as visited
					Level[randomX][randomY].right_wall = false;	// Knock down wall

					back_trackX.push(randomY); 			// Push X for back track
					back_trackY.push(randomX);			// Push Y for back track

					randomY += 2;					// Move to next cell
					Level[randomX][randomY].visited = true;		// Mark cell moved to as visited
					Level[randomX][randomY].display = ' ';		// Update path
					Level[randomX][randomY].left_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}
			// GO LEFT
			else if ((random == 4) && (randomY > 1)) {
				if (Level[randomX][randomY - 2].visited == false) {	// If not visited
					Level[randomX][randomY - 1].display = ' ';	// Delete display
					Level[randomX][randomY - 1].visited = true;	// Mark cell as visited
					Level[randomX][randomY].left_wall = false;	// Knock down wall

					back_trackX.push(randomY); 			// Push X for back track
					back_trackY.push(randomX);			// Push Y for back track

					randomY -= 2;					// Move to next cell
					Level[randomX][randomY].visited = true;		// Mark cell moved to as visited
					Level[randomX][randomY].display = ' ';		// Update path
					Level[randomX][randomY].right_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}
		}
		else {
			randomY = back_trackX.top();
			back_trackX.pop();

			randomX = back_trackY.top();
			back_trackY.pop();
		}
	}
	goalX = randomY;
	goalY = randomX;
	Level[goalY][goalX].display = 'E';
}