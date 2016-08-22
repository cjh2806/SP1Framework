#include "Puzzle.h"
#include <iostream>
#include <ctime>

void Puzzle()
{
	srand(time(NULL));

	int i = rand() % 5;

	if (i == 0)
	{
		int Q = rand() % 1000 + 1;
		random_number_game(Q);
	}
	else if (i == 1)
	{
		int B = rand() % 26 + 97;
		random_alphabet(B);
	}
	else if (i == 2)
	{

		int S = rand() % 10 + 1;
		int Z = rand() % 100;
		random_pattern(S, Z);
	}
	else if (i == 3)
	{
		int A = rand() % 20 + 1;
		logic_game(A);
	}
	else if (i == 4)
	{
		int a = rand() % 14;
		Riddles(a);
	}
}

void random_number_game(int a)
{
	int c = rand() % a;
	int b;
	int guesses = 1;
	int x = 1;
	cout << "From 1 to " << a << ", guess the number" << endl;
	while (x != 0)
	{
		cin >> b;
		if (b > a)
		{
			cout << "Number over the range" << endl;
		}
		if (b < c)
		{
			cout << "Wrong, gimme a bigger number" << endl;
			guesses++;
		}
		else if (b > c)
		{
			cout << "Wrong, gimme a smaller number" << endl;
			guesses++;
		}
		else if (b == c)
		{
			break;
		}
	}
	cout << "Correct! It only took you " << guesses << " times to guess!" << endl;
}

