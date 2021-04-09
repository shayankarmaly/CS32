#include "StudentSpellCheck.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck()
{
    remove(root);
}


bool StudentSpellCheck::load(std::string dictionaryFile)
{
    ifstream dict(dictionaryFile);
    if(!dict)
    {
        return false; // base case if file cannot be opened
    }
    
    delete root; // delete the old dictionary
    string lines;
    root = new TrieNode('\0'); // make a new one
    TrieNode* node = root;
    
    while(getline(dict, lines))
    {
        justInsert(node, lines); // insert the new dictionary based on the given dictionary
    }
    
    return true;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions)
{
    if(search(word, root)) // 0(2L)
    {
        return true;
    }
    
    suggestions.clear(); // 0(maxSuggestions)
    for(int k = 0; k < word.size(); k++) //L*0(L)
    {
        string t = word;
        for (int i = 0; i < 27; i++) // iterates through the alphabet; 0(L)
        {
            if( i == 26)
            {
                t[i] = '\'';
            }
            
            else
            {
                t[i] = i + 'a';
            }
            if(search(t, root) && suggestions.size() != max_suggestions) //0(2L)
            {
                suggestions.push_back(t);
            }
        }
        t = word;
    }
    return false;
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems)
{
    string t;
    vector<Position> pos; // holds the positions of all words in given line
    int tracker = 0; int end = 0; int previous = -1; int start = 0;
    vector<string> wordList; // holds every possible word
    
    for (int k = 0; k < line.size(); k++) // 0(S)
    {
        if(line[k] == '\'' || isalpha(line[k]))
        {
            if(t == "")
            {
                start = k;
            }
            t.push_back(line[k]);
        }
        
        else
        {
            // invalid ,word ends
            if(t != "" && k != 0)
            { // add this word
                wordList.push_back(t);
            }
            end = k; // used to track its end
            t = "";
        }
        
        if(start != previous && start < end) // checking if there is a valid word, if so add it
        {
            if(line[start] != '\'' && !isalpha(line[start]))
            {
                continue;
            }
            
            previous = start;
            Position pro;
            pro.start = start;
            pro.end = end -1;
            pos.push_back(pro);
        }
    }
    
    
    if(((isalpha(t[t.size()- 1])) && !t.empty() )|| t[t.size() - 1] == '\'')
    {
        //only executes if the last word is valid
        Position pro;
        wordList.push_back(t);
        
        pro.start = start;
        pro.end = line.size() - 1;
        pos.push_back(pro);
        
    }
    
    for (int j = 0; j < wordList.size(); j++) // 0(W*L)
    {
        if(!search(wordList[j] , root)) // 0(2L)
        {
            problems.push_back(pos[j]);
        }
    }
}


void StudentSpellCheck::remove(StudentSpellCheck::TrieNode* node)
{
    if(node == nullptr) // base case if node is nullptr there's nothing in the node
    {
        return;
    }
    
    for (int k = 0; k < 27; k++) // iterate through each child of the given node
    {
        remove(node -> children[k]); // remove all TrieNodes children first
    }
    
    delete node; // then delete the given node
}


bool StudentSpellCheck:: search(string & wurd, StudentSpellCheck::TrieNode* node)
{
    for (int k = 0; k < wurd.size(); k++)
    {
        wurd[k] = tolower(wurd[k]); // makes every word lower case, just in case it's not already
    }
    
    TrieNode* temp = getNode(wurd, node);
    
    return temp != nullptr && temp -> word;
}


void StudentSpellCheck:: justInsert(StudentSpellCheck::TrieNode* node, string lines)
{
    for (int k = 0; k < lines.size(); k++)
    {
        char a = lines.at(k);
        a = tolower(a); // making sure its lower case
        
        if(isalpha(a)) // checking if its a letter
        {
            if(node -> children[a - 'a'] == nullptr)
            {
                node -> children[a - 'a'] = new TrieNode(a);
            }
            
            node = node -> children[a - 'a'];
        }
        
        if(a == '\'')
        {
            if(node -> children[26] == nullptr)
            {
                node->children[26] = new TrieNode(a);
            }
            
            node = node -> children[26];
        }
        
        else
        {
            continue;
        }
    }
    
    node -> word = true;
    // set to true because we've reached the last position!
}

StudentSpellCheck::TrieNode* StudentSpellCheck :: getNode(string wurd, StudentSpellCheck::TrieNode* node)
{
    TrieNode* temp = node;
    
    for (int k = 0; k < wurd.size(); k++)
    {
        char a = wurd.at(k);
        if(isalpha(a))
        {
            if(temp -> children[a - 'a'] == nullptr)
            {
                return nullptr; // return nullptr if there's nothing
            }
            
            temp = temp -> children[a - 'a'];
        }
        
        if(a == '\'')
        {
            if(temp -> children[26] == nullptr)
            {
                return nullptr;// return nullptr if there's nothing
            }
            
            temp = temp -> children[26];
        }
        
        else
        {
            return nullptr;
        }
    }
    return temp;
}
