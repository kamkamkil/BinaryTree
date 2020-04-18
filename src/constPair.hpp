#include <utility>
#include <iostream>
template <typename K, typename V>
class constPair
{
public:
    const K key;
    V value;
    constPair(K key_)
    {
        key = key_;
    }
    constPair(K key_, V value_)
    {
        key = key_;
        value = value_;
    }
    constPair(const std::pair<K, V> &obj)
    {
        key = obj.first;
        value = obj.secont;
    } //FIXME
    void setValue(V value_)
    {
        value = value_;
    }

private:
    bool operator>(constPair const &obj) const { return key > obj.key; };
    bool operator<(constPair const &obj) const { return key < obj.key; };
    bool operator<=(constPair const &obj) const { return key <= obj.key; };
    bool operator>=(constPair const &obj) const { return key >= obj.key; };
    bool operator==(constPair const &obj) const { return key == obj.key; };
    ostream &operator<<(ostream &os, const constPair<K,V> &dt)
    {
        os << "[ " << K << ", " << V  << " ]";
        return os;
    }
};