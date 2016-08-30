#ifndef _GAME_H
#define _GAME_H
#include "Framework\timer.h"
#include "Framework\console.h"
#include "sound.h"
#include "Menu\startMenu.h"
#include "instructions.h"
#include "Menu\settingMenu.h"
#include "Menu\quitMenu.h"
#include "Maze\maze.h"
#include "Highscore.h"
#include "Pictures.h"
#include "Puzzle.h"
#include "riddlestorage.h"
#include "logicstorage.h"
#include "picture_storage.h"
#include "endMenu.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

const COORD ScreenReso = { 120, 50 };
const unsigned int OffsetBoundary = 1;

#define VK_A              0x41
#define VK_B              0x42
#define VK_C              0x43
#define VK_D              0x44
#define VK_E              0x45
#define VK_F              0x46
#define VK_G              0x47
#define VK_H              0x48
#define VK_I              0x49
#define VK_J              0x4A
#define VK_K              0x4B
#define VK_L              0x4C
#define VK_M              0x4D
#define VK_N              0x4E
#define VK_O              0x4F
#define VK_P              0x50
#define VK_Q              0x51
#define VK_R              0x52
#define VK_S              0x53
#define VK_T              0x54
#define VK_U              0x55
#define VK_V              0x56
#define VK_W              0x57
#define VK_X              0x58
#define VK_Y              0x59
#define VK_Z              0x5A

#define VK_0			  0x30
#define VK_1			  0x31
#define VK_2			  0x32
#define VK_3			  0x33
#define VK_4			  0x34
#define VK_5			  0x35
#define VK_6			  0x36
#define VK_7			  0x37
#define VK_8			  0x38
#define VK_9			  0x39


// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_BACK,
	K_RETURN,
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_NUM0,
	K_NUM1,
	K_NUM2,
	K_NUM3,
	K_NUM4,
	K_NUM5,
	K_NUM6,
	K_NUM7,
	K_NUM8,
	K_NUM9,
	K_COUNT
};
// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_INSTRUCTIONS,
	S_SETTING,
	S_GAME,
	S_COUNT,
	S_PUZZLE,
	S_PICTURES,
	S_ENDMENU,
	S_QUIT
};

enum CharState
{
	C_UNLIT,
	C_LIT
};

// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory

void splashScreen();
void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void TriggerMiniGames();
void RunPuzzle();
void BackToGame();
void RunPictures();
void ScoreDisplay();
void detectMazeEnd();
void endScreen();
void Alphabets();
void instructionScreen();
void numbers();
void Typing();
void PictureControl();
void TypingNumbers();
void LiveTime();
#endif // _GAME_H