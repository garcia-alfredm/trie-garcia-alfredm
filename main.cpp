#include <cassert>

#include "Trie.h"

int main(int argc, char **argv){
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " dictionary_file\n"; 
        return 0;
    }
    else{
        std::ifstream filestream;
        filestream.open(argv[1]);

        trietree_project::Trie my_trie{filestream};
        //my_trie.Load(filestream);
    
        /*
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
        assert(my_trie.Insert("custard"));
        assert(my_trie.Insert("sun"));
        assert(my_trie.Insert("moon"));
        */

        //my_trie.Print();
        //std::cout << "Number of words: " << my_trie.NumWords() << std::endl;
        //std::cout << "Number of nodes: " << my_trie.CountNodes() << std::endl;
        /*
        my_trie.Remove("abe");
        my_trie.Remove("jump");
        my_trie.Remove("cat");
        my_trie.Remove("dad");
        my_trie.Remove("moon");
        */
        
        assert(my_trie.Contains("apple"));
        assert(my_trie.Contains("abe"));
        assert(my_trie.Contains("bat"));
        assert(my_trie.Contains("bark"));
        assert(my_trie.Contains("bag"));
        assert(my_trie.Contains("brother"));
        assert(my_trie.Contains("cat"));
        assert(my_trie.Contains("dad"));
        assert(my_trie.Contains("fun"));
        assert(my_trie.Contains("jump"));
        assert(my_trie.Contains("aardvark"));
        assert(my_trie.Contains("custard"));
        assert(my_trie.Contains("sun"));
        assert(my_trie.Contains("moon"));
        
        //my_trie.Print(); 
        //assert(!my_trie.Remove("castle"));
        std::cout << "Number of words: " << my_trie.NumWords() << std::endl;
        std::cout << "Number of nodes: " << my_trie.CountNodes() << std::endl;

        my_trie.Clear();
        //my_trie.Print();

        std::cout << "All done!\n"; 
    }

    return 0;
}