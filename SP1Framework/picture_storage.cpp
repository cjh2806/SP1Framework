#include "picture_storage.h"

const string PicRef[5][4] = { { "Transport.txt", "Wrong Answer! 4) is a car, 1) is a Plane, 2) is a Train & 3) is a Boat" ,"3", "Correct!"},
{ "Car.txt", "Wrong Answer! Toyota has earned the most revenue among the 4 other \n brands, with Hyundai at 4) coming in at 2nd","2","Correct!"},
{ "Flag.txt", "Wrong Answer! 1) Vietnam is communist country 2) Japan is not a \n communist country 3) Turkey is not a communist country 4) Switzerland\n is not a communist country","0","Correct!"},
{ "Food.txt", "Wrong Answer! 1) Dominos is from the US along with 2) McDonalds, \n 3) A & W is from Canada while 4) Mos Burger is from Japan","3","Correct!"},
{ "Football.txt", "Wrong Answer! 1) Real Madrid is from Spain, 2) Juventus is from Italy, \n 3) Liverpool is from England and 4) Borussia Dortmund is from Germany","1","Correct!"} };

string** Pic;

string* getPicturedata() { return (string *)Pic; }

void Picturestorage()
{
	Pic = new string*[5];

	for (int i = 0; i < 5; i++)
	{
		Pic[i] = new string[4];

		for (int j = 0; j < 4; j++)
		{
			Pic[i][j] = PicRef[i][j];
		}
	}
}
