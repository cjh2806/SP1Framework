#include "logicstorage.h"

using namespace std;

string** logic;

string* getlogicdata()
{
	return (string *)logic;
}

void logicstorage()
{
	string logicRef[16][7] = { { "There are 12 pens on the table, you took 3, how many do you have?",
		"1) 12",
		"2) 9",
		"3) 0",
		"4) 3",
		"Wrong, you took 3 pens so you have 3 pens",
		"4"},

		{ "If an electric train is traveling from the east to the west, which direction is the smoke traveling?",
		"1) East",
		"2) West",
		"3) Up",
		"4) None of the above",
		"Wrong, an electric train does not produse smoke",
		"4" },

		{ "There are 100 birds on a tree, *BANG*, you shot and killed 1 bird. How many birds are left on the tree?",
		"1) 0",
		"2) 100",
		"3) 99",
		"4) 1",
		"Wrong, if you fired a gun and killed a bird the other birds will fly away" ,
		"1" },

		{ "If you are in a race, what place are you in if you take over the person who is in second place?",
		"1) First",
		"2) Second",
		"3) Third",
		"4) Last",
		"Wrong, if you overtake second, you are now second" ,
		"2" },

		{ "1 is 3, 3 is 5, 5 is 4, 7 is 5. What is 9?",
		"1) 5",
		"2) 4",
		"3) 6",
		"4) 3",
		"Wrong, 9 is 4 as there are 4 letters in 9." ,
		"2" },

		{ "If LOVE is coded as NRZJ, what is FIRE coded as?",
		"1) HLVJ",
		"2) GLUI",
		"3) HKVI",
		"4) GKUJ",
		"Wrong! In the code, the first letter is the second alphabet, the second letter is the third alphabet, the third letter is the fourth alphabet and so on after the corresponding letter in the word.",
		"2" },

		{ "Banks is related to Money in the same way as Transport is the related to ____?",
		"1) Traffic",
		"2) Goods",
		"3) Speed",
		"4) Road",
		"Wrong! Bank deals with the transaction of Money. Likewise Transport deals with the movement of Goods.",
		"2" },

		{ "Find the odd one out.",
		"1) Vapour",
		"2) Mist",
		"3) Hailstone",
		"4) Fog",
		"Wrong! All except Vapour are different forms of Precipitation.",
		"1" },

		{ "F is the brother of A, C is the daughter of A, K is the sister of F and G is the brother of C then who is the uncle of G?",
		"1) C",
		"2) F",
		"3) K",
		"4) None of the above",
		"Wrong! C & J are childern of A and F is the brother of A. So, F is uncle of C & G. ",
		"2" },

		{ "JE, LH, OL, SQ, ?",
		"1) WV",
		"2) WX",
		"3) VW",
		"4) XW",
		"Wrong! The first letter moves forward 2,3,4 ...... steps. The second letter moves forward 3,4,5 ...... steps." ,
		"4" },

		{ "Words from an artifical language.agnoscrenia means poisonous spider delanocrenia means poisonous snake agnosdeery means brown spider Which word could mean 'black widow spider'?",
		"1) deeryclostagnos",
		"2) agnosdelano",
		"3) agnosvitriblunin",
		"4) trymuttiagnos",
		"Wrong! In this language, the noun appears first and the adjectives follow. Since agnos means spider and should appear first, choices 1 and 4 can be ruled out. Choice 2 can be ruled out because delano means snake.",
		"3" },

		{ "Statements: All fishes are grey in colour.Some fishes are heavy.Conclusions : All heavy fishes are grey in colour.All light fishes are not grey in colour. ? ",
		"1) Only conclusion I and II follows.",
		"2) Only conclusion I follows.",
		"3) Only conclusion II follows.",
		"4) Neither conclusion I or II follows",
		"Wrong! Only conclusion I follows.",
		"2" },

		{ "What has a head, tail, is brown and has no legs?",
		"1) An Apple",
		"2) An Ant",
		"3) A Penny",
		"4) A Stalk of an Apple" ,
		"Wrong! A penny has a head and tail and it's also brown" ,
		"3" },

		{ "Adriana's mom had four kids: Marta, Anna, Justina...",
		"1) Cleopatra",
		"2) Adriana",
		"3) Annabell",
		"4) Christina" ,
		"Wrong! Adriana is her mother's child too" ,
		"2" },

		{ "Imagine you're in a dark room that is perfectly empty with nothing in it. There are no windows or doors. What is the easiest way to escape?",
		"1) Die",
		"2) Wait",
		"3) Dig a hole in the ground with your hands",
		"4) Stop imagining" ,
		"Wrong! Just stop imagining and you will leave the room" ,
		"4" },

		{ "Answer Invalid! Try again",
		"Correct!",
		"", } };

	logic = new string*[16];

	for (int i = 0; i < 16; i++)
	{
		logic[i] = new string[7];

		for (int j = 0; j < 7; j++)
		{
			logic[i][j] = logicRef[i][j];
		}
	}
}
