#include "riddlestorage.h"

using namespace std;

string** joke;

string* getriddledata()
{
	return (string *)joke;
}

void riddlestorage()
{
	string jokeRef[16][4] = { { "What is black when you buy it, red when you use it, and gray when you throw it away?",
		"Tip: The word is 8 characters long and is used as energy for cooking",
		"charcoal",
		"" },

		{ "If I drink, I die. If I eat, I am fine. What am I?",
		"Hint: The word is normally orange in colour and rhymes with dire",
		"fire",
		"" },

		{ "I'm the part of the bird that's not in the sky. I can swim in the ocean and yet remain dry. What am I?",
		"Hint: Every living creature has this during the day but not at night",
		"shadow",
		"" },

		{ "I never was, am always to be, No one ever saw me, nor ever will, And yet I am the confidence of all To\nlive and breathe on this terrestrial ball. What am I?",
		"Hint: It's related to day and it's the future",
		"tomorrow",
		"" },

		{ "I have many feathers to help me fly. I have a body and head, but I'm not alive. It is your strength which\ndetermines how far I go. You can hold me in your hand, but I'm never thrown. What am I?",
		"Hint: It's the name of Superhero Show and it is used with a weapon",
		"arrow",
		"" },

		{ "If I have it, I don't share it. If I share it, I don't have it. What is it?",
		"Hint: It's something that you want to hide from other and mostly written inside a diary.",
		"secret",
		"" },

		{ "A little pool with two layers of wall around it. One white and soft and the other dark and hard, amidst a\nlight brown grassy lawn with an outline of a green grass. What am I?",
		"Hint: It's a fruit and can be made into a drink.",
		"coconut",
		"" },

		{ "They come out at night without being called, and are lost in the day without being stolen. What are they?",
		"Hint: It's related to space.",
		"stars",
		"" },

		{ "All about, but cannot be seen, Can be captured, cannot be held, No throat, but can be heard. What am I?",
		"Hint: It's related to the weather.",
		"wind",
		"" },

		{ "I am a box that holds keys without locks, yet they can unlock your soul. What am I?",
		"Hint: It's related to music",
		"piano",
		"" },

		{ "You are in a cabin and it is pitch black. You have one match on you. Which do you light first, the\nnewspaper, the lamp, the candle or the fire?",
		"Hint: What starts the fire",
		"match",
		"" },

		{ "Which word, if pronounced right, is wrong, but if pronounced wrong is right?",
		"Hint: The word is in the riddle",
		"wrong",
		"" },

		{ "Which word is the odd one out : First Second Third Forth Fifth Sixth Seventh Eighth",
		"Hint: 4",
		"forth",
		"" },

		{ "A farmer has 17 sheep and all but 9 die. How many are left?",
		"Hint: All died except 9",
		"nine",
		"" },

		{ "You will always find me in the past. I can be created in the present, But the future can never taint me. What am I?",
		"Hint: It 'was' a phase in time.",
		"history",
		"" },

		{ "Correct! It only took you ",
		" times to guess!",
		"You used up all 10 of your attempts! That's too bad!",
		"Wrong Answer! Try Again" } }; 

	joke = new string*[16];

	for (int i = 0; i < 16; i++)
	{
		joke[i] = new string[4];

		for (int j = 0; j < 4; j++)
		{
			joke[i][j] = jokeRef[i][j];
		}
	}
}
