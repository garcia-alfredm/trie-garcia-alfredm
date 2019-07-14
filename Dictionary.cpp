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
}
