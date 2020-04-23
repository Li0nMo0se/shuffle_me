#include <random>
#include <iostream>

#include "words-manager.hh"

WordsManager::WordsManager(words_data_t* data, std::string source_file)
 : data_(data)
 , source_file_(source_file)
{}

WordsManager::~WordsManager()
{
    // Close file?
    file_out_.close();
    delete data_;
}

void WordsManager::add_word(std::string str_to_add)
{
    data_->push_back(str_to_add);
    file_out_ << str_to_add << std::endl;
}

std::string* WordsManager::next_word()
{
    // take care of the case the vector is empty
    if (data_->is_empty())
        return new std::string("");
    int random_pos = 0;
    if (data_->size() > 1)
        random_pos = rand(0, data_->size() - 1);
    std::string* next = new std::string((*data_)[random_pos]);
    data_->remove(random_pos);
    return next;
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
        std::cerr << "no such config file: " << source_file_ << std::endl;
    std::string line;
    while (std::getline(file_in, line)) // foreach lines, put the line in data
        data_->push_back(line);
    file_in.close();

    // now open the file for writing
    file_out_.open(source_file_, std::ios::out | std::ios::app);
    if (!file_out_.is_open())
        std::cerr << "no such config file: " << source_file_ << std::endl;
}
