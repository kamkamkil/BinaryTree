#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
enum n {right, left};

template <typename T>
class BSTNode
{
private:
    T value;
    BSTNode<T> *children[2];

public:
    BSTNode(const BSTNode<T> &obj);
    BSTNode(const BSTNode<T> &&obj);
    BSTNode(T value);
    ~BSTNode();
    void put(T value);
    BSTNode<T> **getChildren();
    T getValue();
    T* getDataPointer();
    bool bothChildren();
    bool oneChildren();
    bool noChildren();
    int whichChildren();
};

template <typename T>
BSTNode<T>::BSTNode(T data)
{
    
    this->value = value;
    children[right] = nullptr;
    children[left] = nullptr;
}

template <typename T>
BSTNode<T>::~BSTNode()
{
    delete children[right];
    delete children[left];
}
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T> &obj)
{
    this->value = obj.value;
    if (obj.children[right] != nullptr)
        this->children[right] = new BSTNode<T>(*obj.children[right]);
    if (obj.children[left] != nullptr)
        this->children[left] = new BSTNode<T>(*obj.children[left]);
}
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T> &&obj)
{
    this->data = obj.value;
    this->children = obj.children;
    obj.children[right] = nullptr;
    obj.children[left] = nullptr;
    }
template <typename T>
void BSTNode<T>::put(T __data) // FIXME zmiana nazwy
{
    children[__data < this->value] = new BSTNode<T>(__data);
}
template <typename T>
BSTNode<T> **BSTNode<T>::getChildren()
{
    return children;
}
template <typename T>
T BSTNode<T>::getValue()
{
    return value;
}


template <typename T>
bool BSTNode<T>::bothChildren()
{
    return (children[right] != nullptr && children[left] != nullptr);
}
template <typename T>
bool BSTNode<T>::oneChildren()
{
    return (children[right] != nullptr ^ children[left] != nullptr);
}
template <typename T>
bool BSTNode<T>::noChildren()
{
    return (children[right] == nullptr && children[left] == nullptr);
}
template <typename T>
int BSTNode<T>::whichChildren()
{
    if (bothChildren())
        return 2;
    if (noChildren())
        return -1;
    if (children[right] != nullptr)
        return 0;
    if (children[left] != nullptr)
        return 1;
    return 6;
}

#endif // !NODE_CPP
