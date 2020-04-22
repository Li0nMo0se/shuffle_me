#include "words-manager.hh"

#include <fstream>

WordsManager::WordsManager(std::string source_file)
 : words_(std::vector<std::string>())
 , curr_pos_(0)
{
    std::ifstream in_file(source_file);
    std::string line;
    while (in_file >> line)
    {
        // TODO
    }
}

WordsManager::~WordsManager()
{
    // Close file?
}

void WordsManager::add_word(std::string str_to_add)
{
    words_.push_back(str_to_add);
}

std::string WordsManager::next_word()
{
    // take care of the case the vector is empty
    if (words_.empty())
        return "List of words empty. Add words.";
    std::string next = words_[curr_pos_];
    curr_pos_ = (curr_pos_ + 1) % words_.size();
    return next;
}
