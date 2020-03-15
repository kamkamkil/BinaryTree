
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

template <typename T>
class Binarytree
{

private:
    BSTNode<T> *root;
    void put(T data, BSTNode<T> *node);
    void print(BSTNode<T> *root, int space);
    BSTNode<T> *searchNode(T value);
    BSTNode<T> *parent(BSTNode<T> *node);
    BSTNode<T> *successor(BSTNode<T> *node);
    BSTNode<T> *predecessor(BSTNode<T> *node);
    BSTNode<T> *maximum(BSTNode<T> *node);
    BSTNode<T> *minimum(BSTNode<T> *node);
    void visit(T value);

public:
    Binarytree(T head);
    Binarytree();
    ~Binarytree();
    void put(T data);
    int hight(); //todo
    void print();
    const T search(T value);
    bool contains(T value);
    void delate(T value);
    T minimum(){return minimum(root)->getData();};
    T maximum(){return maximum(root)->getData();};
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
        node = q.front();
        q.pop();
        if (node->getData() == value)
        {
            return node;
        }
        if (node->getChildren()[0] != nullptr)
        {
            q.push(node->getChildren()[0]);
        }
        if (node->getChildren()[1] != nullptr)
        {
            q.push(node->getChildren()[1]);
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
const T Binarytree<T>::search(T value)
{
    BSTNode<T> *node = searchNode(value);
    if (node == nullptr)
    {
        throw "NoObjectException";
    }
    const T result = node->getData();
    return result;
}
template <typename T>
bool Binarytree<T>::contains(T value)
{
    return searchNode(value) != nullptr;
}
template <typename T>
void Binarytree<T>::delate(T value)
{
    BSTNode<T> *node = root;
    while (node->getChildren()[0] != nullptr || node->getChildren()[1] != nullptr)
    {
        int side = value < node->getData();
        if (node->getChildren()[side] != nullptr)
        {
            if (node->getChildren()[side]->getData() == value)
            {
                // BSTNode<T> *nodeToDelate = node->getChildren()[side];
                // int children = 0;
                // if (nodeToDelate->getChildren()[0] == nullptr && nodeToDelate->getChildren()[1] == nullptr)
                // {
                //     delete nodeToDelate;
                //     node->getChildren()[side] = nullptr;
                // }
                // if (nodeToDelate->getChildren()[0] == nullptr && nodeToDelate->getChildren()[1] != nullptr)
                // {
                //     node->getChildren()[side] = nodeToDelate->getChildren()[1];
                //     delete nodeToDelate;
                // }
                // if (nodeToDelate->getChildren()[0] == nullptr && nodeToDelate->getChildren()[1] == nullptr)
                // {
                //     BSTNode<T> *temp = node->getChildren()[side]; //FIXME

                    
                // }
            }
        }
        else
            return;
        node = node->getChildren()[side];
    }
}
template<typename T>
BSTNode<T> *Binarytree<T>::parent(BSTNode<T> * node)
{
    if(root == node)
        return nullptr;
    BSTNode<T> *parent = root;
    BSTNode<T> *temp = root;
    temp = temp->getChildren()[node->getData() < temp->getData()];
    while (temp != node)
    {
        parent = temp;
        temp = temp->getChildren()[node->getData() < temp->getData()];
        if (temp == nullptr)
            return nullptr; 
    }
    return parent;
}
template<typename T>
BSTNode<T> *Binarytree<T>::successor(BSTNode<T> * node)
{
}
template<typename T>
BSTNode<T> *Binarytree<T>::predecessor(BSTNode<T> * node)
{

}
template<typename T>
BSTNode<T> *Binarytree<T>::maximum(BSTNode<T> * node)
{
    if(node->getChildren()[0] != nullptr)
        return maximum(node->getChildren()[0]);
    else
        return node;
}
template<typename T>
BSTNode<T> *Binarytree<T>::minimum(BSTNode<T> * node)
{
        if(node->getChildren()[1] != nullptr)
        return minimum(node->getChildren()[1]);
    else
        return node;
}

#endif // !BINARYTREE_CPP
