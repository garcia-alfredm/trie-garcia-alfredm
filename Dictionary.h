#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"

#include <algorithm>

namespace dictionary_project{
class Dictionary{
  public:
    /* Default Constructor */
    Dictionary();

    /* One parameter constructor */
    Dictionary(std::ifstream & filestream);
    
    /* Destructor */
    ~Dictionary();
    
    /* Use filestream object of populate Trie */
    void Load(std::ifstream & filestream);
    
    /* Determines whether string is legal word */
    bool isLegalWord(const std::string & word_) const;
    
    /* Calls NumWords() to determine size of trie */
    inline unsigned int Word_Count(){ return my_trie.NumWords();};
    
    /* Returns a vector of suggested words
     * @word_: string values used to determine similar words
     * @size_: number of suggested words
     * Precondition: Trie is populated with legal values
     * Postcondition: a vector of suggested words is returned
     */
    std::vector<std::string> Suggest(std::string & word_, int & size_);

  private:
    trietree_project::Trie my_trie;

    /* Create a comparator with a functor to handle comparing strings by length
     */
    struct Comparator{
        bool operator()(const std::string & first, const std::string & second){
            return first.size() < second.size();
        }
    };
};
}

#endif
