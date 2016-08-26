// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include <MMSystem.h>
#pragma comment(lib, "Winmm.lib")

const WORD bgColor = 0x0F;
const double DelayCharBlink = 0.5;
const unsigned int PlayerHealth = 3;
const char CharacterType = 64;

CharState charState;

bool InitPictures;
bool InitPuzzle;
double t_charBlink;
int playerHealth;
int highscore;
int Score;
int timer;
string Input;
double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(ScreenReso, "Maze Thinker");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
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
	Input = "";
	SetOffsetBuffer(g_Console);

	charState = C_LIT;
	t_charBlink = g_dElapsedTime;
	playerHealth = PlayerHealth;
	Score = 0;
	highscore = Highscore(Score);

	initPicCon(g_Console);
	initPuzPtr(g_Console);

	music();
	riddlestorage();
	logicstorage();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
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
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_BACK] = isKeyPressed(VK_BACK);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
}

void Alphabets()
{
	g_abKeyPressed[K_A] = isKeyPressed(VK_A);
	g_abKeyPressed[K_B] = isKeyPressed(VK_B);
	g_abKeyPressed[K_C] = isKeyPressed(VK_C);
	g_abKeyPressed[K_D] = isKeyPressed(VK_D);
	g_abKeyPressed[K_E] = isKeyPressed(VK_E);
	g_abKeyPressed[K_F] = isKeyPressed(VK_F);
	g_abKeyPressed[K_G] = isKeyPressed(VK_G);
	g_abKeyPressed[K_H] = isKeyPressed(VK_H);
	g_abKeyPressed[K_I] = isKeyPressed(VK_I);
	g_abKeyPressed[K_J] = isKeyPressed(VK_J);
	g_abKeyPressed[K_K] = isKeyPressed(VK_K);
	g_abKeyPressed[K_L] = isKeyPressed(VK_L);
	g_abKeyPressed[K_M] = isKeyPressed(VK_M);
	g_abKeyPressed[K_N] = isKeyPressed(VK_N);
	g_abKeyPressed[K_O] = isKeyPressed(VK_O);
	g_abKeyPressed[K_P] = isKeyPressed(VK_P);
	g_abKeyPressed[K_Q] = isKeyPressed(VK_Q);
	g_abKeyPressed[K_R] = isKeyPressed(VK_R);
	g_abKeyPressed[K_S] = isKeyPressed(VK_S);
	g_abKeyPressed[K_T] = isKeyPressed(VK_T);
	g_abKeyPressed[K_U] = isKeyPressed(VK_U);
	g_abKeyPressed[K_V] = isKeyPressed(VK_V);
	g_abKeyPressed[K_W] = isKeyPressed(VK_W);
	g_abKeyPressed[K_X] = isKeyPressed(VK_X);
	g_abKeyPressed[K_Y] = isKeyPressed(VK_Y);
	g_abKeyPressed[K_Z] = isKeyPressed(VK_Z);
}

