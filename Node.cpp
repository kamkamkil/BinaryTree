#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
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
    T getData();
    T* getDataPointer();
    bool bothChildren();
    bool oneChildren();
    bool noChildren();
    int whichChildren();
};

template <typename T>
BSTNode<T>::BSTNode(T data)
{
    this->value = data;
    children[0] = nullptr;
    children[1] = nullptr;
}

template <typename T>
BSTNode<T>::~BSTNode()
{
    delete children[0];
    delete children[1];
}
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T> &obj)
{
    this->value = obj.value;
    if (obj.children[0] != nullptr)
        this->children[0] = new BSTNode<T>(*obj.children[0]);
    if (obj.children[1] != nullptr)
        this->children[1] = new BSTNode<T>(*obj.children[1]);
}
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T> &&obj)
{
    this->data = obj.value;
    this->children = obj.children;
    obj.children[0] = nullptr;
    obj.children[1] = nullptr;
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
T BSTNode<T>::getData()
{
    return value;
}

template <typename T>
T* BSTNode<T>::getDataPointer()
{
    return *value;
}
template <typename T>
bool BSTNode<T>::bothChildren()
{
    return (children[0] != nullptr && children[1] != nullptr);
}
template <typename T>
bool BSTNode<T>::oneChildren()
{
    return (children[0] != nullptr ^ children[1] != nullptr);
}
template <typename T>
bool BSTNode<T>::noChildren()
{
    return (children[0] == nullptr && children[1] == nullptr);
}
template <typename T>
int BSTNode<T>::whichChildren()
{
    if (bothChildren())
        return 2;
    if (noChildren())
        return -1;
    if (children[0] != nullptr)
        return 0;
    if (children[1] != nullptr)
        return 1;
    return 6;
}

#endif // !NODE_CPP
