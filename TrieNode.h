#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

namespace trienode_project{

const int ALPHABET_SIZE = 52;

class TrieNode{
  public:
    /* Default constructor*/
    TrieNode(TrieNode * node_parent = nullptr): isEndOfWord{false}{
        for(size_t i = 0; i < ALPHABET_SIZE; ++i){
          children[i] = nullptr;
        }
    };

    TrieNode * children[ALPHABET_SIZE];
    bool isEndOfWord;
};

}

#endif
