#include <iomanip>
#include <sstream>
#include "Puzzle.h"

using namespace std;

int Puzzle()
{
	srand(time(NULL));
	int Score = 0;
	int Minigames = rand();
	Minigames %= 5;
	switch (Minigames)
	{
	case eGame::GAME_ONE: Score = random_number_game();
		break;
	case eGame::GAME_TWO: Score = random_alphabet();
		break;
	case eGame::GAME_THREE: Score = random_pattern();
		break;
	case eGame::GAME_FOUR: Score = logic_game();
		break;
	case eGame::GAME_FIVE: Score = Riddles();
		break;
	}
	return Score;
}

int random_number_game()
{
	int Variable = rand() % LIMIT + ONE;
	int Score;
	int UserAnswer;
	int guesses = 1;
	int x = 1;
	cout << "From 1 to " << LIMIT << ", guess the number" << endl;
	while (x != 0)
	{
		cin >> UserAnswer;
		if (UserAnswer > LIMIT || UserAnswer < ONE)
		{
			cout << "Number over the range" << endl;
		}
		if (UserAnswer < Variable)
		{
			cout << "Wrong, gimme a bigger number" << endl;
			guesses++;
		}
		else if (UserAnswer > Variable)
		{
			cout << "Wrong, gimme a smaller number" << endl;
			guesses++;
		}
		else if (UserAnswer == Variable)
		{
			break;
		}
	}
	cout << "Correct! It only took you " << guesses << " times to guess!" << endl;
	if (guesses < 10)
	{
		Score = 50;
	}
	else
	{
		Score = 0;
	}
	cin.clear();
	return Score;
}

