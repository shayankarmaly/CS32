#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck
{
public:
    // empty root node
    StudentSpellCheck() { root = new TrieNode('\0'); }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

        struct TrieNode // Trie Struct that holds the English Alphabet and dummy node that points to the root
    {
        TrieNode(char ch)
        {
            
        }
        
        bool word = false;
        TrieNode* children[27] = { nullptr };
        char a;
    };
    
    StudentSpellCheck::TrieNode* root;
    
    void remove(StudentSpellCheck::TrieNode* node); // removes all the nodes starting from the given node
    bool search(std::string& wurd, StudentSpellCheck::TrieNode* node); // checks if a word is in the dictionary using the given TrieNode* node
    void justInsert(StudentSpellCheck::TrieNode* node, std::string lines); // places a new word into the trie when called
    StudentSpellCheck::TrieNode* getNode(std::string wurd, StudentSpellCheck::TrieNode* node); // starts at the given starting point and returns a pointer to the node with the last character of the string given
};

#endif  // STUDENTSPELLCHECK_H_
