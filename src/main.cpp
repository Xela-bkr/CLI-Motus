#include <iostream>
#include <random>

#include "colors.h"
#include "words.h"

#define A_ASCII 97
#define WIDTH 80

using namespace std;

static void colprint(const char *, char *);
static void welcome(void);
static void print_word(string, string, int);
static void game_over(string word);
static void game_win(string word);
static void replay(int & life, bool & play, string & word);
static void choose_word(string & word);

static void 
colprint(const char * color, char * text)
{
	cout << color << text << RESET << endl;
}

static void 
welcome(void)
{
	string line (WIDTH, '_');
	string title = "MOTUS";
	string padding ( (WIDTH - title.size())/2, ' ');

	cout << BOLD << line << RESET << endl << endl;
	cout << padding << title << padding << endl << endl;
	cout << BOLD << line << RESET << endl << endl;
}

static void
print_word(string expected, string gotten, int life)
{
	vector<int> v (26);
	for (unsigned int i = 0; i < expected.size(); ++i)
	{
		v[expected[i] - A_ASCII]++;
	}
	for (unsigned int i = 0; i < gotten.size(); i++)
	{
		if (expected[i] == gotten[i])
		{
			--v[expected[i] - A_ASCII];
		}
	}
	for (unsigned int i = 0; i < expected.size(); ++i)
	{
		char c = gotten[i];
		unsigned int j = gotten[i] - A_ASCII;
		if (c == expected[i])
		{
			cout << " " << GREEN << c << RESET;
		}
		else if ((expected.find(c) != string::npos) && v[j])
		{
			cout << " " << ORANGE << c << RESET;
			v[j]--;
		}
		else
		{
			cout << " " << RED << c << RESET;
		}
	}
	cout << " | " << BLUE << life - 1 << RESET << " more rounds" << endl; 
}

static void 
game_over(string word)
{
	string line (WIDTH, '_');
	string title = "GAME OVER \"\"\\_|°.°|_/\"\"";
	string guess_word = "The word is : ";
	string guess_word_padding ((WIDTH - guess_word.size() - word.size() - 2)/2, ' ');
	string padding ( (WIDTH - title.size())/2, ' ');

	cout << BOLD << line << RESET << endl << endl;
	cout << padding << RED << title << RESET << endl << endl;
	cout << guess_word_padding << guess_word << RED << word << RESET << endl << endl;
	cout << BOLD << line << RESET << endl << endl;
}

static void 
game_win(string word)
{
	string line (WIDTH, '_');
	string title = "GAME WIN -|°O°|-";
	string guess_word = "The word is : ";
	string guess_word_padding ((80 - guess_word.size() - word.size() - 2)/2, ' ');
	string padding ( (WIDTH - title.size())/2, ' ');

	cout << BOLD << line << RESET << endl;
	cout << guess_word_padding << guess_word << GREEN << word << RESET << endl << endl;
	cout << padding << GREEN << title << RESET << endl;
	cout << BOLD << line << RESET << endl << endl;
}

static void 
replay(int & life, bool & play, string & word)
{
	char repl;
	cout << "Replay ? [y/n] : ";
	cin >> repl;
	if (repl == 'y')
	{
		life = 8;
		choose_word(word);
	}
	else 
	{
		play = false;
	}
}

static void
choose_word(string & word)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist (0, words.size());
	int index = dist(gen);
	word = words[index];
}

int 
main(void)
{
	int life;
	bool play;
	string word, user_input;

	life = 8;
	play = true;
	choose_word(word);

	welcome ();
	while (play)
	{
		if (life <= 0)
		{
			char repl;
			game_over(word);
			replay(life, play, word);
			continue;
		}
		cout << "Entrez un mot (8 lettres) : ";
		cin >> user_input;
		if (user_input.size() < 8)
		{
			cout << BOLD << RED << "Saisie de moins de 8 caractères invalide" << RESET << endl;
			continue;
		}
		if (word == user_input)
		{
			game_win(word);
			replay(life, play, word);
			continue;
		}
		print_word(word, user_input, life);
		--life;
	}
	return 0;
}