int random_alphabet()
{
	int AsciiCharacter = rand() % RANGE + ASCII;
	int Score;
	char UserAnswer;
	int guesses = 1;
	int x = 1;
	cout << "From a to z , guess the letter" << endl;
	while (x != 0)
	{
		cin >> UserAnswer;
		if (UserAnswer >= 65 && UserAnswer <= 90)
		{
			UserAnswer += 32;
		}
		else if (UserAnswer < 65 || UserAnswer > 90 && UserAnswer < 97 || UserAnswer >122)
		{
			cout << "Invalid Character" << endl;
		}
		if ((int)UserAnswer > AsciiCharacter)
		{
			cout << "Wrong, gimme an alphabet nearer to a" << endl;
			guesses++;
		}
		else if ((int)UserAnswer < AsciiCharacter)
		{
			cout << "Wrong, gimme an alphabet nearer to z" << endl;
			guesses++;
		}
		else if ((int)UserAnswer == AsciiCharacter)
		{
			break;
		}
	}
	cout << "Correct! It only took you " << guesses << " times to guess!" << endl;
	if (guesses < 10)
	{
		Score = 100;
	}
	else
	{
		Score = 0;
	}
	return Score;
}
int random_pattern()
{
	srand(time(NULL));
	int Variable = rand() % LIMIT;
	int Pattern = rand();
	int UserAnswer;
	int Score;
	int guesses = 1;
	cout << "Enter the next number in the pattern" << endl;
	while (true)
	{
		if (Pattern % TOTALPATTERNS == PatternONE)
		{
			cout << Variable << " " << Variable + 2 << " " << Variable + 4 << " " << Variable + 6 << " " << Variable + 8 << endl;
			cin >> UserAnswer;
			if (UserAnswer == Variable + 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternTWO)
		{
			cout << Variable << ", " << Variable * 2 << ", " << Variable * 4 << ", " << Variable * 6 << ", " << Variable * 8 << endl;
			cin >> UserAnswer;
			if (UserAnswer == Variable * 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternTHREE)
		{
			cout << Variable << ", " << Variable + 2 << ", " << Variable + 6 << ", " << Variable + 12 << ", " << Variable + 20 << endl;
			cin >> UserAnswer;
			if (UserAnswer == Variable + 30)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternFOUR)
		{
			cout << Variable << ", " << Variable + 1 << ", " << Variable - 2 << ", " << Variable + 3 << ", " << Variable - 4 << ", " << Variable + 5 << endl;
			cin >> UserAnswer;
			if (UserAnswer == Variable - 6)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternFIVE)
		{
			cout << Variable << ", " << Variable - 1 << ", " << Variable - 2 << ", " << Variable - 3 << ", " << Variable - 4 << endl;
			cin >> UserAnswer;
			if (UserAnswer == Variable - 5)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternSIX)
		{
			cout << Variable << ", " << Variable * 2 << ", " << (Variable * 2) + 1 << ", " << ((Variable * 2) + 1) * 2 << ", " << (((Variable * 2) + 1) * 2) + 2 << ", " << ((((Variable * 2) + 1) * 2) + 2) * 2 << ", " << (((((Variable * 2) + 1) * 2) + 2) * 2) + 3 << ", " << ((((((Variable * 2) + 1) * 2) + 2) * 2) + 3) * 2 << endl;
			cin >> UserAnswer;
			if (UserAnswer == (((((((Variable * 2) + 1) * 2) + 2) * 2) + 3) * 2) + 4)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternSEVEN)
		{
			cout << Variable << ", " << Variable + 8 << ", " << (Variable + 8) - 3 << ", " << ((Variable + 8) - 3) + 9 << ", " << (((Variable + 8) - 3) + 9) - 2 << endl;
			cin >> UserAnswer;
			if (UserAnswer == ((((Variable + 8) - 3) + 9) - 2) + 10)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternEIGHT)
		{
			cout << Variable << ", " << Variable + 10 << ", " << (Variable + 10) - 5 << ", " << ((Variable + 10) - 5) + 20 << ", " << (((Variable + 10) - 5) + 20) - 10 << endl;
			cin >> UserAnswer;
			if (UserAnswer == ((((Variable + 10) - 5) + 20) - 10) + 30)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternNINE)
		{
			cout << Variable << ", " << Variable * 2 << ", " << (Variable * 2) / 2 << ", " << ((Variable * 2) / 2) * 4 << ", " << (((Variable * 2) / 2) * 4) / 2 << ", " << ((((Variable * 2) / 2) * 4) / 2) * 6 << endl;
			cin >> UserAnswer;
			if (UserAnswer == (((((Variable * 2) / 2) * 4) / 2) * 6) / 2)
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
				guesses++;
			}
		}
		else if (Pattern % TOTALPATTERNS == PatternTEN)
		{
			cout << Variable << ", " << Variable + 10 << ", " << (Variable + 10) - 5 << ", " << ((Variable + 10) - 5) + 20 << ", " << (((Variable + 10) - 5) + 20) - 4 << ", " << ((((Variable + 10) - 5) + 20) - 4) + 30 << ", " << (((((Variable + 10) - 5) + 20) - 4) + 30) - 3 << endl;
			cin >> UserAnswer;
			if (UserAnswer == ((((((Variable + 10) - 5) + 20) - 4) + 30) - 3) + 40)
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
	if (guesses < 5)
	{
		Score = 50;
	}
	else
	{
		Score = 0;
	}
	cin.clear();
	return Score;
}
int logic_game()
{
	int Logic_Game = rand();
	int score;
	int UserAnswer;
	int correct = 0;
	if (Logic_Game % LOGIC == LogicONE)
	{
		cout << "There are 12 pens on the table, you took 3, how many do you have?" << endl;
		cout << "1) 12" << endl;
		cout << "2) 9" << endl;
		cout << "3) 0" << endl;
		cout << "4) 3" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 4)
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

		cin >> UserAnswer;
		if (UserAnswer != 4)
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

		cin >> UserAnswer;
		if (UserAnswer != 1)
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

		cin >> UserAnswer;
		if (UserAnswer != 2)
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

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! 9 is 4 as there are 4 letters in nine" << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}
	}
	else if (Logic_Game % LOGIC == LogicTWO)
	{
		cout << "If LOVE is coded as NRZJ, what is FIRE coded as?" << endl;
		cout << "1) HLVJ" << endl;
		cout << "2) GKUI" << endl;
		cout << "3) HKVJ" << endl;
		cout << "4) GLUJ" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! In the code, the first letter is the second alphabet, the second letter is the third alphabet, the third letter is the fourth alphabet and so on after the corresponding letter in the word. " << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "Banks is related to Money in the same way as Transport is the related to ____" << endl;
		cout << "1) Traffic" << endl;
		cout << "2) Goods" << endl;
		cout << "3) Speed" << endl;
		cout << "4) Road" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! Bank deals with transaction of Money.Likewise Transport deals with the movement of Goods." << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "Find the odd one out." << endl;
		cout << "1) Vapour" << endl;
		cout << "2) Mist" << endl;
		cout << "3) Hailstone" << endl;
		cout << "4) Fog" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 1)
		{
			cout << "Wrong! All except Vapour are different forms of Precipitation." << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << " F is the brother of A, C is the daughter of A, K is the sister of F and G is the brother of C then who is the uncle of G?" << endl;
		cout << "1) C" << endl;
		cout << "2) A" << endl;
		cout << "3) K" << endl;
		cout << "4) None of the above" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! C & J are childern of A and F is the brother of A. So, F is uncle of C & J. " << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "JE, LH, OL, SQ, ?" << endl;
		cout << "1) WV" << endl;
		cout << "2) WX" << endl;
		cout << "3) VW" << endl;
		cout << "4) XW" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 4)
		{
			cout << "Wrong! The first letter moves forward 2,3,4 ...... steps. The second letter moves forward 3,4,5 ...... steps." << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}
	}
	else if (Logic_Game % LOGIC == LogicTHREE)
	{
		cout << "Words from an artifical language. agnoscrenia means poisonous spider delanocrenia means poisonous snake agnosdeery means brown spider Which word could mean 'black widow spider'?" << endl;
		cout << "1) deeryclostagnos" << endl;
		cout << "2) agnosdelano" << endl;
		cout << "3) agnosvitriblunin" << endl;
		cout << "4) trymuttiagnos" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 3)
		{
			cout << "Wrong! In this language, the noun appears first and the adjectives follow. Since agnos means spider and should appear first, choices 1 and 4 can be ruled out. Choice 2 can be ruled out because delano means snake. " << endl;
		}
		else
		{
			cout << "Correct" << endl;
			correct++;
		}

		cout << "Statements: All fishes are grey in colour. Some fishes are heavy. Conclusions: All heavy fishes are grey in colour. All light fishes are not grey in colour." << endl;
		cout << "1) Only conclusion I and II follows." << endl;
		cout << "2) Only conclusion I follows." << endl;
		cout << "3) Only conclusion II follows." << endl;
		cout << "4) Neither conclusion I or II follows" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! Only conclusion I follows." << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "What has a head, tail, is brown and has no legs?" << endl;
		cout << "1) An apple" << endl;
		cout << "2) An ant" << endl;
		cout << "3) A penny" << endl;
		cout << "4) A stalk of an apple" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 3)
		{
			cout << "Wrong! A penny has a head and tail and it's also brown" << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "Adriana's mom had four kids: Marta, Anna, Justina..." << endl;
		cout << "1) Cleopatra" << endl;
		cout << "2) Annabell" << endl;
		cout << "3) Adriana" << endl;
		cout << "4) Christina" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 2)
		{
			cout << "Wrong! Adriana is her mother's child too" << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}

		cout << "Imagine you're in a dark room that is perfectly empty with nothing in it. There are no windows or doors. What is the easiest way to escape?" << endl;
		cout << "1) Die" << endl;
		cout << "2) Wait" << endl;
		cout << "3) Dig a hole in the ground with your hands" << endl;
		cout << "4) Stop imagining" << endl;

		cin >> UserAnswer;
		if (UserAnswer != 4)
		{
			cout << "Wrong! Just stop imagining and you will leave the room" << endl;
		}
		else
		{
			cout << "Correct!" << endl;
			correct++;
		}
	}
	if (correct == 0 || correct == 1)
	{
		cout << "You aren't that great with this are you?" << endl;
		score = 0;
	}
	else if (correct == 2 || correct == 3)
	{
		cout << "You are pretttttty average at this." << endl;
		score = 50;
	}
	else
	{
		cout << "YOU SIR, are a genius!" << endl;
		score = 100;
	}
	return score;
}

