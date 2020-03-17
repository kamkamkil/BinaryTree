#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
enum n {right, left};

template <typename T>
class BSTNode
{
private:
    BSTNode<T> *children[2];
    T value;
public:
    BSTNode(const BSTNode<T> &obj);
    BSTNode( BSTNode<T> &&obj);
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
    bool operator==(const BSTNode<T>& node) const;
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
    std::cout << "temp" << std::endl;
    value = obj.value;
        children[right] = nullptr;
    children[left] = nullptr;
    if (obj.children[right] != nullptr)
        this->children[right] = new BSTNode<T>(*obj.children[right]);
    if (obj.children[left] != nullptr)
        this->children[left] = new BSTNode<T>(*obj.children[left]);
}
template <typename T>
BSTNode<T>::BSTNode( BSTNode<T> &&obj)
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
        return 2;
    if (noChildren())
        return -1;
    if (children[right] != nullptr)
        return 0;
    if (children[left] != nullptr)
        return 1;
    return 6;
}
template <typename T>
bool BSTNode<T>::operator==(const BSTNode<T>& node) const
{
    if(value == node.value)
        return (*children[0] == *(node.children[0]) && *children[1] == *(node.children[1])); 
    else
        return false;
}


#endif // !NODE_CPP
