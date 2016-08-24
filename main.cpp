#include <iostream>
#include <windows.h>
#include <MMSystem.h>

int main()
{
	PlaySound(L"c:\\cow.wav", NULL, SND_ASYNC);


	system("PAUSE");//gives it time to play and not close out
	return 0;
}
