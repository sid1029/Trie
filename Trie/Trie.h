#ifndef TRIE_H
#define TRIE_H

#include <cctype>
typedef unsigned int uint;

using namespace std;

class Trie
{
public:
	static const int NUM_LETTERS = 26;
	struct TrieNode
	{
		TrieNode() : final(false), actualWord(NULL) { std::memset(children, NULL, sizeof(children)); }

		~TrieNode()	{
			for(int i = 0;i < NUM_LETTERS;++i)
				if(children[i]) delete children[i];
			if(actualWord)
				delete actualWord;
		}
 
		inline TrieNode*& child(const char c) {	return children[tolower(c)-'a']; }

		TrieNode* children[NUM_LETTERS];
		bool final;
		std::string* actualWord;
	};

	Trie() : mRoot(new TrieNode) {}
 
	~Trie() { delete mRoot; }
	
	void add(string word);
 
	bool search(string& word, Trie::TrieNode* node);

	bool suggestWord(string& query);

	inline bool isVowel(const char& c) { return ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')); }

private:
	TrieNode* mRoot;
};

#endif // TRIE_H