#include "Dictionary.h"

int main(int argc, char **argv){
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " dictionary_file\n";
        return 0;
    }
    else{
        std::ifstream filestream;
        filestream.open(argv[1]);
        dictionary_project::Dictionary my_dictionary;
        my_dictionary.Load(filestream);
        
        std::string word{};
        int size{0};
        while(true){
            std::cout << "\nEnter CTRL-C anytime to exit.\nEnter word for suggestion: ";
            std::cin >> word;
            std::cout << "Enter number of suggestions: ";
            std::cin >> size;

            std::vector<std::string> answers = my_dictionary.Suggest(word, size);
            for(auto & x : answers){
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
