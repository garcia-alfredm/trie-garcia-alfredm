#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

namespace trienode_project{

const int ALPHABET_SIZE = 26;

class TrieNode 
{
  public:
    /* Default constructor*/
    TrieNode(TrieNode * node_parent = nullptr): isEndOfWord{false}{
        for(size_t i = 0; i < ALPHABET_SIZE; ++i){
          children[i] = nullptr;
        }
    };

    //TrieNode * parent;
    TrieNode * children[ALPHABET_SIZE];
    bool isEndOfWord;
    //std::vector<int> occurences;
};

}

#endif
