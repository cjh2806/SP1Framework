#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include "Pictures.h"
#include <ctime>

void Picture_Puzzle()
{
	srand(time(NULL));

	int i = rand() % 5;
	if (i == 0)
	{
		std::ifstream Reader("Transport.txt");
		std::string Art = getFileContents(Reader);
		std::cout << Art << std::endl;
		Reader.close();
		int x;
		std::cin >> x;
		if (x == 4)
		{
			std::cout << "Correct!" << std::endl;
		}
		else
		{
			std::cout << "Wrong Answer! 4) is a car, 1) is a Plane, 2) is a Train & 3) is a Boat" << std::endl;
		}
	}
	else if (i == 1)
	{
		std::ifstream Reader("car.txt");
		std::string Art = getFileContents(Reader);
		std::cout << Art << std::endl;
		Reader.close();
		int x;
		std::cin >> x;
		if (x == 3)
		{
			std::cout << "Correct!" << std::endl;
		}
		else
		{
			std::cout << "Wrong Answer! Toyota has earned the most revenue among the 4 other brands, with Hyundai at 4) coming in at 2nd" << std::endl;
		}
	}
	else if (i == 2)
	{
		std::ifstream Reader("Football.txt");
		std::string Art = getFileContents(Reader);
		std::cout << Art << std::endl;
		Reader.close();
		int x;
		std::cin >> x;
		if (x == 2)
		{
			std::cout << "Correct!" << std::endl;
		}
		else
		{
			std::cout << "Wrong Answer! 1) Real Madrid is from Spain, 2) Juventus is from Italy, 3) Liverpool is from England and 4) Borussia Dortmund is from Germany" << std::endl;
		}
	}
	else if (i == 3)
	{
		std::ifstream Reader("Flag.txt");
		std::string Art = getFileContents(Reader);
		std::cout << Art << std::endl;
		Reader.close();
		int x;
		std::cin >> x;
		if (x == 1)
		{
			std::cout << "Correct!" << std::endl;
		}
		else
		{
			std::cout << "Wrong Answer! 1) Vietnam is communist country 2) Japan is not a communist country 3) Turkey is not a communist country 4) Switzerland is not a communist country" << std::endl;
		}
	}
else if (i == 4){
		std::ifstream Reader("Food.txt");
		std::string Art = getFileContents(Reader);
		std::cout << Art << std::endl;
		Reader.close();
		int x;
		std::cin >> x;
		if (x == 4)
		{
			std::cout << "Correct!" << std::endl;
		}
		else
		{
			std::cout << "Wrong Answer! 1) Dominos is from the US along with 2) McDonalds, 3) A & W is from Canada while 4) Mos Burger is from Japan" << std::endl;
		}
	}
}

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";
	if (File)
	{
		while (File.good())
		{
			std::string TempLine;
			std::getline(File, TempLine);
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