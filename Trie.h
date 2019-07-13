#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "TrieNode.h"

namespace trietree_project{
class Trie 
{
  public:
    /* Default Constructor */
    Trie(): root_{new trienode_project::TrieNode()}, number_of_words{0} {};
    
    /* one paramter constructor using filestream to textfile */
    Trie(std::ifstream & filestream): root_{ new trienode_project::TrieNode()}, number_of_words{0}{
        //if not empty, clear()
        Load(filestream);
    };

    /* Destructor */
    ~Trie(){
        Clear();
    };

    /* creates Trie using given dictionary file 
     * if trie is already loaded, clear and reload
     */ 
    void Load(std::ifstream & filestream){
        std::string word;
        while(!filestream.eof()){
            filestream >> word;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            Insert(word);
        }
        filestream.close();
    };

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
        ++number_of_words;
        return true;
    };

    bool Contains(const std::string & word_) const{
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
    bool Remove(std::string && word_){
        return Remove(std::move(word_), root_); //->children[letter_]);
    };

    /* empties Trie of all nodes but dummy root, set word count to zero*/
    void Clear(){
        Clear(root_);
        number_of_words = 0;
        root_ = new trienode_project::TrieNode();
        return;
    };
    /* returns number of words in trie*/
    inline unsigned int NumWords() const { return number_of_words; };
    
    /* returns number of nodes that have been made in trie except root, calculated on demand*/
    unsigned int CountNodes(){
        // if root is empty, all children point to null
        //unsigned int node_count{0};
        return CountNodes(root_);//, node_count);
    };

    void Print() const{
        bool empty_trie = true;
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            // if index i is empty
            if(root_->children[i] == nullptr){
                continue;
            }
            empty_trie = false;
            std::string word_{};
            int letter_ = i + int('a');
            word_ = word_ + char(letter_);
            Print(root_->children[i], word_);
        }
        if(empty_trie){
            std::cout << "Trie is empty\n";
            return;
        }
    };

  private:
    trienode_project::TrieNode * root_;
    unsigned int number_of_words;
    
    bool Remove(std::string && word_, trienode_project::TrieNode * & node){
        /* There are five recursive conditions
         * node points to nullptr
         * Node has other children, is not end of word: call remove
         * Node had other children, is end of word: change isEndOfWord to false, return true
         * Node doesn't have other children, is not end of word: call remove, delete node
         * Node doesn't have other children, is end of word: delete node, return true
         */

        /* Node points to null, no such word*/
        if(node == nullptr ){
            return false;
        }
        // get current letter index
        int letter_ = word_[0] - 'a';
        //check if node has children
        bool has_children = true;
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            //avoid testing current index
            if(int(i) == letter_){ continue; }
            else if(node->children[i] != nullptr){
                has_children = false;
                break;
            }
        };
        //if node has other children
        if(has_children){
            if(!node->isEndOfWord){
                return Remove(word_.substr(1), node->children[letter_]);
            }
            //is end of word
            else{
                node->isEndOfWord = false;
                --number_of_words;
                return true;
            }
        }
        //does not have other children
        else{
            if(!node->isEndOfWord){
                return Remove(word_.substr(1), node->children[letter_]);
                delete node;
                node = nullptr;
            }
            //is end of word
            else{
               delete node;
               node = nullptr;
               --number_of_words;
               return true; 
            }
        }
    };

    void Clear(trienode_project::TrieNode * node){
        //How many recursive conditions?
        //Node points to nullptr
        //Node has children, is end of word
        //Node has children, is not end of word
        //Node doesn't have children, is end of word
        if(node == nullptr){ return; }
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            // node has children
            if(node->children[i] != nullptr){
                Clear(node->children[i]);
            }
            //node doesn't have children
            else{
                delete node;
                node = nullptr;
                return;
            }
        }
    };

    unsigned int CountNodes(trienode_project::TrieNode * & node){//, unsigned int count){
        // Think, how many subnodes does the node have?
        // IF node = nullptr return 0
        // IF node isEndOfWord and has no children: return 1
        // IF node has children: CountNodes(children[a]) + CountNodes(children[b])+...
        //Need to fix count when removing nodes
        unsigned int count{1};

        if(node == nullptr){
            //return count; 
            return -1;
        }
        bool has_children = false;
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            if(node->children[i] != nullptr){
                has_children = true;
                break;
            }
        }
        //Node isEndOfWord and has no children
        if(has_children == false){
            return 1;
        }
        //Node has children
        for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
            if(node->children[i] != nullptr){
                count = count + CountNodes(node->children[i]);//, count); 
            }
        }
        return count;
    };
    
    void Print(trienode_project::TrieNode * & node, std::string & word_) const {
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
