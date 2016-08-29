#include "sound.h"

void openMusic() { mciSendString(L"open \"Sound/Music.mp3\" type mpegvideo alias mp3", NULL, 0, NULL); }
void playMusic() { mciSendString(L"play mp3 repeat", NULL, 0, NULL); }
void pauseMusic() { mciSendString(L"pause mp3", NULL, 0, NULL); }
void resumeMusic() { mciSendString(L"resume mp3", NULL, 0, NULL); }