void numbers(void)
{
	g_abKeyPressed[K_1] = isKeyPressed(VK_1);
	g_abKeyPressed[K_2] = isKeyPressed(VK_2);
	g_abKeyPressed[K_3] = isKeyPressed(VK_3);
	g_abKeyPressed[K_4] = isKeyPressed(VK_4);
	g_abKeyPressed[K_5] = isKeyPressed(VK_5);
	g_abKeyPressed[K_6] = isKeyPressed(VK_6);
	g_abKeyPressed[K_7] = isKeyPressed(VK_7);
	g_abKeyPressed[K_8] = isKeyPressed(VK_8);
	g_abKeyPressed[K_9] = isKeyPressed(VK_9);
	g_abKeyPressed[K_0] = isKeyPressed(VK_0);
	g_abKeyPressed[K_NUM0] = isKeyPressed(VK_NUMPAD0);
	g_abKeyPressed[K_NUM1] = isKeyPressed(VK_NUMPAD1);
	g_abKeyPressed[K_NUM2] = isKeyPressed(VK_NUMPAD2);
	g_abKeyPressed[K_NUM3] = isKeyPressed(VK_NUMPAD3);
	g_abKeyPressed[K_NUM4] = isKeyPressed(VK_NUMPAD4);
	g_abKeyPressed[K_NUM5] = isKeyPressed(VK_NUMPAD5);
	g_abKeyPressed[K_NUM6] = isKeyPressed(VK_NUMPAD6);
	g_abKeyPressed[K_NUM7] = isKeyPressed(VK_NUMPAD7);
	g_abKeyPressed[K_NUM8] = isKeyPressed(VK_NUMPAD8);
	g_abKeyPressed[K_NUM9] = isKeyPressed(VK_NUMPAD9);
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
	case S_PUZZLE: Puzzle();
		break;
	case S_PICTURES: Picture_Puzzle();
		break;
	case S_ENDMENU: endScreen();
		break;
	case S_INSTRUCTIONS: instructionScreen();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
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
		case M_STARTGAME: g_eGameState = S_GAME;
			break;
		case M_INSTRUCTION: g_eGameState = S_INSTRUCTIONS;
			break;
		case M_QUITGAME: g_bQuitGame = true;
			break;
		}
	}
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	music();                   // sound can be played here too.

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
		//Beep(1440, 30);

		switch (g_eGameState)
		{
		case S_SPLASHSCREEN:
			if (IsCurrentState() == M_QUITGAME)
				IsCurrentState(M_INSTRUCTION);
			else if (IsCurrentState() == M_INSTRUCTION)
				IsCurrentState(M_STARTGAME);
			break;

		case S_GAME:
			if (g_sChar.m_cLocation.Y > OffsetBoundary && !checkMazeDisplay(g_sChar.m_cLocation, '*', 0, (-1)))
				g_sChar.m_cLocation.Y--;
			break;

		case S_PUZZLE:
			break;

		case S_PICTURES:
			break;
		}

		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT])
	{
		//Beep(1440, 30);

		if (g_eGameState == S_GAME && g_sChar.m_cLocation.X > OffsetBoundary && !checkMazeDisplay(g_sChar.m_cLocation, '*', (-1)))
			g_sChar.m_cLocation.X--;

		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN])
	{
		//Beep(1440, 30);

		switch (g_eGameState)
		{
		case S_SPLASHSCREEN:
			if (IsCurrentState() == M_STARTGAME)
				IsCurrentState(M_INSTRUCTION);
			else if (IsCurrentState() == M_INSTRUCTION)
				IsCurrentState(M_QUITGAME);
			break;

		case S_GAME:
			if (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 2 && !checkMazeDisplay(g_sChar.m_cLocation, '*', 0, 1))
				g_sChar.m_cLocation.Y++;
			break;

		case S_PUZZLE:
			break;

		case S_PICTURES:
			break;
		}

		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_RIGHT])
	{
		//Beep(1440, 30);

		if (g_eGameState == S_GAME && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 2 && !checkMazeDisplay(g_sChar.m_cLocation, '*', 1))
			g_sChar.m_cLocation.X++;

		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE])
	{
		switch (g_eGameState)
		{
		case S_SPLASHSCREEN:
			IsSelectionMade(true);
			break;

		case S_INSTRUCTIONS:
			g_eGameState = S_SPLASHSCREEN;
			IsSelectionMade(false);
			break;
		}

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
	g_Console.clearBuffer(bgColor);
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

		g_sChar.m_cLocation = getStartPosition();

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
		g_Console.writeToBuffer(g_sChar.m_cLocation, CharacterType, charColor[C_UNLIT]);
	}
	else
	{
		colour(charColor[C_LIT]);
		g_Console.writeToBuffer(g_sChar.m_cLocation, CharacterType, charColor[C_LIT]);
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
	g_Console.writeToBuffer(c, ss.str(), 0x09);

	ss.str("");
	ss << playerHealth << " Lives";
	c.X = 15;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x09);

	if (g_dElapsedTime > (1 + timer) && g_dElapsedTime < (1.01 + timer) && playerHealth>0)
	{
		timer = timer + 2;
		//playerHealth--;
	}
	if (playerHealth <= 0)
	{
		g_eGameState = S_ENDMENU;
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

void initConsole(bool input)
{
	if (input)
	{
		g_Console.initConsole(ScreenReso, "Maze Thinker");
		g_Console.setConsoleFont(0, 16, L"Raster Consolas");
	}
	else
	{
		shutdown();
		g_Console.~Console();
	}
}

void detectMazeEnd()
{
	if (checkMazeDisplay(g_sChar.m_cLocation, 'E'))
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
		InitPuzzle = true;
		g_eGameState = S_PUZZLE;
	}
	else
	{
		InitPictures = true;
		g_eGameState = S_PICTURES;
	}
}

