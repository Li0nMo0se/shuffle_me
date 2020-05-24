#ifndef WORDS_MANAGER_HH
#define WORDS_MANAGER_HH

#include <string>
#include <fstream>

#include "data.hh"

class WordsManager
{
public:
    using pair_t = std::pair<std::string, std::string>;
    using words_data_t = Data<pair_t>;
    WordsManager(words_data_t* data, std::string source_file = "words.list");
    ~WordsManager();

    // Append a word in the file
    void add_pair(std::string question, std::string answer);

    // Return the next word
    pair_t* next_word();

    // Return a random between between [min, max]
    int rand(int min, int max);

    // Load the data from the file
    void start();


private:
    // data of words
    words_data_t* data_;
    // input file stream
    std::ofstream file_out_;
    // file name
    std::string source_file_;
};

#endif /* ENDIF WORDS_MANAGER_HH */
