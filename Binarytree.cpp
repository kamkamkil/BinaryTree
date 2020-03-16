
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "Node.cpp"
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <exception>
#include <functional>

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
    void preOrder(std::function<void(const T&)> f,BSTNode<T> *node); 
    void inOrder (std::function<void(const T&)> f,BSTNode<T> *node); 
    void postOrder (std::function<void(const T&)> f, BSTNode<T> *node);
    bool testGoodTree(BSTNode<T> *node);

public:
    Binarytree(T head);
    Binarytree(const Binarytree<T> &obj);
    Binarytree(const Binarytree<T> &&obj);
    Binarytree();
    ~Binarytree();
    void put(T data);
    void print();
    void remove(T value);
    void breadthFirst(std::function<void(const T&)> f);
    void preOrder(std::function<void(const T&)> f){preOrder(f,root);}; 
    void inOrder (std::function<void(const T&)> f){inOrder(f,root);};
    void postOrder (std::function<void(const T&)> f){postOrder(f,root);};
    int hight(); //todo
    std::size_t  size();
    bool contains(T value);
    bool testGoodTree() { return testGoodTree(root); };
    bool empty() {return root == nullptr;};
    T* search(T value);
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
std::size_t  Binarytree<T>::size()
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
    while(node != nullptr && node->getData() != value)
    {
        node = node->getChildren()[value < node->getData()];
    }
    return node;
}

template <typename T>
T* Binarytree<T>::search(T value)
{
    return searchNode(value)->getDataPointer();
    
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

    if (toDelete->oneChildren())
    {
        int side = toDelete->whichChildren();
        if (toDelete != root)
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
        tempNode->getChildren()[1] = toDelete->getChildren()[1];
        newNode->getChildren()[0] = nullptr;
        delete newNode;
    }
    toDelete->getChildren()[0] = nullptr;
    toDelete->getChildren()[1] = nullptr;
    if (toDelete != root)
    {
        if (_parent->getChildren()[0] == toDelete)
            _parent->getChildren()[0] = tempNode;
        else
            _parent->getChildren()[1] = tempNode;
    }
    else
        root = tempNode;
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
template <typename T>
void Binarytree<T>::breadthFirst(std::function<void(const T&)> f)
{
    if(root == nullptr)
        return;
    BSTNode<T> *node = root;
    std::queue<BSTNode<T> *> s;
    s.push(node);
    while (!s.empty())
    {
        node = s.front();
        s.pop();
        f(node->getData());
        if (node->getChildren()[1] != nullptr)
            s.push(node->getChildren()[1]);
        if (node->getChildren()[0] != nullptr)
            s.push(node->getChildren()[0]);
    }
}
template <typename T> 
void Binarytree<T>::preOrder(std::function<void(const T&)> f,BSTNode<T> *node) 
{
        if(node == nullptr)
            return;
        f(node->getData);
        preOrder(f,node->getChildren()[1]);
        preOrder(f,node->getChildren()[0]);
}
template <typename T> 
void Binarytree<T>::inOrder(std::function<void(const T&)> f,BSTNode<T> *node) 
{
        if(node == nullptr)
            return;
        preOrder(f,node->getChildren()[1]);
        f(node->getData);
        preOrder(f,node->getChildren()[0]);
}template <typename T> 
void Binarytree<T>::postOrder(std::function<void(const T&)> f,BSTNode<T> *node) 
{
        if(node == nullptr)
            return;
        preOrder(f,node->getChildren()[1]);
        preOrder(f,node->getChildren()[0]);
        f(node->getData);
}
#endif // !BINARYTREE_CPP
