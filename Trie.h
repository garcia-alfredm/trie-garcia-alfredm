#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "TrieNode.h"

namespace trietree_project{
class Trie{
  public:
    /* Default Constructor */
    Trie();
    
    /* One parameter constructor with initizliation list
     * @filestream: ifstream object linked to word list
     * Postcondition: any existing trie is cleared. Populated with new words
     */ 
    Trie(std::ifstream & filestream);

    /* Destructor calls Clear() */
    ~Trie();

    /* Creates trie using given word file
     * @filesteam: ifstream object linked to word list
     * Postcondition: existing trie is cleared. Populated with new words
     */
    void Load(std::ifstream & filestream);

    /* Word is inserted to trie with an iterative approach 
     * @word_: const string to be inserted to trie
     * Precondition: Trie has been initialized 
     * Postcondition: word has been inserted to trie, size incremented
     */
    bool Insert(const std::string & word_);

    /* Checks if word already exists in trie
     * @word_: string value to be check
     * Precondition: trie has been initialized;
     */
    bool Contains(const std::string & word_) const;

    /* Removes l-value reference string */
    bool Remove(std::string && word_);

    /* empties Trie of all nodes but dummy root, set word count to zero*/
    void Clear();

    /* returns number of words in trie*/
    inline unsigned int NumWords() const { return number_of_words; };
    
    /* returns number of nodes that have been made in trie except root, calculated on demand*/
    unsigned int CountNodes();

    /* Print all contents of trie nodes in alphabetical order */
    void Print() const;
    
    /* Returns a vector of suggested words
     * @word_: string value used to determine suggested words
     * @my_vector: string vector that holds suggested words
     * Precondition: Trie will be populated with values
     */
    void getSuggested(std::string & word_, std::vector<std::string> & my_vector);

  private:
    trienode_project::TrieNode * root_;
    unsigned int number_of_words;
    
    int getIndex(const char & character_) const;

    char getCharacter(const int & value_) const;
    
    /* Removes target word recursively
     * @word_: l-value string to be removed
     * @node: current trie node, recursive target
     * Postcondition: word_ is not longer valid target within trie
     */
    bool Remove(std::string && word_, trienode_project::TrieNode * & node);

    /* Clears the trie of allocated data
     * @node: TrieNode used for crawling recursivly thru trie
     * Precondition: Trie is populated with data
     * Postcondition: Trie is depopulated and dynamically allocated data is removed
     */
    void Clear(trienode_project::TrieNode * & node);

    /* Counts nodes on deman
     * @node: TrieNode that crawls thru trie
     */
    unsigned int CountNodes(trienode_project::TrieNode * & node);
    
    /* Prints all contents of Trie in alphabetical order */
    void Print(trienode_project::TrieNode * & node, std::string & word_) const;
    
    /* Returns a vector of suggested words
     * @word_: string value used to determine suggested words
     * @my_vector: string vector that holds suggested words
     * Precondition: Trie will be populated with values
     */
    void getSuggested(std::string word_, std::vector<std::string> & my_vector, trienode_project::TrieNode * & node);

};

}

#endif 