void RunPuzzle()
{
	Typing();

	if (InitPuzzle)
	{
		initCurrentAnswer();
		InitPuzzle = false;
	}

	if (isPuzzleFinished())
	{
		Score += AddScore();
		AddScore(0);
		g_eGameState = S_GAME;
	}

	t_charBlink = g_dElapsedTime;
}

void RunPictures()
{
	PictureControl();

	if (InitPictures)
	{
		initPictures();
		InitPictures = false;
	}

	if (isPicturesFinished())
	{
		Score += AddScore();
		AddScore(0);
		g_eGameState = S_GAME;
	}

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
	c.X = g_Console.getConsoleSize().X - ss.str().length();
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str(), 0x0A);
}

void endScreen()
{
	processUserInput();
	endMenu(g_Console);
}

void instructionScreen()
{
	moveCharacter();
	instructions(g_Console);
}

void music()
{
	mciSendString(L"open \"Nyan.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString(L"play mp3", NULL, 0, NULL);
}

void Typing()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_A])
	{
		Input += "a";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_B])
	{
		Input += "b";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_C])
	{
		Input += "c";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_D])
	{
		Input += "d";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_E])
	{
		Input += "e";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_F])
	{
		Input += "f";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_G])
	{
		Input += "g";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_H])
	{
		Input += "h";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_I])
	{
		Input += "i";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_J])
	{
		Input += "j";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_K])
	{
		Input += "k";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_L])
	{
		Input += "l";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_M])
	{
		Input += "m";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_N])
	{
		Input += "n";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_O])
	{
		Input += "o";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_P])
	{
		Input += "p";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_Q])
	{
		Input += "q";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_R])
	{
		Input += "r";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_S])
	{
		Input += "s";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_T])
	{
		Input += "t";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_U])
	{
		Input += "u";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_V])
	{
		Input += "v";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_W])
	{
		Input += "w";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_X])
	{
		Input += "x";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_Y])
	{
		Input += "y";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_Z])
	{
		Input += "z";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_1] || g_abKeyPressed[K_NUM1])
	{
		Input += "1";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_2] || g_abKeyPressed[K_NUM2])
	{
		Input += "2";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_3] || g_abKeyPressed[K_NUM3])
	{
		Input += "3";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_4] || g_abKeyPressed[K_NUM4])
	{
		Input += "4";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_5] || g_abKeyPressed[K_NUM5])
	{
		Input += "5";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_6] || g_abKeyPressed[K_NUM6])
	{
		Input += "6";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_7] || g_abKeyPressed[K_NUM7])
	{
		Input += "7";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_8] || g_abKeyPressed[K_NUM8])
	{
		Input += "8";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_9] || g_abKeyPressed[K_NUM9])
	{
		Input += "9";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_0] || g_abKeyPressed[K_NUM0])
	{
		Input += "0";
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_BACK] && (Input.length() != 0))
	{
		Input.erase(Input.length() - 1, 1);
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_RETURN])
	{
		if (Input != "")
		{
			transferUserInput(Input);
			Input = "";
			AddGuesses();
		}
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}

	CurrentUserInput(Input);
}

void PictureControl()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_LEFT] && atoi(currentUserInput().c_str()) > 0)
	{
		currentUserInput(to_string(atoi(currentUserInput().c_str()) - 1));
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_RIGHT] && atoi(currentUserInput().c_str()) < 4)
	{
		currentUserInput(to_string(atoi(currentUserInput().c_str()) + 1));
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_RETURN])
	{
		TransferUserInput(currentUserInput());
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}