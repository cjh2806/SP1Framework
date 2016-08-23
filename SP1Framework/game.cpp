// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>

const double DelayCharBlink = 0.5;
const unsigned int PlayerHealth = 3;

CharState charState;

double t_charBlink;
int playerHealth;
int highscore;
int Score;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(ScreenResoX, ScreenResoY, "Maze Thinker");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Raster Consolas");

	initMenuTitle();

	charState = C_LIT;

	t_charBlink = 0.0;
	playerHealth = PlayerHealth;
	Score = 0;
	highscore = Highscore(Score);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
		case S_SPLASHSCREEN: splashScreen(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_PUZZLE: RunPuzzle();
			break;
		case S_PICTURES: RunPictures();
			break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
	}
	if (Backtogame == true)
	{
		renderFramerate();  // renders debug information, frame rate, elapsed time, etc
		renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	}
}

void splashScreen()
{
	splashScreenWait();
	moveCharacter();
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (IsSelectionMade())
	{
		switch (IsCurrentState())
		{
		case STARTGAME: g_eGameState = S_GAME;
			break;
		case INSTRUCTION: IsSelectionMade(false);
			break;
		case QUITGAME: g_bQuitGame = true;
			break;
		}
	}
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.

	detectMazeEnd();
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP])
    {
		if (IsCurrentState() == QUITGAME)
			IsCurrentState(INSTRUCTION);
		else if (IsCurrentState() == INSTRUCTION)
			IsCurrentState(STARTGAME);

        //Beep(1440, 30);
		if (g_sChar.m_cLocation.Y > OffsetBuffer && getMazeData(g_sChar.m_cLocation.X - OffsetBuffer, g_sChar.m_cLocation.Y - 2).display != '*')
			g_sChar.m_cLocation.Y--;

		bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > OffsetBuffer && getMazeData(g_sChar.m_cLocation.X - 2, g_sChar.m_cLocation.Y - OffsetBuffer).display != '*')
	{
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_DOWN])
	{
		if (IsCurrentState() == STARTGAME)
			IsCurrentState(INSTRUCTION);
		else if (IsCurrentState() == INSTRUCTION)
			IsCurrentState(QUITGAME);

		//Beep(1440, 30);
		if (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 2 && getMazeData(g_sChar.m_cLocation.X - OffsetBuffer, g_sChar.m_cLocation.Y).display != '*')
			g_sChar.m_cLocation.Y++;

		bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 2 && getMazeData(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y - OffsetBuffer).display != '*')
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_SPACE])
	{
		IsSelectionMade(true);

		//g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	startMenu(g_Console);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
	if (!IsMazeGenerated())
	{
		generateMaze();

		g_sChar.m_cLocation.X = getStartPosition().X + OffsetBuffer;
		g_sChar.m_cLocation.Y = getStartPosition().Y + OffsetBuffer;

		IsMazeGenerated(true);
	}

	bufferMaze(g_Console);
}

void renderCharacter()
{
    // Draw the location of the character
	WORD charColor[] = { 0x0A, 0xAA };

	if (t_charBlink < g_dElapsedTime)
	{
		t_charBlink += DelayCharBlink;
		(charState == C_LIT) ? (charState = C_UNLIT) : (charState = C_LIT);
	}

	if (charState)
	{
		colour(charColor[C_UNLIT]);
		g_Console.writeToBuffer(g_sChar.m_cLocation, (char)64, charColor[C_UNLIT]);
	}
	else
	{
		colour(charColor[C_LIT]);
		g_Console.writeToBuffer(g_sChar.m_cLocation, (char)64, charColor[C_LIT]);
	}
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(),0x09);

	ss.str("");
	ss << playerHealth << " Lives";
	c.X = 15;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x09);
	
	if (g_dElapsedTime > 5 && g_dElapsedTime < 5.01)
	{
		playerHealth--;
	}

	// displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x09);

	ScoreDisplay();
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void detectMazeEnd()
{
	if (getMazeData(g_sChar.m_cLocation.X - OffsetBuffer, g_sChar.m_cLocation.Y - OffsetBuffer).display == 'E')
	{
		IsMazeGenerated(false);
		TriggerMiniGames();
		Score += 50;
	}
}
void TriggerMiniGames()
{
	srand(time(NULL));
	int i = rand();
	if (i % 2 == 1)
	{
		g_eGameState = S_PUZZLE;
	}
	else
	{
		g_eGameState = S_PICTURES;
	}
}
void RunPuzzle()
{
	Backtogame = false;
	shutdown();
	g_Console.~Console();
	Score += Puzzle();
	g_eGameState = S_GAME;
	COORD c = { ScreenResoX, ScreenResoY };
	g_Console.initConsole(c, "Maze Thinker");
	t_charBlink = g_dElapsedTime;
}

void RunPictures()
{
	Backtogame = false;
	shutdown();
	g_Console.~Console();
	Score += Picture_Puzzle();
	g_eGameState = S_GAME;
	COORD c = { ScreenResoX, ScreenResoY };
	g_Console.initConsole(c, "Maze Thinker");
	t_charBlink = g_dElapsedTime;
}

void ScoreDisplay()
{
	COORD c;
	std::ostringstream ss;
	ss.str("");
	ss << "Score: " << Score;
	c.X = g_Console.getConsoleSize().X - ss.str().length();
	c.Y = 2;
	g_Console.writeToBuffer(c, ss.str(), 0x0A);

	if (Score > highscore)
		highscore = Highscore(Score);

	ss.str("");
	ss << "Highscore:" << highscore;
	c.X = g_Console.getConsoleSize().X - ss.str().length();;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str(), 0x0A);
}