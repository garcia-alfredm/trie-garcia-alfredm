#include "Dictionary.h"

namespace dictionary_project{

/* Default Constructor */
Dictionary::Dictionary(): my_trie{trietree_project::Trie()} 
{ }
/* One parameter constructor */
Dictionary::Dictionary(std::ifstream & filename): my_trie{trietree_project::Trie(filename)}
{ }
/* Destructor*/
Dictionary::~Dictionary(){
    my_trie.Clear();
  }
/* Use filestream object to populate Trie */
void Dictionary::Load(std::ifstream & filestream){
    my_trie.Load(filestream);
  }
/* Determines whether string is legal word */
bool Dictionary::isLegalWord(const std::string& word_) const{
    return my_trie.Contains(word_);
  }
/* Returns a vector of suggested words
 * @word_: string values used to determine similar words
 * @size_: number of suggested words
 * Precondition: Trie is populated with legal values
 * Postcondition: a vector of suggested words is returned
 */
std::vector<std::string> Dictionary::Suggest(std::string & word_, int & size_){
    std::vector<std::string> my_vector;
    Comparator comparator;

    my_trie.getSuggested(word_, my_vector);

    /* trie structure means vector is in alphabetical order
     * use stable sort with fuctor to sort by length
     */
    std::stable_sort(my_vector.begin(), my_vector.end(), comparator);
    my_vector.resize(size_);

    return my_vector;
  }
}
