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
    Clear();
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
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
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
        int letter_ = word_[i] - 'a';

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
        int letter_ = word_[i] - 'a';
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
        // if index i is empty, continue to next iteration
        if(root_->children[i] == nullptr){
            continue;
        }
        empty_trie = false;
        std::string word_{};
        int letter_ = i + int('a');
        word_ = word_ + char(letter_);
        Print(root_->children[i], word_);
    }
    if(empty_trie){
        std::cout << "Trie is empty\n";
        return;
    }
  }

/* Removes target word recursively
 * @word_: l-value string to be removed
 * @node: current trie node, recursive target
 * Postcondition: word_ is not longer valid target within trie
 */
bool Trie::Remove(std::string && word_, trienode_project::TrieNode * & node){
    /* There are five recursive conditions
     * node points to nullptr
     * Node has other children, is not end of word: call remove
     * Node had other children, is end of word: change isEndOfWord to false, return true
     * Node doesn't have other children, is not end of word: call remove, delete node
     * Node doesn't have other children, is end of word: delete node, return true
     */

    /* Node points to null, no such word*/
    if(node == nullptr ){
        return false;
    }
    // get current letter index
    int letter_ = word_[0] - 'a';
    //check if node has children
    bool has_children = true;
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        //avoid testing current index
        if(int(i) == letter_){ continue; }
        else if(node->children[i] != nullptr){
            has_children = false;
            break;
        }
    };
    //if node has other children
    if(has_children){
        if(!node->isEndOfWord){
            return Remove(word_.substr(1), node->children[letter_]);
        }
        //is end of word
        else{
            node->isEndOfWord = false;
            --number_of_words;
            return true;
        }
    }
    //does not have other children
    else{
        if(!node->isEndOfWord){
            return Remove(word_.substr(1), node->children[letter_]);
            delete node;
            node = nullptr;
        }
        //is end of word
        else{
           delete node;
           node = nullptr;
           --number_of_words;
           return true; 
        }
    }
  }

/* Clears the trie of allocated data
 * @node: TrieNode used for crawling recursivly thru trie
 * Precondition: Trie is populated with data
 * Postcondition: Trie is depopulated and dynamically allocated data is removed
 */
void Trie::Clear(trienode_project::TrieNode * & node){
    /* Recursive condition */
    if(node == nullptr){ return; }
    /* Loop thru array of TrieNodes */
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        // node has children
        if(node->children[i] != nullptr){
            Clear(node->children[i]);
        }
        //node doesn't have children
        else{
            delete node;
            node = nullptr;
            return;
        }
    }
  }

/* Counts nodes on demand
 * @node: TrieNode that crawls thru trie
 */
unsigned int Trie::CountNodes(trienode_project::TrieNode * & node){
    // IF node = nullptr return 0
    // IF node isEndOfWord and has no children: return 1
    // IF node has children: CountNodes(children[a]) + CountNodes(children[b])+...
    unsigned int count{1};

    if(node == nullptr){
        return -1;
    }
    bool has_children = false;
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        if(node->children[i] != nullptr){
            has_children = true;
            break;
        }
    }
    //Node isEndOfWord and has no children
    if(has_children == false){
        return 1;
    }
    //Node has children
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        if(node->children[i] != nullptr){
            count = count + CountNodes(node->children[i]);//, count); 
        }
    }
    return count;
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
            int letter_ = i + int('a');
            std::string full_word = word_ + char(letter_);
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
    //std::string answer{};
    int letter{0};
    trienode_project::TrieNode * temp = root_;

    for(size_t i{0}; i < word_.length(); ++i){
        //answer += word_[i];
        letter = word_[i] - 'a';
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
            copy_ += char(i + int('a'));
            getSuggested(copy_, my_vector, node->children[i]);
        }
    }
    //current node is a word and has no children
    return;
  }
}
