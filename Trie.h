#ifndef TRIE_H
#define TRIE_H

#include <string>

#include "TrieNode.h"

namespace trietree_project{
class Trie 
{
  public:
    /* Default Constructor */
    Trie(): root_{new trienode_project::TrieNode()}{};
    /* one paramter constructor using filestream to textfile */
    /* Destructor */
    ~Trie(){};

    bool Insert(const std::string & word_){
        trienode_project::TrieNode * temp_ = root_;
        
        for(size_t i{0}; i < word_.length(); ++i){
            /* Returns the appropriate index for the children attribute */
            int index = word_[i] - int('a');

            /* Make new node if path doesn't exist */
            if(temp_->children[index] == nullptr){
                temp_->children[index] = new trienode_project::TrieNode();
            }
            /* if isendofword is true and reached last letter, word exists */
            else if(i == word_.length() - 1 && temp_->isEndOfWord == true){
              return false;
            }
            temp_ = temp_->children[index];
        }
        /* Mark last node as EndOfWord */
        temp_->isEndOfWord = true;
        return true;
    };

    bool Contains(std::string word_);
    /* empties Trie of all nodes but dummy root, set word count to zero*/
    void Clear();
    /* returns number of words in trie*/
    unsigned int NumWords();
    /* returns number of nodes that have been made in trie but root, calculated on demand*/
    unsigned int CountNodes();

  private:
    trienode_project::TrieNode * root_;

};

}

#endif 