void random_alphabet(int a)
{
	char b;
	int guesses = 1;
	int x = 1;
	cout << "From a to z , guess the letter" << endl;
	while (x != 0)
	{
		cin >> b;
		if (b >= 65 && b <= 90)
		{
			b += 32;
		}
		else if (b < 65 || b > 90 && b < 97 || b >122)
		{
			cout << "Invalid Character" << endl;
		}
		if ((int)b > a)
		{
			cout << "Wrong, gimme an alphabet nearer to a" << endl;
			guesses++;
		}
		else if ((int)b < a)
		{
			cout << "Wrong, gimme an alphabet nearer to z" << endl;
			guesses++;
		}
		else if ((int)b == a)
		{
			break;
		}
	}
	cout << "Correct! It only took you " << guesses << " times to guess!" << endl;
}
void random_pattern(int a, int b)
{
	int c;

	int guesses = 1;
	cout << "Enter the next number in the pattern" << endl;
	while (true)
	{
		if (a == 1)
		{
			cout << b << " " << b + 2 << " " << b + 4 << " " << b + 6 << " " << b + 8 << endl;
			cin >> c;
			if (c == b + 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 2)
		{
			cout << b << ", " << b * 2 << ", " << b * 4 << ", " << b * 6 << ", " << b * 8 << endl;
			cin >> c;
			if (c == b * 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 3)
		{
			cout << b << ", " << b + 2 << ", " << b + 6 << ", " << b + 12 << ", " << b + 20 << endl;
			cin >> c;
			if (c == b + 30)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 4)
		{
			cout << b << ", " << b + 1 << ", " << b - 2 << ", " << b + 3 << ", " << b - 4 << ", " << b + 5 << endl;
			cin >> c;
			if (c == b - 6)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 5)
		{
			cout << b << ", " << b - 1 << ", " << b - 2 << ", " << b - 3 << ", " << b - 4 << endl;
			cin >> c;
			if (c == b - 5)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 6)
		{
			cout << b << ", " << b * 2 << ", " << (b * 2) + 1 << ", " << ((b * 2) + 1) * 2 << ", " << (((b * 2) + 1) * 2) + 2 << ", " << ((((b * 2) + 1) * 2) + 2) * 2 << ", " << (((((b * 2) + 1) * 2) + 2) * 2) + 3 << ", " << ((((((b * 2) + 1) * 2) + 2) * 2) + 3) * 2 << endl;
			cin >> c;
			if (c == (((((((b * 2) + 1) * 2) + 2) * 2) + 3) * 2) + 4)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 7)
		{
			cout << b << ", " << b + 8 << ", " << (b + 8) - 3 << ", " << ((b + 8) - 3) + 9 << ", " << (((b + 8) - 3) + 9) - 2 << endl;
			cin >> c;
			if (c == ((((b + 8) - 3) + 9) - 2) + 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 8)
		{
			cout << b << ", " << b + 10 << ", " << (b + 10) - 5 << ", " << ((b + 10) - 5) + 20 << ", " << (((b + 10) - 5) + 20) - 10 << endl;
			cin >> c;
			if (c == ((((b + 10) - 5) + 20) - 10) + 30)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 9)
		{
			cout << b << ", " << b * 2 << ", " << (b * 2) / 2 << ", " << ((b * 2) / 2) * 4 << ", " << (((b * 2) / 2) * 4) / 2 << ", " << ((((b * 2) / 2) * 4) / 2) * 6 << endl;
			cin >> c;
			if (c == (((((b * 2) / 2) * 4) / 2) * 6) / 2)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (a == 10)
		{
			cout << b << ", " << b + 10 << ", " << (b + 10) - 5 << ", " << ((b + 10) - 5) + 20 << ", " << (((b + 10) - 5) + 20) - 4 << ", " << ((((b + 10) - 5) + 20) - 4) + 30 << ", " << (((((b + 10) - 5) + 20) - 4) + 30) - 3 << endl;
			cin >> c;
			if (c == ((((((b + 10) - 5) + 20) - 4) + 30) - 3) + 40)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
	}
	cout << "Correct! It only took " << guesses << " guesses" << endl;
}
void logic_game(int a)
{
	int x;
	int correct = 0;
	cout << "There are 12 pens on the table, you took 3, how many do you have?" << endl;
	cout << "1) 12" << endl;
	cout << "2) 9" << endl;
	cout << "3) 0" << endl;
	cout << "4) 3" << endl;

	cin >> x;
	if (x != 4)
	{
		cout << "Wrong, you took 3 pens so you have 3 pens" << endl;
	}
	else
	{
		cout << "Correct" << endl;
		correct++;
	}

	cout << "If an electric train is traveling from the east to the west, which direction is the smoke traveling?" << endl;
	cout << "1) East" << endl;
	cout << "2) West" << endl;
	cout << "3) Up" << endl;
	cout << "4) None of the above" << endl;

	cin >> x;
	if (x != 4)
	{
		cout << "Wrong, an electric train does not produse smoke" << endl;
	}
	else
	{
		cout << "Correct" << endl;
		correct++;
	}

	cout << "There are 100 birds on a tree" << endl;
	cout << "*BANG*" << endl;
	cout << "you shot and killed 1 bird" << endl;
	cout << "How many birds are left on the tree?" << endl;
	cout << "1) 0" << endl;
	cout << "2) 100" << endl;
	cout << "3) 99" << endl;
	cout << "4) 1" << endl;

	cin >> x;
	if (x != 1)
	{
		cout << "Wrong, if you fired a gun and killed a bird the other birds will fly away" << endl;
	}
	else
	{
		cout << "Correct" << endl;
		correct++;
	}

	cout << "If you are in a race, what place are you in if you take over the person who is in second place?" << endl;
	cout << "1) First" << endl;
	cout << "2) Second" << endl;
	cout << "3) Third" << endl;
	cout << "4) Last" << endl;

	cin >> x;
	if (x != 2)
	{
		cout << "Wrong! If you overtake second, you are now second" << endl;
	}
	else
	{
		cout << "Correct!" << endl;
		correct++;
	}
	cout << "1 is 3, 3 is 5, 5 is 4, 7 is 5. What is 9?" << endl;
	cout << "1) 5" << endl;
	cout << "2) 4" << endl;
	cout << "3) 6" << endl;
	cout << "4) 3" << endl;

	cin >> x;
	if (x != 2)
	{
		cout << "Wrong! 9 is 4 as there are 4 letters in nine" << endl;
	}
	else
	{
		cout << "Correct!" << endl;
		correct++;
	}

	if (correct == 0 || correct == 1)
	{
		cout << "You aren't that great with this are you?" << endl;
	}
	else if (correct == 2 || correct == 3)
	{
		cout << "You are pretttttty average at this." << endl;
	}
	else
	{
		cout << "YOU SIR, are a genius!" << endl;
	}
}

void Riddles(int a)
{
	int Tries = 1;
	int x = 1;
	string Answer;
	if (a == 0)
	{
		cout << "What is black when you buy it, red when you use it, and gray when you throw it away?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Tip: The word is 8 characters long and is used as energy for cooking" << endl;
			}
			if (Answer == "Charcoal" || Answer == "charcoal")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}

		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 1)
	{
		cout << "If I drink, I die. If I eat, I am fine. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: The word is normally orange in colour and rhymes with dire" << endl;
			}
			if (Answer == "Fire" || Answer == "fire")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}

		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 2)
	{
		cout << "I'm the part of the bird that's not in the sky. I can swim in the ocean and yet remain dry. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: Every living creature has this during the day but not at night" << endl;
			}
			if (Answer == "Shadow" || Answer == "shadow")
			{
				break;
			}
			else if (Answer == "Shishanth")
			{
				cout << "Close but not quite and also who?" << endl;
				Tries++;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 3)
	{
		cout << "I never was, am always to be, No one ever saw me, nor ever will, And yet I am the confidence of all To live and breathe on this terrestrial ball. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's related to day and it's the future" << endl;
			}
			if (Answer == "Tomorrow" || Answer == "tomorrow")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 4)
	{
		cout << "I have many feathers to help me fly. I have a body and head, but I'm not alive. It is your strength which determines how far I go. You can hold me in your hand, but I'm never thrown. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's the name of Superhero Show and it is used with a weapon" << endl;
			}
			if (Answer == "Arrow" || Answer == "arrow")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 5)
	{
		cout << "If I have it, I don't share it. If I share it, I don't have it. What is it?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's something that you want to hide from other and mostly written inside a diary." << endl;
			}
			if (Answer == "Secret" || Answer == "secret")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 6)
	{
		cout << "A little pool with two layers of wall around it. One white and soft and the other dark and hard, amidst a light brown grassy lawn with an outline of a green grass. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's a fruit and can be made into a drink." << endl;
			}
			if (Answer == "Coconut" || Answer == "coconut")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}			
		}
		cout << "Correct! It only took you " << Tries << " tries!" << endl;
	}
	else if (a == 7)
	{
		cout << "They come out at night without being called, and are lost in the day without being stolen. What are they?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's related to space." << endl;
			}
			if (Answer == "Stars" || Answer == "stars")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 8)
	{
		cout << "All about, but cannot be seen, Can be captured, cannot be held, No throat, but can be heard. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's related to the weather." << endl;
			}
			if (Answer == "Wind" || Answer == "wind")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 9)
	{
		cout << "I am a box that holds keys without locks, yet they can unlock your soul. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It's related to music" << endl;
			}
			if (Answer == "Piano" || Answer == "piano")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 10)
	{
		cout << "You are in a cabin and it is pitch black. You have one match on you. Which do you light first, the newspaper, the lamp, the candle or the fire?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: What starts the fire" << endl;
			}
			if (Answer == "Match" || Answer == "match")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 11)
	{
		cout << "Which word, if pronounced right, is wrong, but if pronounced wrong is right?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: The word is in the riddle" << endl;
			}
			if (Answer == "Wrong" || Answer == "wrong")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 12)
	{
		cout << "Which word is the odd one out : First Second Third Forth Fifth Sixth Seventh Eighth" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: 4" << endl;
			}
			if (Answer == "Forth" || Answer == "forth")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	else if (a == 13)
	{
		cout << "A farmer has 17 sheep and all but 9 die. How many are left?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: All died except 9" << endl;
			}
			if (Answer == "Nine" || Answer == "nine" || Answer == "9")
			{
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		cout << "Correct! It only took you " << Tries << "tries!" << endl;
	}
	
}