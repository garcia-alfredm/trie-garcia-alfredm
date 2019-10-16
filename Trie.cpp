#include "Trie.h"

//using namespace trienode_project;

namespace trietree_project{

/* Default Construction using initialization list */
Trie::Trie(): root_{ new trienode_project::TrieNode()}, number_of_words{0} 
{ }

/* One parameter constructor with initizliation list
 * @filestream: ifstream object linked to word list
 * Postcondition: any existing trie is cleared. Populated with new words
 */ 
Trie::Trie(std::ifstream & filestream): root_{new trienode_project::TrieNode()}, number_of_words{0}{
    Load(filestream);
  }

/* Destructor calls Clear() */
Trie::~Trie(){
    Clear();
  }

/* Creates trie using given word file
 * @filesteam: ifstream object linked to word list
 * Postcondition: existing trie is cleared. Populated with new words
 */
void Trie::Load(std::ifstream & filestream){
    Clear();
    std::string word;
    while(!filestream.eof()){
        filestream >> word;
        //std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        Insert(word);
    }
    filestream.close();
  }

/* Word is inserted to trie with an iterative approach 
 * @word_: const string to be inserted to trie
 * Precondition: Trie has been initialized 
 * Postcondition: word has been inserted to trie, size incremented
 */
bool Trie::Insert(const std::string & word_){
    trienode_project::TrieNode * temp_ = root_;
    for(size_t i = 0; i < word_.length(); ++i){
        /* Returns the appropriate letter for the child node */
        int letter_ = getIndex(word_[i]);

        /* Make new node if path doesn't exist */
        if(temp_->children[letter_] == nullptr){
            temp_->children[letter_] = new trienode_project::TrieNode(temp_);
        }
        temp_ = temp_->children[letter_];

        /* if isEndOfWord is true and reached last letter, word exists */
        if(i == word_.length() && temp_->isEndOfWord == true){
            return false;
        }
    }
    /* Mark last node as EndOfWord */
    temp_->isEndOfWord = true;
    ++number_of_words;
    return true;
  }

/* Checks if word already exists in trie
 * @word_: string value to be check
 * Precondition: trie has been initialized;
 */
bool Trie::Contains(const std::string & word_) const{
   trienode_project::TrieNode * temp_ = root_;
   for(size_t i = 0; i < word_.length(); ++i){
        int letter_ = getIndex(word_[i]);
        /* Word doesn't exist in trie tree*/
        if(temp_->children[letter_] == nullptr){
            return false;
        }
        temp_ = temp_->children[letter_];
    }
    return(temp_->isEndOfWord);
  }

/* Removes l-value reference string */
bool Trie::Remove(std::string && word_){
    return Remove(std::move(word_), root_);
  }

/* Clears trie of dynamically allocated space */
void Trie::Clear(){
    Clear(root_);
    number_of_words = 0;
    root_ = new trienode_project::TrieNode();
    return;
  }

/* Calculates number of nodes in trie on demand */
unsigned int Trie::CountNodes(){
    return CountNodes(root_);
  }

/* Print all contents of trie node in alphabetical order */
void Trie::Print() const{
    bool empty_trie = true;
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        // if index i is empty, continue to next index
        if(root_->children[i] == nullptr){
            continue;
        }
        empty_trie = false;
        std::string word_{};
        char letter_;
        letter_ = getCharacter(i);
        //int letter_ = i + int('a');
        word_ += letter_;
        Print(root_->children[i], word_);
    }
    if(empty_trie){
        std::cout << "Trie is empty\n";
        return;
    }
  }

int Trie::getIndex(char & character_){
    int letter_{0};
    /* ASCII alphabet values for A-Z are 65-90 respec.*/
    letter_ = character_ - 'A';
    /* handle lower-case characters*/
    if(letter_ >= 32){
        letter_ -= 6;
    }
    return letter_;
}

