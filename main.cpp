#include <cassert>

#include "Trie.h"

int main(int argc, char **argv){
    //if(argc != 2){std::cout << "Usage: " << argv[0] << " wordfile\n"; return 0;}
    trietree_project::Trie my_trie;
    
    assert(my_trie.Insert("apple"));
    assert(my_trie.Insert("abe"));
    assert(my_trie.Insert("bat"));
    assert(my_trie.Insert("bark"));
    assert(my_trie.Insert("bag"));
    assert(my_trie.Insert("brother"));
    assert(my_trie.Insert("cat"));
    assert(my_trie.Insert("dad"));
    assert(my_trie.Insert("fun"));
    assert(my_trie.Insert("jump"));
    assert(my_trie.Insert("aardvark"));
    assert(my_trie.Insert("custered"));
    assert(my_trie.Insert("sun"));
    assert(my_trie.Insert("moon"));
    
    my_trie.Print();
    std::cout << "All done!\n";

    return 0;
}