#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"

namespace dictionary_project{
class Dictionary{
  public:
    /* Default Constructor */
    Dictionary();
    /* One parameter constructor */
    Dictionary(std::ifstream & filestream);
    /* Destructor */
    ~Dictionary();
    void Load(std::ifstream & filestream);
    bool isLegalWord(const std::string & word_) const;
    inline unsigned int Word_Count(){ return my_trie.NumWords();};
    std::vector<std::string> Suggest(std::string & word_, int & size_);

  private:
    trietree_project::Trie my_trie;
};
}

#endif
