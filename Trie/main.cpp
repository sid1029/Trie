#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

int main(int argc, char * argv[])
{
	Trie trie;
	string tmp;

	ifstream dict("../dict.txt");

	if (!dict)
	{
		cout<<"Dictionary file not found";
		return 0;
	}

	int count = 0;
	while(!dict.eof())
	{
		dict >> tmp;
		trie.add(tmp);
		++count;
	}

	while(true)
	{
		cout << "> ";
		cin >> tmp;
		cout<<tmp<<endl;
		if (!trie.suggestWord(tmp))
			cout<<"NO SUGGESTION";

		cout << endl;
	}
	
	getchar();
	return 0;
}