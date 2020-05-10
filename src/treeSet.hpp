#pragma once

#include "Binarytree.hpp"

#include <functional>

// Uwaga! Kod powinien byc odporny na bledy i kazda z metod jezeli zachodzi niebezpieczenstwo wywolania z niepoprawnymi parametrami powinna zglaszac odpowiednie wyjatki!

// klasa reprezentujaca zbiór (set) oparty na drzewie (BST/AVL)
template <typename T>
class Set
{
public:
    class iterator;
    Set() = default;
    Set(const Set<T> &source) = default;
    Set<T> &operator=(const Set<T> &source) = default;
    Set(Set<T> &&source) = default;
    Set<T> &operator=(Set<T> &&source) = default;
    ~Set() = default;

private:
    // drzewo BST
    Binarytree<T> bst_;

public:
    // zwraca ilość elementów
    std::size_t size() const { return bst_.size(); };
    // zwraca true gdy zbiór jest pusty, lub false w innym przypadku
    bool empty() const { return bst_.empty(); };
    // dodaje element - zwraca iterator do dodanego elementu i true, lub iterator do istniejącego elementu i false, jeżeli z jakiegoś powodu nie udało się dodać/znaleźć to zwraca false i to samo co end()
    std::pair<iterator, bool> insert(const T &value)
    {
        bool temp = false;
        std::pair<typename Set<T>::iterator, bool> p;
        if (!bst_.contains(value))
        {
            bst_.put(value);
            temp = true;
        }
        p.first = iterator(bst_.valIt(value));
        p.second = temp;
        return p;
    }
    // wyszukuje element o podanej wartości - jeżeli element został znaleziony to zwraca iterator do wyszukanego elementu, jeżeli nie to zwraca to samo co end()
    iterator find(const T &value) const
    {
        if (bst_.contains(value))
            return iterator(bst_.valIt(value));
        else
            return end();
    }
    // usuwa element o podanej wartości - jeżeli element został usunięty to zwraca true, jeżeli elementu o podanej wartości nie udało się odnaleźć to zwraca false;
    bool remove(const T &value);
    // wykonuje f na każdym elemencie zbioru w kolejności inorder
    void inorder(std::function<void(const T &)> f) const;
    iterator begin() const
    {
        return iterator(bst_.begin());
    }
    iterator end() const
    {
        return iterator(bst_.end());
    }
};

template <typename T>
bool Set<T>::remove(const T &value)
{
    if (bst_.contains(value))
        bst_.remove(value);
    else
        return false;
    return true;
}
template <typename T>
void Set<T>::inorder(std::function<void(const T &)> f) const
{
    bst_.inOrder(f);
}

//!---------iterator----------
template <typename T>
class Set<T>::iterator : public std::iterator<std::input_iterator_tag, const T>
{
public:
    iterator();
    iterator(typename Binarytree<T>::iterator it_) { it = it_; };
    ~iterator();
    iterator &operator++()
    {
        it++;
        return *this;
    }
    iterator operator++(int)
    {
        iterator iterator = *this;
        ++*this;
        return iterator;
    }
    bool operator==(const iterator &rhs);
    bool operator!=(const iterator &rhs);
    int &operator*() const;

private:
    typename Binarytree<T>::iterator it;
};

template <typename T>
Set<T>::iterator::iterator()
{
}
template <typename T>
Set<T>::iterator::~iterator()
{
}

template <typename T>
int &Set<T>::iterator::operator*() const
{
    return *it;
}

template <typename T>
bool Set<T>::iterator::operator==(const iterator &it)
{
    return !(this->it != it.it);
}
template <typename T>
bool Set<T>::iterator::operator!=(const iterator &it)
{
    return (this->it != it.it);
}