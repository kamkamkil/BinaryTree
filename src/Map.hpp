#pragma once

#include <cstdint>
#include <utility>
#include <iterator>
#include "Binarytree.hpp"
#include "constPair.hpp"

// klasa reprezentująca słownik (map) oparty na drzewie BST/AVL
// K - typ kluczy
// V - typ wartości
template <typename K, typename V>
class Map
{
private:
    Binarytree<constPair<K, V>> tree;

public:
    class Iterator
    {
        // ...

    public:
        Iterator(){};
        Iterator(typename Binarytree<constPair<K, V>>::iterator it_) { it = it_; };
        bool operator==(const Iterator &it_) const { return it == it_.it; };
        bool operator!=(const Iterator &it_) const { return it != it_.it; };
        Iterator &operator++()
        {
            it++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
        V &operator*() const { return *it; };
        V *operator->() const;
        operator bool() const;

    private:
        typename Binarytree<constPair<K, V>>::iterator it;
    };

    class ConstIterator
    {
        // ...

    public:
        ConstIterator(){};
        ConstIterator(typename Binarytree<constPair<K, V>>::iterator it_) { it = it_; };
        bool operator==(const ConstIterator &it_) const { return it == it_.it; }
        bool operator!=(const ConstIterator &it_) const { return it != it_.it; }
        ConstIterator &operator++()
        {
            it++;
            return *this;
        }
        ConstIterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
        const V &operator*() const;
        const V *operator->() const;
        operator bool() const;

    private:
        typename Binarytree<constPair<K, V>>::iterator it;
    };

    // ...

public:
    Map();
    Map(const Map<K, V> &source);
    Map<K, V> &operator=(const Map<K, V> &source);
    Map(Map<K, V> &&source);
    Map<K, V> &operator=(Map<K, V> &&source);
    ~Map();

    // zwraca ilość elementów
    std::size_t size() const { return tree.size(); };
    // dodaje klucz i wartość - zwraca "Iterator" do dodanej wartości i true, lub "Iterator" do istniejącej wartości i false, jeżeli z jakiegoś powodu nie udało się dodać/znaleźć to zwraca false i to samo co end()
    std::pair<Iterator, bool> insert(const std::pair<K, V> &key_value)
    {
        std::pair<Iterator, bool> result;

        constPair<K, V> pair(key_value);
        if (tree.contais(pair))
        {
            tree.search(pair)->setValue(pair.value);
            result.second = false;
            result.first = Iterator(tree.valIt(pair));
            return result;
        }
        else
        {
            tree.put(pair);
            result.first = Iterator(tree.valIt(pair));
            result.second = true;
            return result;
        }
        result.first = end();
        result.second = false;
        return result;
    }
    // wyszukuje element o podanym kluczu - jeżeli element został znaleziony to zwraca "ConstIterator" do znalezionej wartości, jeżeli nie to zwraca to samo co end()
    ConstIterator find(const K &key) const
    {
        constPair<V, K> pair(key);
        if (tree.contains(pair))
        {
            return ConstIterator(tree.valIt(pair));
        }
        else
        {
            return end();
        }
    }
    // wyszukuje element o podanym kluczu - jeżeli element został znaleziony to zwraca "Iterator" do znalezionej wartości, jeżeli nie to zwraca to samo co end()
    Iterator find(const K &key)
        {
        constPair<V, K> pair(key);
        if (tree.contains(pair))
        {
            return Iterator(tree.valIt(pair));
        }
        else
        {
            return end();
        }
    }
    // wyszukuje element o podanym kluczu - jeżeli element został znaleziony to zwraca referencję do znalezionej (stałej) wartości, jeżeli nie to dodaje nowy element o podanym kluczu i domyślnej wartości V() i zwraca referencję do wartości
    const V &operator[](const K &key) const;
    // wyszukuje element o podanym kluczu - jeżeli element został znaleziony to zwraca referencję do znalezionej wartości, jeżeli nie to dodaje nowy element o podanym kluczu i domyślnej wartości V() i zwraca referencję do wartości
    //pamiętać o rzuceniu wyjątku
    V &operator[](const K &key);
    // usuwa element o podanej wartości - jeżeli element został usunięty to zwraca "Iterator" na kolejny element, jeżeli elementu o podanej wartości nie udało się odnaleźć to zwraca to samo co "end()"
    Iterator remove(const K &key);
    // usuwa wszystkie elementy
    void clear();

    // zwraca "ConstIterator" na pierwszy element
    ConstIterator begin() const;
    // zwraca "Iterator" na pierwszy element
    Iterator begin();
    // zwraca "ConstIterator" "za ostatni" element
    ConstIterator end() const;
    // zwraca "Iterator" "za ostatni" element
    Iterator end();
};
