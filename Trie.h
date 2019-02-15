#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>

#include "TrieNode.h"

namespace trietree_project{
class Trie 
{
  public:
    /* Default Constructor */
    Trie(){root_ = new trienode_project::TrieNode();}//: root_{new trienode_project::TrieNode()}{};
    
    /* one paramter constructor using filestream to textfile */

    /* Destructor */
    ~Trie(){};

    /* creates Trie using given dictionary file 
     * if trie is already loaded, clear and reload
     */ 
    void load();

    bool Insert(const std::string & word_){
        trienode_project::TrieNode * temp_ = root_;
        
        for(size_t i = 0; i < word_.length(); ++i){
            /* Returns the appropriate letter for the children */
            int letter_ = word_[i] - 'a';

            /* Make new node if path doesn't exist */
            if(temp_->children[letter_] == nullptr){
                temp_->children[letter_] = new trienode_project::TrieNode();
            }

            temp_ = temp_->children[letter_];

            /* if isEndOfWord is true and reached last letter, word exists */
            if(i == word_.length() && temp_->isEndOfWord == true){
              return false;
            }
        }
        /* Mark last node as EndOfWord */
        temp_->isEndOfWord = true;
        return true;
    };

    bool Contains(std::string word_){
        trienode_project::TrieNode * temp_ = root_;
        for(size_t i = 0; i < word_.length(); ++i){
            int letter_ = word_[i] - 'a';
            /* Word doesn't exist in trie tree*/
            if(temp_->children[letter_] == nullptr){
                return false;
            }
            temp_ = temp_->children[letter_];
        }
        return(temp_->isEndOfWord);

    };

    /* If given string is in Trie, remove and return true
     * otherwires return false
     */
    bool remove(std::string & word_){
        remove(word_, root_);
    };

    /* empties Trie of all nodes but dummy root, set word count to zero*/
    void Clear();
    /* returns number of words in trie*/
    unsigned int NumWords();
    /* returns number of nodes that have been made in trie but root, calculated on demand*/
    unsigned int CountNodes();

    void Print(){
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            if(root_->children[i] == nullptr){
                continue;
            }
            std::string word_{};
            int letter_ = i + int('a');
            word_ = word_ + char(letter_);
            Print(root_->children[i], word_);
        }
    };



  private:
    trienode_project::TrieNode * root_;

    void Print(trienode_project::TrieNode * node, std::string & word_){
    /* If reached end of word */
        if(node->isEndOfWord){
            std::cout << word_ << " ";
        }
        /* Loop through the children array of node */
        for(int i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            /* If child index isn't nullptr, it has a value */
            if(node->children[i] != nullptr){
                int letter_ = i + int('a');
                std::string full_word = word_ + char(letter_);
                Print(node->children[i], full_word);
            }
            else{
                continue;
            }   
        }
    };

    bool remove(std::string & word_, trienode_project::TrieNode * node){

    };

};

}

#endif 