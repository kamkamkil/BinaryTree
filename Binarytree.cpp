
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "Node.cpp"
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <exception>

template <typename T>
class Binarytree
{

private:
    BSTNode<T> *root;
    void put(T data, BSTNode<T> *node);
    void print(BSTNode<T> *root, int space);
    BSTNode<T> *searchNode(T value);
    BSTNode<T> *parentNode(BSTNode<T> *node);
    BSTNode<T> *successorNode(BSTNode<T> *node);
    BSTNode<T> *predecessorNode(BSTNode<T> *node);
    BSTNode<T> *maximum(BSTNode<T> *node);
    BSTNode<T> *minimum(BSTNode<T> *node);
    void visit(T value);
    bool testGoodTree(BSTNode<T> *node);

public:
    Binarytree(T head);
    Binarytree(const Binarytree<T> &obj);
    Binarytree(const Binarytree<T> &&obj);
    Binarytree();
    ~Binarytree();
    void put(T data);
    int hight(); //todo
    int size();
    void print();
    const T search(T value);
    bool contains(T value);
    void remove(T value);
    bool testGoodTree() { return testGoodTree(root); };
    T parent(T value) { return parentNode(searchNode(value))->getData(); };
    T predecessor(T value) { return predecessorNode(searchNode(value))->getData(); }
    T successor(T value) { return successorNode(searchNode(value))->getData(); }
    T minimum() { return minimum(root)->getData(); };
    T maximum() { return maximum(root)->getData(); };
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
Binarytree<T>::Binarytree(const Binarytree<T> &obj)
{
    this->root = new BSTNode<T>(*root);
}
template <typename T>
Binarytree<T>::Binarytree(const Binarytree<T> &&obj)
{
    this->root = obj.root;
    obj.root = nullptr;
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
int Binarytree<T>::size()
{
    int result = 0;
    if (root == nullptr)
        return result;
    BSTNode<T> *node = root;
    std::queue<BSTNode<T> *> q;
    q.push(node);
    while (!q.empty())
    {
        result++;
        node = q.front();
        q.pop();
        if (node->getChildren()[0] != nullptr)
        {
            q.push(node->getChildren()[0]);
        }
        if (node->getChildren()[1] != nullptr)
        {
            q.push(node->getChildren()[1]);
        }
    }
    return result;
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
    if (root == nullptr)
        return nullptr;
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
void Binarytree<T>::remove(T value)
{
    BSTNode<T> *toDelete = searchNode(value);
    BSTNode<T> *_parent = parentNode(toDelete);
    if (toDelete->noChildren())
    {
        if (toDelete == root)
        {
            root = nullptr;
            return;
        }
        if (_parent->getChildren()[0] == toDelete)
        {
            _parent->getChildren()[0] = nullptr;
        }
        else
        {
            _parent->getChildren()[1] = nullptr;
        }
        return;
        delete toDelete;
    }

    if(toDelete->oneChildren())
    {
        int side = toDelete->whichChildren() ;
        if(toDelete != root)
            _parent->getChildren()[value < _parent->getData()] = toDelete->getChildren()[side];
        else    
            root = toDelete->getChildren()[side];
         toDelete->getChildren()[side] = nullptr;
         delete toDelete;
         return;
    }

    BSTNode<T> *newNode = successorNode(toDelete);
    BSTNode<T> *tempNode = new BSTNode<T>(newNode->getData());
    if (newNode != toDelete->getChildren()[0])
    {
        tempNode->getChildren()[0] = toDelete->getChildren()[0];
        tempNode->getChildren()[1] = toDelete->getChildren()[1];
        remove(newNode->getData());
    }
    else
    {
        tempNode->getChildren()[0] = newNode->getChildren()[0];
        newNode->getChildren()[0] = nullptr;
        delete newNode;
    }
    toDelete->getChildren()[0] = nullptr;
    toDelete->getChildren()[1] = nullptr;
    if (_parent->getChildren()[0] == toDelete)
        _parent->getChildren()[0] = tempNode;
    else
        _parent->getChildren()[1] = tempNode;
    delete toDelete;
}
template <typename T>
BSTNode<T> *Binarytree<T>::predecessorNode(BSTNode<T> *node)
{
    if (node->getChildren()[1] != nullptr)
        return (maximum(node->getChildren()[1]));
    BSTNode<T> *_parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (_parent->getChildren()[0] == node)
            return _parent;
        node = _parent;
        _parent = parentNode(node);
    }
    return nullptr;
}
template <typename T>
BSTNode<T> *Binarytree<T>::successorNode(BSTNode<T> *node)
{
    if (node->getChildren()[0] != nullptr)
        return (minimum(node->getChildren()[0]));
    BSTNode<T> *_parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (_parent->getChildren()[1] == node)
            return _parent;
        node = _parent;
        _parent = parentNode(node);
    }
    return nullptr;
}
template <typename T>
BSTNode<T> *Binarytree<T>::parentNode(BSTNode<T> *node)
{
    if (root == node)
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

template <typename T>
BSTNode<T> *Binarytree<T>::maximum(BSTNode<T> *node)
{
    if (node->getChildren()[0] != nullptr)
        return maximum(node->getChildren()[0]);
    else
        return node;
}
template <typename T>
BSTNode<T> *Binarytree<T>::minimum(BSTNode<T> *node)
{
    if (node->getChildren()[1] != nullptr)
        return minimum(node->getChildren()[1]);
    else
        return node;
}
template <typename T>
bool Binarytree<T>::testGoodTree(BSTNode<T> *node)
{
    if (node == nullptr)
        return true;
    if (node->bothChildren())
    {
        if (node->getChildren()[1]->getData() < node->getChildren()[0]->getData())
        {
            return testGoodTree(node->getChildren()[1]) && testGoodTree(node->getChildren()[0]);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return testGoodTree(node->getChildren()[1]) && testGoodTree(node->getChildren()[0]);
    }
}
#endif // !BINARYTREE_CPP
