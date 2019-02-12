#include <cassert>

#include "Trie.h"

int main(int argc, char **argv){
    //if(argc != 2){std::cout << "Usage: " << argv[0] << " wordfile\n"; return 0;}
    trietree_project::Trie my_trie;
    
    assert(my_trie.Insert("apple"));
    //assert(my_trie.Insert("abe"));
    assert(my_trie.Insert("bat"));
    //assert(my_trie.Insert("bark"));
    //assert(my_trie.Insert("bag"));
    //assert(my_trie.Insert("bruh"));
    assert(my_trie.Insert("cat"));
    assert(my_trie.Insert("dad"));
    assert(my_trie.Insert("fun"));
    

    std::cout << "All done!\n";
    my_trie.Print();
    std::cout << std::endl;

    return 0;
}