char getCharacter(int & value_){
    int letter_{0};
    /* Index value turns to appropriate ASCII value */
    letter_ = value_ + 65;
    /* handle lowercase letters */
    if( letter_ > 90){
        letter_ += 6;
    }
    return char(letter_);
}

/* Removes target word 
 * @word_: l-value string to be removed
 * @node: current trie node, recursive target
 * Postcondition: word_ is not longer valid target within trie
 * node->isEndOfWord is set to false, no change in trie size
 */
bool Trie::Remove(std::string && word_, trienode_project::TrieNode * & node){
    /* Node points to null, no such word*/
    if(node == nullptr ){
        return false;
    }
    // get current letter index
    int letter_ = getIndex(word_[0]);
    
    /* if node isn't EndOfWord*/
    /* and if is not at end of word */
    /* handles the case if target word has already been deleted but exists in trie */
    if(!node->isEndOfWord && word_.length() >= 1){
        return Remove(word_.substr(1), node->children[letter_]);
    }
    /* iterated to end of word and isEndOfWord */
    else{
        node->isEndOfWord = false;
        --number_of_words;
        return true;
    }
}

/* Clears the trie of allocated data
 * @node: TrieNode used for crawling recursivly thru trie; post-order traversal
 * Precondition: Trie is populated with data
 * Postcondition: Trie is depopulated and dynamically allocated data is removed
 */
void Trie::Clear(trienode_project::TrieNode * & node){
    /* Recursive condition */
    if(node == nullptr){ return; }
    /* Loop thru array of TrieNodes */
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        // if node has children, clear their values
        if(node->children[i] != nullptr){
            Clear(node->children[i]);
        }
    }
    /* finished iterating thru children */
    delete node;
    node = nullptr;
    return; 
}

/* Counts nodes on demand, post-order recursion
 * @node: TrieNode that crawls thru trie
 */
unsigned int Trie::CountNodes(trienode_project::TrieNode * & node){
    unsigned int count{0};

    /* Avoid counting an empty node */
    if(node == nullptr){
        return -1;
    }
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        if(node->children[i] != nullptr){
            count += CountNodes(node->children[i]); 
        }
    }
    return count + 1;
  }

/* Prints all contents of Trie in alphabetical order */
void Trie::Print(trienode_project::TrieNode * & node, std::string & word_)const {
    /* If reached end of word */
    if(node->isEndOfWord){
        std::cout << word_ << " ";
    }
    /* Loop through the children array of node */
    for(int i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        /* If child index isn't nullptr, it has a value */
        if(node->children[i] != nullptr){
            char letter_;
            letter_ = getCharacter(i);
            std::string full_word = word_ + letter_;
            Print(node->children[i], full_word);
        }
        else{
            continue;
        }   
    }
  }

/* Returns a vector of suggested words
 * @word_: string value used to determine suggested words
 * @my_vector: string vector that holds suggested words
 * Precondition: Trie will be populated with values
 */
void Trie::getSuggested(std::string & word_, std::vector<std::string> & my_vector){
    int letter{0};
    trienode_project::TrieNode * temp = root_;

    for(size_t i{0}; i < word_.length(); ++i){
        letter = getIndex( word_[i]);
        temp = temp->children[letter];
    }
    getSuggested(word_, my_vector, temp);
    return;
  }

/* Returns a vector of suggested words
 * @word_: string value used to determine suggested words
 * @my_vector: string vector that holds suggested words
 * Precondition: Trie will be populated with values
 */
void Trie::getSuggested(std::string word_, std::vector<std::string> & my_vector, trienode_project::TrieNode * & node){
    //if node returns EndOfWord, push to vector
    if(node->isEndOfWord){
        my_vector.push_back(word_);
    }
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        std::string copy_{word_};
        //children[i] isn't empty
        if(node->children[i] != nullptr){
            char value_ = getCharacter(i);
            copy_.push_back(value);
            getSuggested(copy_, my_vector, node->children[i]);
        }
    }
    //current node is a word and has no children
    return;
  }
}
