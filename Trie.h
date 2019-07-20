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
    
    /* one paramter constructor using filestream to textfile */
    Trie(std::ifstream & filestream);

    /* Destructor */
    ~Trie();

    /* creates Trie using given dictionary file 
     * if trie is already loaded, clear and reload
     */ 
    void Load(std::ifstream & filestream);

    bool Insert(const std::string & word_);

    bool Contains(const std::string & word_) const;

    /* If given string is in Trie, remove and return true
     * otherwires return false
     */
    bool Remove(std::string && word_);

    /* empties Trie of all nodes but dummy root, set word count to zero*/
    void Clear();
    /* returns number of words in trie*/
    inline unsigned int NumWords() const { return number_of_words; };
    
    /* returns number of nodes that have been made in trie except root, calculated on demand*/
    unsigned int CountNodes();

    void Print() const;
    
    void getSuggested(std::string & word_, std::vector<std::string> & my_vector);

  private:
    trienode_project::TrieNode * root_;
    unsigned int number_of_words;
    
    bool Remove(std::string && word_, trienode_project::TrieNode * & node);

    void Clear(trienode_project::TrieNode * & node);

    unsigned int CountNodes(trienode_project::TrieNode * & node);
    
    void Print(trienode_project::TrieNode * & node, std::string & word_) const;
    
    void getSuggested(std::string word_, std::vector<std::string> & my_vector, trienode_project::TrieNode * & node);

};

}

#endif 
