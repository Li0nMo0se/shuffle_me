template <typename T>
void Data<T>::push_back(T t)
{
    list_.push_back(t);
}

template <typename T>
T& Data<T>::get(int i)
{
    return this[i];
}

template <typename T>
T& Data<T>::operator[](int i)
{
    auto it = list_.begin();
    if (i < 0 || i >= (int)list_.size())
        return *it;
    while (i > 0)
    {
        i--;
        it++;
    }
    return *it;
}

template <typename T>
bool Data<T>::is_empty()
{
    return list_.empty();
}

template <typename T>
int Data<T>::size()
{
    return list_.size();
}

template <typename T>
void Data<T>::remove(int i)
{
    if (i >= (int)list_.size() || i < 0)
        return;
    auto it = list_.begin();
    while (i > 0)
    {
        i--;
        it++;
    }
    list_.erase(it);
}
