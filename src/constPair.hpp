#include <utility>
#include <iostream>
#pragma once
template <typename K, typename V>
class constPair
{
public:
    const K key;
    V value;
    constPair(K key_) : key(key_){};
    constPair(K key_, V value_) : key(key_), value(value_){};
    constPair(const std::pair<K, V> obj) : key(obj.first), value(obj.second){};
    void setValue(V value_)
    {
        value = value_;
    }

    bool operator>(constPair const &obj) const { return key > obj.key; };
    bool operator<(constPair const &obj) const { return key < obj.key; };
    bool operator<=(constPair const &obj) const { return key <= obj.key; };
    bool operator>=(constPair const &obj) const { return key >= obj.key; };
    bool operator==(constPair const &obj) const { return key == obj.key; };
    bool operator!=(constPair const &obj) const { return key != obj.key; };
    void operator=(V const &obj) { value = obj; };
    operator V() const { return value; };
    operator V&()  { return value; };
    operator V*() const { return &value; };
    friend std::ostream &operator<<(std::ostream &os, const constPair<K, V> &dt)
    {
        os << "[ " << dt.key << ", " << dt.value << " ]";
        return os;
    }
};