#ifndef WORDS_MANAGER_HH
#define WORDS_MANAGER_HH

#include <vector>
#include <string>

class WordsManager
{
public:
    WordsManager(std::string source_file = "words.list");
    ~WordsManager();

    // Append a word in the file
    void add_word(std::string str_to_add);

    // Return the next word
    std::string next_word();

private:
    std::vector<std::string> words_;
    int curr_pos_;
};

#endif /* ENDIF WORDS_MANAGER_HH */
