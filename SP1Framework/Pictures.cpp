#include "game.h"
#include "Framework\console.h"
#include "Pictures.h"
#include <ctime>

using namespace std;

int Picture_Puzzle()
{
	srand(time(NULL));
	int Score;
	int i = rand() % 5;
	if (i == 0)
	{
		ifstream Reader("Transport.txt");
		string Art = getFileContents(Reader);
		cout << Art << endl;
		Reader.close();
		int x;
		cin >> x;
		if (x == 4)
		{
			cout << "Correct!" << endl;
			Score = 50;
		}
		else
		{
			cout << "Wrong Answer! 4) is a car, 1) is a Plane, 2) is a Train & 3) is a Boat" << endl;
			Score = 0;
		}
	}
	else if (i == 1)
	{
		ifstream Reader("car.txt");
		string Art = getFileContents(Reader);
		cout << Art << endl;
		Reader.close();
		int x;
		cin >> x;
		if (x == 3)
		{
			cout << "Correct!" << endl;
			Score = 50;
		}
		else
		{
			cout << "Wrong Answer! Toyota has earned the most revenue among the 4 other brands, with Hyundai at 4) coming in at 2nd" << endl;
			Score = 0;
		}
	}
	else if (i == 2)
	{
		ifstream Reader("Football.txt");
		string Art = getFileContents(Reader);
		cout << Art << endl;
		Reader.close();
		int x;
		cin >> x;
		if (x == 2)
		{
			cout << "Correct!" << endl;
			Score = 50;
		}
		else
		{
			cout << "Wrong Answer! 1) Real Madrid is from Spain, 2) Juventus is from Italy, 3) Liverpool is from England and 4) Borussia Dortmund is from Germany" << endl;
			Score = 0;
		}
	}
	else if (i == 3)
	{
		ifstream Reader("Flag.txt");
		string Art = getFileContents(Reader);
		cout << Art << endl;
		Reader.close();
		int x;
		cin >> x;
		if (x == 1)
		{
			cout << "Correct!" << endl;
			Score = 50;
		}
		else
		{
			cout << "Wrong Answer! 1) Vietnam is communist country 2) Japan is not a communist country 3) Turkey is not a communist country 4) Switzerland is not a communist country" << endl;
			Score = 0;
		}
	}
	else if (i == 4)
	{
		ifstream Reader("Food.txt");
		string Art = getFileContents(Reader);
		cout << Art << endl;
		Reader.close();
		int x;
		cin >> x;
		if (x == 4)
		{
			cout << "Correct!" << endl;
			Score = 50;
		}
		else
		{
			cout << "Wrong Answer! 1) Dominos is from the US along with 2) McDonalds, 3) A & W is from Canada while 4) Mos Burger is from Japan" << endl;
			Score = 0;
		}
	}
	return Score;
}

string getFileContents(ifstream& File)
{
	string Lines = "";
	if (File)
	{
		while (File.good())
		{
			string TempLine;
			getline(File, TempLine);
			TempLine += "\n";
			Lines += TempLine;
		}
		return Lines;
	}
	else
	{
		return "ERROR File does not exist.";
	}
}