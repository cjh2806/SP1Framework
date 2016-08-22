#include "maze.h"

bool isMazeGenerated = false;
Cell Level[YSIZE][XSIZE];

bool IsMazeGenerated()
{
	return isMazeGenerated;
}

void IsMazeGenerated(bool input)
{
	isMazeGenerated = input;
}

Cell getMazeData(int a, int b)
{
	return Level[a][b];
}

void bufferMaze(Console &refCon)
{
	COORD c;

	for (int i = 0; i < YSIZE; i++)
	{
		for (int j = 0; j < XSIZE; j++)
		{
			c.X = i + OffsetCoord;
			c.Y = j + OffsetCoord;

			if (Level[i][j].display == '*')
				refCon.writeToBuffer(c, Level[i][j].display, 0xFF);
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

void Initialize(Cell Level[][XSIZE])
{
	for (int i = 0; i < YSIZE; i++)
	{
		for (int j = 0; j < XSIZE; j++)
		{
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}

	for (int i = 1; i < YSIZE - 1; i++)
	{
		for (int j = 1; j < XSIZE - 1; j++)
		{
			// Border Cells have fewer accessible walls
			Level[1][j].top_wall = false;
			Level[YSIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][XSIZE - 2].right_wall = false;
		}
	}
}

void GenerateMaze(Cell Level[][XSIZE], int &posX, int &posY, int &goalX, int &goalY)
{
	srand((unsigned)time(NULL));				        					// Pick random start cell
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (XSIZE - 1);						// Generate a random odd number between 1 and YSIZE
	int randomY = ((2 * rand()) + 1) % (YSIZE - 1);						// Generate a random odd number between 1 and YSIZE
	posX = randomY;                       						// Save player's initial X position
	posY = randomX;                      						// Save player's initial Y position
	int visitedCells = 1;
	int totalCells = ((YSIZE - 1) / 2)*((XSIZE - 1) / 2);
	int percent = 0;
	stack<int> back_trackX, back_trackY; 						// Stack is used to trace the reverse path

	Level[randomY][randomX].display = 'S';						// Set S as the start cell
	Level[randomY][randomX].visited = true;						// Set start cell as visited;

	while (visitedCells < totalCells)
	{
		if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
			((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
			((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
			((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
		{
			random = (rand() % 4) + 1;		// Pick a random wall 1-4 to knock down

			// GO UP
			if ((random == 1) && (randomY > 1)) {
				if (Level[randomY - 2][randomX].visited == false) {	// If not visited
					Level[randomY - 1][randomX].display = ' ';	// Delete display
					Level[randomY - 1][randomX].visited = true;	// Mark cell as visited
					Level[randomY][randomX].top_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomY -= 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].bot_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO DOWN
			else if ((random == 2) && (randomY < YSIZE - 2)) {
				if (Level[randomY + 2][randomX].visited == false) {	// If not visited
					Level[randomY + 1][randomX].display = ' ';	// Delete display
					Level[randomY + 1][randomX].visited = true;	// Mark cell as visited
					Level[randomY][randomX].bot_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomY += 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].top_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO RIGHT
			else if ((random == 3) && (randomX < XSIZE - 2)) {
				if (Level[randomY][randomX + 2].visited == false) {	// If not visited
					Level[randomY][randomX + 1].display = ' ';	// Delete display
					Level[randomY][randomX + 1].visited = true;	// Mark cell as visited
					Level[randomY][randomX].right_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomX += 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].left_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO LEFT
			else if ((random == 4) && (randomX > 1)) {
				if (Level[randomY][randomX - 2].visited == false) {	// If not visited
					Level[randomY][randomX - 1].display = ' ';	// Delete display
					Level[randomY][randomX - 1].visited = true;	// Mark cell as visited
					Level[randomY][randomX].left_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomX -= 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].right_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}
		}
		else {
			randomX = back_trackX.top();
			back_trackX.pop();

			randomY = back_trackY.top();
			back_trackY.pop();
		}
	}

	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = 'E';
}