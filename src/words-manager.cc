#include <random>
#include <iostream>

#include "words-manager.hh"

WordsManager::WordsManager(words_data_t* data, std::string source_file)
 : data_(data)
 , source_file_(source_file)
{
    file_out_.open(source_file_, std::ios::out | std::ios::app);
    if (!file_out_.is_open())
        std::cerr << "no such config file: " << source_file_ << std::endl;
}

WordsManager::~WordsManager()
{
    file_out_.close();
    delete data_;
}

void WordsManager::add_pair(std::string question, std::string answer)
{
    data_->push_back(new pair_t(question, answer));
    if (file_out_.is_open())
        file_out_ << question << ";" << answer << '\n';
}

std::pair<std::string, std::string>* WordsManager::next_word()
{
    // take care of the case the vector is empty
    if (data_->is_empty())
        return new pair_t("", "");
    int random_pos = 0;
    if (data_->size() > 1)
        random_pos = rand(0, data_->size() - 1);
    pair_t* next = (*data_)[random_pos];
    // make a copy
    pair_t* next_copy = new pair_t(next->first, next->second);
    data_->remove(random_pos);
    return next_copy;
}

int WordsManager::rand(int min, int max)
{
    // found here:
    // https://stackoverflow.com/questions/5008804/
    // generating-random-integer-from-a-range

    std::random_device rd; // only used once to initialise (seed) engine
    // random-number engine used (Mersenne-Twister in this case)
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    return uni(rng);
}

void WordsManager::start()
{
    if (file_out_.is_open())
        file_out_.close(); // close output file

    // open for reading
    std::ifstream file_in;
    file_in.open(source_file_, std::ios::in);
    if (!file_in.is_open())
        std::cerr << "no such config file: " << source_file_ << '\n';
    std::string line;
    while (std::getline(file_in, line)) // foreach lines, put the line in data
    {
        auto delim = line.find(";");
        if (delim == std::string::npos)
        {
            std::cerr << "Incorrect line, not enough words" << '\n';
            continue;
        }
        // valid first string
        std::string first = line.substr(0, delim);
        // second string until next delimiter
        auto old_delim = delim + 1;
        delim = line.find(";", delim + 1);
        if (delim != std::string::npos)
        {
            std::cerr << "Incorrect line, too much words" << '\n';
            continue;
        }
        std::string second = line.substr(old_delim, delim);
        pair_t* pair = new pair_t(first, second);
        data_->push_back(pair);
    }
    file_in.close();

    // now open the file for writing
    file_out_.open(source_file_, std::ios::out | std::ios::app);
    if (!file_out_.is_open())
        std::cerr << "no such config file: " << source_file_ << std::endl;
}
