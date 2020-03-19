#ifndef NODE_CPP
#define NODE_CPP
#pragma once

#include <iostream>
enum n
{
    right,
    left,
    both
};

template <typename T>
class BSTNode
{
private:
    BSTNode<T> *children[2];
    T value;

public:
    BSTNode(const BSTNode<T> &obj);
    BSTNode(BSTNode<T> &&obj);
    BSTNode(T value);
    ~BSTNode();
    void put(T value);
    BSTNode<T> **getChildren();
    T getValue();
    T *getDataPointer(); //todo
    bool bothChildren();
    bool oneChildren();
    bool noChildren();
    int whichChildren();
    bool operator==(const BSTNode<T> &node) const;
};

template <typename T>
BSTNode<T>::BSTNode(T data)
{

    this->value = data;
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
    value = obj.value;
    children[right] = nullptr;
    children[left] = nullptr;
    if (obj.children[right] != nullptr)
        this->children[right] = new BSTNode<T>(*obj.children[right]);
    if (obj.children[left] != nullptr)
        this->children[left] = new BSTNode<T>(*obj.children[left]);
}
template <typename T>
BSTNode<T>::BSTNode(BSTNode<T> &&obj)
{
    this->data = obj.value;
    this->children = obj.children;
    obj.children[right] = nullptr;
    obj.children[left] = nullptr;
}
template <typename T>
void BSTNode<T>::put(T __data)
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
T* BSTNode<T>::getDataPointer()
{
    return &value;
}
template <typename T>
bool BSTNode<T>::bothChildren()
{
    return (children[right] != nullptr && children[left] != nullptr);
}
template <typename T>
bool BSTNode<T>::oneChildren()
{
    return ((children[right] != nullptr) ^ (children[left] != nullptr));
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
        return both;
    if (noChildren())
        return -1;
    if (children[right] != nullptr)
        return right;
    if (children[left] != nullptr)
        return left;
    return -1;
}
template <typename T>
bool BSTNode<T>::operator==(const BSTNode<T> &node) const
{
    if ((children[right] != nullptr && node.children[right] == nullptr) || (children[right] == nullptr && node.children[right] != nullptr))
        return false;
    if ((children[left] != nullptr && node.children[left] == nullptr) || (children[left] == nullptr && node.children[left] != nullptr))
        return false;
    else if (children[right] == nullptr && node.children[right] == nullptr && children[1] == nullptr && node.children[1] == nullptr)
        return true;
    else if (children[right] == nullptr && node.children[right] == nullptr)
        return *children[left] == *(node.children[left]);
    else if (children[left] == nullptr && node.children[left] == nullptr)
        return *children[right] == *(node.children[right]);
    else if (value == node.value)
        return (*children[right] == *(node.children[right]) && *children[left] == *(node.children[left]));
    else
        return false;
}

#endif // !NODE_CPP
