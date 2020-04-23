#pragma once

#include <list>
#include <string>

template <typename T>
class Data
{
public:
    Data()=default;
    ~Data()=default;

    /* Modifier */
    void push_back(T t);

    // get an element at the position i
    // if i is invalid, return the first element
    T& get(int i);
    T& operator[](int i);

    // remove elt at the position i
    // if i is invalid, do nothing
    void remove(int i);

    /* Capacity */
    bool is_empty();
    int size();

private:
    std::list<T> list_;
};

#include "data.hxx"
