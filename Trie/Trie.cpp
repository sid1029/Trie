#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include "Trie.h"

/*
* The trie is populated by skipping over repititions of characters in words. e.g. "apple" is stored as "aple".
* The final node of every word holds the original word.
*/
void Trie::add(string word)
{
    TrieNode* curr = mRoot;
    for(uint i = 0; i < word.length(); ++i)
    {
		char& c = word[i];
		
		if ( (i > 0 && c == word[i-1]) || !isalpha(c) )
			continue;

		if(!curr->child(c))
			curr->child(c) = new TrieNode;
		
		curr = curr->child(c);
    }
    curr->final = true;
	curr->actualWord = new std::string(word);
}

/*
* The search is a combination of recursion and looping. It uses loop iterations to skip over repated consonants,
* while using recursion to search through all possible vowels that could have taken the place of the original one in the misspelling.
* Complexity in the worst case (all vowels in a word): O(mlog(m)).
* average case : O(log(m)).
* best case (all consonants): O(m).
* Here m is the number of characters in the query word.
*/
bool Trie::search(string& word, Trie::TrieNode* node)
{
	if(!node)
		return false;

	for(uint i = 0; i < word.size(); ++i)
    {
		const char& c = word[i];
		if (isVowel(c))
		{
			// As soon as we see a vowel, recurse down into all substrings starting with vowels from that node.
			// Give first preference to the vovel already at hand.
			char* v = "aeiou";
			std::set<char> vovels(v, v + strlen(v));
			vovels.erase(c);

			std::set<char>::const_iterator it(vovels.begin());

			if ( search( word.substr(i+1), node->child(c) )
				|| search( word.substr(i+1), node->child(*(it++)) )
				|| search( word.substr(i+1), node->child(*(it++)) )
				|| search( word.substr(i+1), node->child(*(it++)) )
				|| search( word.substr(i+1), node->child(*(it++)) ) )
				return true; // Will early out if one of them returns true
		}

		if ( (i < word.size() - 1) && (c == word[i+1]) )
			continue;

		node = node->child(c);
		if (!node)
			return false;
    }
	if (node->final)
	{
		cout<<*(node->actualWord);
		return true;
	}
	return false;
}

// A wrapper for the recursive search function.
bool Trie::suggestWord(string& query)
{
	std::transform(query.begin(), query.end(), query.begin(), ::tolower);
	return this->search(query, this->mRoot);
}