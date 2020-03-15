
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "Node.cpp"
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <exception>
//to nie działa na linux
// #include "printWinFun.cpp"//!!
//

class NoObjectException : public exception
{
    virtual const char *what() const throw()
    {
        return "there are no object like that in tree";
    }
};

template <typename T>
class Binarytree
{

private:
    BSTNode<T> *root;
    void put(T data, BSTNode<T> *node);
    void print(BSTNode<T> *root, int space);
    BSTNode<T> *searchNode(T value);
    void visit(T value);

public:
    Binarytree(T head);
    Binarytree();
    ~Binarytree();
    void put(T data);
    int hight();
    void print();
    T &&search(T value);
    bool contains(T value);
};

template <typename T>
Binarytree<T>::Binarytree()
{
    root = nullptr;
}
template <typename T>
Binarytree<T>::Binarytree(T head)
{
    root = new BSTNode<T>(head);
}
template <typename T>
Binarytree<T>::~Binarytree()
{
    delete root;
}
template <typename T>
void Binarytree<T>::put(T data)
{
    if (root == nullptr)
    {
        root = new BSTNode<T>(data);
    }
    else
    {
        put(data, root);
    }
}
template <typename T>
void Binarytree<T>::put(T data, BSTNode<T> *node)
{
    while (node->getChildren()[data < (node->getData())] != nullptr)
    {
        node = node->getChildren()[data < node->getData()];
    }
    node->put(data);
}
template <typename T>
void Binarytree<T>::print(BSTNode<T> *root, int space)
{
    const int gap = 5;
    if (root == NULL)
        return;
    space += gap;
    print(root->getChildren()[0], space);
    std::cout << std::endl;
    for (int i = gap; i < space; i++)
        std::cout << " ";
    std::cout << root->getData() << std::endl;
    print(root->getChildren()[1], space);
}

template <typename T>
void Binarytree<T>::print()
{
    print(root, 0);
}
template <typename T>
int Binarytree<T>::hight()
{
    return 0;
}

template <typename T>
BSTNode<T> *Binarytree<T>::searchNode(T value)
{
    BSTNode<T> *node = root;
    std::queue<BSTNode<T> *> q;
    q.push(node);
    while (!q.empty())
    {
        node = q.front;
        q.pop;
        if (node->getData == value)
        {
            return node;
        }
        if (node->getChildren[0] != nullptr)
        {
            q.push(node->getChildren[0]);
        }
        if (node->getChildren[1] != nullptr)
        {
            q.push(node->getChildren[1]);
        }
    }
    return nullptr;
}
template <typename T>
void Binarytree<T>::visit(T value)
{
    std::cout << "i'm in node : " << value << std::endl;
}
template <typename T>
T &&Binarytree<T>::search(T value)
{
    BSTNode<T> *node = searchNode(value);
    if (node == nullptr)
    {
       // throw new NoObjectException;
    }
}
template <typename T>
bool Binarytree<T>::contains(T value)
{
    return searchNode != nullptr;
}
#endif // !BINARYTREE_CPP
