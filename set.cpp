#pragma once

#include "BinaryTree.cpp"

#include <functional>

// Uwaga! Kod powinien byc odporny na bledy i kazda z metod jezeli zachodzi niebezpieczenstwo wywolania z niepoprawnymi parametrami powinna zglaszac odpowiednie wyjatki!

// klasa reprezentujaca zbiór (set) oparty na drzewie (BST/AVL)
template <typename T>
class Set
{
public:
    Set();
    Set(const Set<T> &source);
    Set<T> &operator=(const Set<T> &source);
    Set(Set<T> &&source);
    Set<T> &operator=(Set<T> &&source);
    ~Set();

private:
    // drzewo BST
    Binarytree<T> bst_;

public:
    // zwraca ilość elementów
    std::size_t size() const {return bst_.size();};
    // zwraca true gdy zbiór jest pusty, lub false w innym przypadku
    bool empty() const {return bst_.empty();};
    // dodaje element - zwraca adres dodanego, lub istniejącego elementu
    const T *insert(const T &value);
    // wyszukuje element o podanej wartości - jeżeli element został znaleziony to zwraca wskaźnik do wyszukanego elementu, jeżeli nie to zwraca nullptr
    const T *find(const T &value) const;
    // usuwa element o podanej wartości - jeżeli element został usunięty to zwraca true, jeżeli elementu o podanej wartości nie udało się odnaleźć to zwraca false;
    bool remove(const T &value) ;
    // wykonuje f na każdym elemencie zbioru w kolejności inorder
    void inorder(std::function<void(const T &)> f) const;
};

template <typename T>
const T * Set<T>::find(const T &value) const
{
    return(bst_.search(value));
}
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
    bst_.inorder(f);
}
template <typename T>
const T *Set<T>::insert(const T &value)
{
    bst_.put(value);
    return bst_.search(value)
}
