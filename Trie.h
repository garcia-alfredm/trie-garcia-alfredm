#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <utility>

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
                temp_->children[letter_] = new trienode_project::TrieNode(temp_);
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
    bool Remove(std::string & word_){
        //int letter_ = word_[0] - 'a';
        //word_ = word_.substr(1,std::string::npos);
        return Remove(std::move(word_), root_); //->children[letter_]);
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
    
    bool Remove(std::string && word_, trienode_project::TrieNode * & node){
        /* There are five recursive conditions
         * Where node isn't EOW and has child/ren: do nothing and return true
         * Where node isn't EOW and has no children: delete node, recursive step back
         * Where node IS EOW and has no childrn: delete node, recursive step back
         * Where node is EOW AND has children: mark EOW false and return true
         */
        /* Node points to null, no such word*/
        if(node == nullptr ){
            std::cout << "No such word.\n";
            return false;
        }
        /* If we have not reached end of word. check if node has children */
        else if(node->isEndOfWord == false){
            /* index for next value*/
            int letter_ = word_[0] - 'a';
            bool has_children = true;

            /*Test if node has children*/
            /* Use a helper function that determines if more than 2 children*/
            for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
                //avoid testing existing index
                if(int(i) == letter_){ continue; }

                else if(node->children[i] != nullptr){
                    has_children = false;
                    break;
                }
            }
            //word_ = word_.substr(1);

            /* Doesn't have children, can remove*/
            if(!has_children){
                Remove(word_.substr(1), node->children[letter_]);
                delete node;
                node = nullptr;
            }
            /*Has children, don't remove*/
            else{
                Remove(word_.substr(1), node->children[letter_]);
                return true;
            }
        }
        else if(node->isEndOfWord == true){
            bool is_empty = true;
            /*Test if EndOfWord node has child*/
            for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
                if(node->children[i] != nullptr){
                    is_empty = false;
                }
            }
            /* has no other child pointers */
            if(is_empty == true){
                delete node;
            }
            /* has other child pointers */
            else{
                node->isEndOfWord = false;
                return true;
            }
        }
    };
    
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
};

}

#endif 