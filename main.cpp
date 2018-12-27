#include <cassert>
#include <iostream>

#include "Trie.h"

int main(int argc, char **argv){
    //if(argc != 2){std::cout << "Usage: " << argv[0] << " wordfile\n"; return 0;}
    trietree_project::Trie my_trie;
    
    assert(my_trie.Insert("add"));
    assert(my_trie.Insert("add"));
    std::cout << "All done!\n";

    return 0;
}