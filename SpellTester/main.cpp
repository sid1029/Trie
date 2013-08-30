#include <ctime>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

// Sleep between word generations
#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif

typedef unsigned int uint;
using namespace std;

#define SWITCH_CASE(x) (islower(x) ? toupper(x) : tolower(x))

inline double roll(const double a, const double b) { return (b - a) * (rand() / double(RAND_MAX)) + a; }

inline bool isVowel(const char c) { return ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')); }

char getRandomVowel(const char c)
{
	char* v = "aeiou";
	std::set<char> vovels(v, v + strlen(v));
	vovels.erase(c);

	std::set<char>::const_iterator it(vovels.begin());
	std::advance(it, (uint)roll(1, 4));
	return (*it);
}

int main(int argc, char * argv[])
{
	vector<string> wordList;
	wordList.reserve(235923); // Reserving the memory upfront speeds up the copy process since it eliminates the resizes that would have occured.
	ifstream dict("../dict.txt");

	if (!dict)
	{
		cout<<"Dictionary file not found";
		return 0;
	}

	std::copy(std::istream_iterator<string>(dict),
				 std::istream_iterator<string>(),
				 std::back_inserter(wordList));
	dict.close();
	std::srand((uint)std::time(0));
	uint count = 0;
	while (true)
	{
		sleep(800);
		// choosing a random word
		string word(wordList[(uint)roll(0, wordList.size())]);

		// Starting with 15 unmodified words.
		if (count < 15)
		{
			cout<<word<<endl;
			++count;
			continue;
		}

		for(uint i = 0; i < word.size(); ++i)
		{
			double randRoll = roll(0, 100);

			// Choose variation
			if (randRoll >= 0 && randRoll <= 40.0f) // 40% chance to change case.
			{
				word[i] = SWITCH_CASE(word[i]);
			}
			if (randRoll >= 40.0f && randRoll <= 70.0f) // 30% chance to repeat character.
			{
				if (isVowel(word[i]))
				{
					if (roll(0,100) > 50) // 50% chance to change vovel.
						word[i] = getRandomVowel(word[i]);
				}
				uint repeats = (uint) roll(1, 5); // repeat it anywhere between 1 and 5 times.
				if (roll(0,100) > 50) // 50% chance to make it upper case.
					word.insert( i, repeats, SWITCH_CASE(word[i]) );
				else
					word.insert( i, repeats, word[i] );
				i += repeats;
			}
		}
		cout<<word<<endl;
	}

	getchar();
	return 0;
}