int Riddles()
{
	int Score;
	int Riddle = rand();
	int Tries = 1;
	int x = 1;
	string Answer;
	if (Riddle % RIDDLES == RiddleONE)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}

		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleTWO)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}

		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleTHREE)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
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
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleFOUR)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleFIVE)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleSIX)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleSEVEN)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleEIGHT)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleNINE)
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
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 100;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleTEN)
	{
		cout << "I am a box that holds keys without locks, yet they can unlock your soul. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 10)
			{
				cout << "Hint: It's related to music" << endl;
			}
			if (Answer == "Piano" || Answer == "piano")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 100;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleELEVEN)
	{
		cout << "You are in a cabin and it is pitch black. You have one match on you. Which do you light first, the newspaper, the lamp, the candle or the fire?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 10)
			{
				cout << "Hint: What starts the fire" << endl;
			}
			if (Answer == "Match" || Answer == "match")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 100;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleTWELVE)
	{
		cout << "Which word, if pronounced right, is wrong, but if pronounced wrong is right?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 10)
			{
				cout << "Hint: The word is in the riddle" << endl;
			}
			if (Answer == "Wrong" || Answer == "wrong")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 100;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleTHIRTEEN)
	{
		cout << "Which word is the odd one out : First Second Third Forth Fifth Sixth Seventh Eighth" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 10)
			{
				cout << "Hint: 4" << endl;
			}
			if (Answer == "Forth" || Answer == "forth")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 100;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleFOURTEEN)
	{
		cout << "A farmer has 17 sheep and all but 9 die. How many are left?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 10)
			{
				cout << "Hint: All died except 9" << endl;
			}
			if (Answer == "Nine" || Answer == "nine" || Answer == "9")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
	else if (Riddle % RIDDLES == RiddleFIFTEEN)
	{
		cout << "You will always find me in the past. I can be created in the present, But the future can never taint me. What am I?" << endl;
		while (x != 0)
		{
			cin >> Answer;
			if (Tries == 5)
			{
				cout << "Hint: It 'was' a phase in time." << endl;
			}
			if (Answer == "history" || Answer == "History")
			{
				cout << "Correct! It only took you " << Tries << " tries!" << endl;
				break;
			}
			else if (Tries == 10)
			{
				cout << "You used up all 10 of your attempts! That's too bad!" << endl;
				break;
			}
			else
			{
				cout << "Wrong Answer! Try Again" << endl;
				Tries++;
			}
		}
		if (Tries < 10)
		{
			Score = 50;
		}
		else
		{
			Score = 0;
		}
		return Score;
	}
}