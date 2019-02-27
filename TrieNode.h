#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

namespace trienode_project{

const int ALPHABET_SIZE = 26;
//const int MAX_WORD_SIZE = 20;

class TrieNode 
{
  public:
    /* Default constructor*/
    TrieNode(TrieNode * node_parent = nullptr): isEndOfWord{false}{
        for(size_t i = 0; i < ALPHABET_SIZE; ++i){
          children[i] = nullptr;
        }
    };
    //copy constructor
    //TrieNode(const T& data, Node next): data(data), next(next) {};


    //TrieNode * parent;
    TrieNode * children[ALPHABET_SIZE];
    bool isEndOfWord;
    //std::vector<int> occurences;
};

}

#endif