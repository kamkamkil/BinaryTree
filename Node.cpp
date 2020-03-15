#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
template <typename T>
class BSTNode
{
private:
    T data;
    BSTNode<T> *children[2];
public:
    BSTNode(T data);
    ~BSTNode();
    void put(T data);
    BSTNode<T> **getChildren();
    T getData();
};

template <typename T>
BSTNode<T>::BSTNode(T data)
{
    this->data = data;
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
void BSTNode<T>::put(T __data) // FIXME zmiana nazwy
{
    children[__data < this->data] = new BSTNode<T>(__data);
}
template <typename T>
BSTNode<T> **BSTNode<T>::getChildren()
{
    return children;
}
template <typename T>
T BSTNode<T>::getData()
{
    return data;
}

#endif // !NODE_CPP
