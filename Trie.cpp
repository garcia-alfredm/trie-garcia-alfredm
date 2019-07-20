#include "Trie.h"

//using namespace trienode_project;

namespace trietree_project{

Trie::Trie(): root_{ new trienode_project::TrieNode()}, number_of_words{0} 
{ }

Trie::Trie(std::ifstream & filestream): root_{new trienode_project::TrieNode()}, number_of_words{0}{
    Clear();
    Load(filestream);
  }

Trie::~Trie(){
    Clear();
  }

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

bool Trie::Insert(const std::string & word_){
    trienode_project::TrieNode * temp_ = root_;
    for(size_t i = 0; i < word_.length(); ++i){
        /* Returns the appropriate letter for the children */
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

bool Trie::Remove(std::string && word_){
    return Remove(std::move(word_), root_);
  }

void Trie::Clear(){
    Clear(root_);
    number_of_words = 0;
    root_ = new trienode_project::TrieNode();
    return;
  }

unsigned int Trie::CountNodes(){
    return CountNodes(root_);
  }

void Trie::Print() const{
    bool empty_trie = true;
    for(size_t i = 0; i < trienode_project::ALPHABET_SIZE; ++i){
        // if index i is empty
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

void Trie::Clear(trienode_project::TrieNode * & node){
    //How many recursive conditions?
    //Node points to nullptr
    //Node has children, is end of word
    //Node has children, is not end of word
    //Node doesn't have children, is end of word
    if(node == nullptr){ return; }
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

unsigned int Trie::CountNodes(trienode_project::TrieNode * & node){
    // Think, how many subnodes does the node have?
    // IF node = nullptr return 0
    // IF node isEndOfWord and has no children: return 1
    // IF node has children: CountNodes(children[a]) + CountNodes(children[b])+...
    //Need to fix count when removing nodes
    unsigned int count{1};

    if(node == nullptr){
        //return count; 
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

void Trie::getSuggested(std::string & word_, std::vector<std::string> & my_vector){
    std::string answer{};
    int letter{0};
    trienode_project::TrieNode * temp = root_;

    for(size_t i{0}; i < word_.length(); ++i){
        answer += word_[i];
        letter = word_[i] - 'a';
        temp = temp->children[letter];
    }
    getSuggested(answer, my_vector, temp);
    return;
  }

void Trie::getSuggested(std::string word_, std::vector<std::string> & my_vector, trienode_project::TrieNode * & node){
    //if node returns EndOfWord, push to vector
    if(node->isEndOfWord){
        my_vector.push_back(word_);
    }
    else if(my_vector.size() >= my_vector.capacity()){
        return;
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
