#include "Dictionary.h"

namespace dictionary_project{

Dictionary::Dictionary(): my_trie{trietree_project::Trie()} 
{ }

Dictionary::Dictionary(std::ifstream & filename): my_trie{trietree_project::Trie(filename)}
{ }

Dictionary::~Dictionary(){
    my_trie.Clear();
  }

void Dictionary::Load(std::ifstream & filestream){
    my_trie.Load(filestream);
  }
bool Dictionary::isLegalWord(const std::string& word_) const{
    return my_trie.Contains(word_);
  }

std::vector<std::string> Dictionary::Suggest(std::string & word_, int & size_){
     //throw error code; or rather have AutoComplete class handle
    // return;    
    std::vector<std::string> my_vector(size_);
    my_trie.getSuggested(word_, my_vector);
    return my_vector;
  }
}
