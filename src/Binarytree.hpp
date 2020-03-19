
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP
#pragma once

#include "Node.hpp"
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <exception>
#include <functional>
#include <string>

template <typename T>
class Binarytree
{
public:
    class iterator;
    friend class iterator;

private:
    BSTNode<T> *root;
    BSTNode<T> *searchNode(T value) const;
    BSTNode<T> *parentNode(BSTNode<T> *node) const ;
    BSTNode<T> *successorNode(BSTNode<T> *node) const ;
    BSTNode<T> *predecessorNode(BSTNode<T> *node)const ;
    BSTNode<T> *maximum(BSTNode<T> *node) const ;
    BSTNode<T> *minimum(BSTNode<T> *node) const ;
    void put(T data, BSTNode<T> *node);
    void preOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    void print(BSTNode<T> *root, int space) const ;
    void inOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    void postOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    bool testGoodTree(BSTNode<T> *node) const ;

public:
    Binarytree(T head);
    Binarytree(const Binarytree<T> &obj);
    Binarytree(Binarytree<T> &&obj);
    Binarytree();
    ~Binarytree();
    void put(T data);
    void put(T *data, int size);
    void print() const;
    void remove(T value);
    void breadthFirst(std::function<void(const T &)> f) const;
    void preOrder(std::function<void(const T &)> f) const { preOrder(f, root); };
    void inOrder(std::function<void(const T &)> f) const { inOrder(f, root); };
    void postOrder(std::function<void(const T &)> f) const { postOrder(f, root); };
    int hight(); //todo
    std::size_t size() const;
    bool contains(T value) const;
    bool testGoodTree()const { return testGoodTree(root); } ;
    bool empty() const{ return root == nullptr; } ;
    T *search(T value) const;
    T parent(T value) const{ return parentNode(searchNode(value))->getValue(); } ;
    T predecessor(T value) const { return predecessorNode(searchNode(value))->getValue(); } 
    T successor(T value) const { return successorNode(searchNode(value))->getValue(); } 
    T minimum() const { return minimum(root)->getValue(); };
    T maximum() const { return maximum(root)->getValue(); };
    bool operator==(const Binarytree<T> &tree) const ;
    Binarytree<T> &operator=(const Binarytree<T> &other);
    Binarytree<T> &operator=(Binarytree<T> &&other);
    iterator begin()
    {
        if (root == nullptr)
            throw "empty_tree_iterator_is_impossible";
        return iterator(*this);
    }
    iterator end()
    {
        if (root == nullptr)
            throw "empty_tree_iterator_is_impossible";
        return iterator();
    }
};

template <typename T>
Binarytree<T> &Binarytree<T>::operator=(Binarytree<T> &&other)
{
    this->root = other.root;
    other.root = nullptr;
    return *this;
}
template <typename T>
Binarytree<T> &Binarytree<T>::operator=(const Binarytree<T> &other)
{
    if (&other == this)
        return *this;
    delete this->root;
    if (other.root == nullptr)
        this->root = nullptr;
    else
        this->root = new BSTNode<T>(*other.root);
    return *this;
}
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
    if (obj.root == nullptr)
    {
        this->root = nullptr;
        return;
    }
    this->root = new BSTNode<T>(*obj.root);
}
template <typename T>
Binarytree<T>::Binarytree(Binarytree<T> &&obj)
{
    this->root = obj.root;
    obj.root = nullptr;
}
template <typename T>
void Binarytree<T>::put(T data)
{
    if(contains(data))
        return;
    if (root == nullptr)
        root = new BSTNode<T>(data);
    else
        put(data, root);
}
template <typename T>
void Binarytree<T>::put(T *data, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        T temp = data[i];
        put(temp);
    }
}
template <typename T>
std::size_t Binarytree<T>::size() const
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
        if (node->getChildren()[right] != nullptr)
        {
            q.push(node->getChildren()[right]);
        }
        if (node->getChildren()[left] != nullptr)
        {
            q.push(node->getChildren()[left]);
        }
    }
    return result;
}
template <typename T>
void Binarytree<T>::put(T data, BSTNode<T> *node)
{
    while (node->getChildren()[data < (node->getValue())] != nullptr)
    {
        node = node->getChildren()[data < node->getValue()];
    }
    node->put(data);
}
template <typename T>
void Binarytree<T>::print(BSTNode<T> *root, int space) const 
{
    const int gap = 5;
    if (root == NULL)
        return;
    space += gap;
    print(root->getChildren()[right], space);
    std::cout << std::endl;
    for (int i = gap; i < space; i++)
        std::cout << " ";
    std::cout << root->getValue() << std::endl;
    print(root->getChildren()[left], space);
}

template <typename T>
void Binarytree<T>::print() const
{
    print(root, 0);
}

template <typename T>
BSTNode<T> *Binarytree<T>::searchNode(T value) const
{
    if (root == nullptr)
        return nullptr;
    BSTNode<T> *node = root;
    while (node != nullptr && node->getValue() != value)
        node = node->getChildren()[value < node->getValue()];
    return node;
}

template <typename T>
T *Binarytree<T>::search(T value) const
{
    return searchNode(value)->getDataPointer();
}
template <typename T>
bool Binarytree<T>::contains(T value) const 
{
    return searchNode(value) != nullptr;
}
template <typename T>
void Binarytree<T>::remove(T value) 
{
    BSTNode<T> *toDelete = searchNode(value);
    if(toDelete == nullptr)
        throw "deleting_non_existing_object" ;// todo add test
    BSTNode<T> *parent = parentNode(toDelete);
    if (toDelete->noChildren())
    {
        if (toDelete == root)
        {
            root = nullptr;
            return;
        }
        if (parent->getChildren()[right] == toDelete)
            parent->getChildren()[right] = nullptr;
        else
            parent->getChildren()[left] = nullptr;
        return;
        delete toDelete;
    }

    if (toDelete->oneChildren())
    {
        int side = toDelete->whichChildren();
        if (toDelete != root)
            parent->getChildren()[value < parent->getValue()] = toDelete->getChildren()[side];
        else
            root = toDelete->getChildren()[side];
        toDelete->getChildren()[side] = nullptr;
        delete toDelete;
        return;
    }

    BSTNode<T> *newNode = successorNode(toDelete);
    BSTNode<T> *tempNode = new BSTNode<T>(newNode->getValue());
    if (newNode != toDelete->getChildren()[right])
    {
        tempNode->getChildren()[right] = toDelete->getChildren()[right];
        tempNode->getChildren()[left] = toDelete->getChildren()[left];
        remove(newNode->getValue());
    }
    else
    {
        tempNode->getChildren()[right] = newNode->getChildren()[right];
        tempNode->getChildren()[left] = toDelete->getChildren()[left];
        newNode->getChildren()[right] = nullptr;
        delete newNode;
    }
    toDelete->getChildren()[right] = nullptr;
    toDelete->getChildren()[left] = nullptr;
    if (toDelete != root)
    {
        if (parent->getChildren()[right] == toDelete)
            parent->getChildren()[right] = tempNode;
        else
            parent->getChildren()[left] = tempNode;
    }
    else
        root = tempNode;
    delete toDelete;
}
template <typename T>
BSTNode<T> *Binarytree<T>::predecessorNode(BSTNode<T> *node) const 
{
    if (node->getChildren()[left] != nullptr)
        return (maximum(node->getChildren()[left]));
    BSTNode<T> *parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (parent->getChildren()[right] == node)
            return parent;
        node = parent;
        parent = parentNode(node);
    }
    return nullptr;
}
template <typename T>
BSTNode<T> *Binarytree<T>::successorNode(BSTNode<T> *node) const 
{
    if (node->getChildren()[right] != nullptr)
        return (minimum(node->getChildren()[right]));
    BSTNode<T> *parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (parent->getChildren()[left] == node)
            return parent;
        node = parent;
        parent = parentNode(node);
    }
    return nullptr;
}
template <typename T>
BSTNode<T> *Binarytree<T>::parentNode(BSTNode<T> *node) const
{
    if (root == node)
        return nullptr;
    BSTNode<T> *parent = root;
    BSTNode<T> *temp = root;
    temp = temp->getChildren()[node->getValue() < temp->getValue()];
    while (temp != node)
    {
        parent = temp;
        temp = temp->getChildren()[node->getValue() < temp->getValue()];
        if (temp == nullptr)
            return nullptr;
    }
    return parent;
}

template <typename T>
BSTNode<T> *Binarytree<T>::maximum(BSTNode<T> *node) const 
{
    if (node->getChildren()[right] != nullptr)
        return maximum(node->getChildren()[right]);
    else
        return node;
}
template <typename T>
BSTNode<T> *Binarytree<T>::minimum(BSTNode<T> *node) const 
{
    if (node->getChildren()[left] != nullptr)
        return minimum(node->getChildren()[left]);
    else
        return node;
}
template <typename T>
bool Binarytree<T>::testGoodTree(BSTNode<T> *node) const 
{
    if (node == nullptr)
        return true;
    if (node->bothChildren())
    {
        if (node->getChildren()[left]->getValue() < node->getChildren()[right]->getValue())
            return testGoodTree(node->getChildren()[left]) && testGoodTree(node->getChildren()[right]);
        else
            return false;
    }
    else
        return testGoodTree(node->getChildren()[left]) && testGoodTree(node->getChildren()[right]);
}
template <typename T>
void Binarytree<T>::breadthFirst(std::function<void(const T &)> f) const 
{
    if (root == nullptr)
        return;
    BSTNode<T> *node = root;
    std::queue<BSTNode<T> *> s;
    s.push(node);
    while (!s.empty())
    {
        node = s.front();
        s.pop();
        f(node->getValue());
        if (node->getChildren()[left] != nullptr)
            s.push(node->getChildren()[left]);
        if (node->getChildren()[right] != nullptr)
            s.push(node->getChildren()[right]);
    }
}
template <typename T>
void Binarytree<T>::preOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    f(node->getValue());
    preOrder(f, node->getChildren()[left]);
    preOrder(f, node->getChildren()[right]);
}
template <typename T>
void Binarytree<T>::inOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    inOrder(f, node->getChildren()[left]);
    f(node->getValue());
    inOrder(f, node->getChildren()[right]);
}
template <typename T>
void Binarytree<T>::postOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    postOrder(f, node->getChildren()[left]);
    postOrder(f, node->getChildren()[right]);
    f(node->getValue());
}
template <typename T>
bool Binarytree<T>::operator==(const Binarytree<T> &tree) const
{
    if (root == nullptr && tree.root == nullptr)
    {
        return true;
    }
    else if ((root == nullptr && tree.root != nullptr) || (root != nullptr && tree.root == nullptr))
        return false;
    else
        return *root == *(tree.root);
}
//!!-----------iterator--------------
template <typename T>
class Binarytree<T>::iterator : public std::iterator<std::input_iterator_tag, const T>
{
public:
    iterator();
    iterator(Binarytree<T> &tree);
    ~iterator();
    iterator(T value);
    iterator &operator++()
    {
        queue->pop();
        return *this;
    }
    iterator operator++(int)
    {
        iterator iterator = *this;
        ++*this;
        return iterator;
    }
    bool operator==(const iterator &rhs);
    bool operator!=(const iterator &rhs);
    int &operator*();
    std::queue<T> *getQueue(Binarytree<T> &tree);

private:
    std::queue<T> *queue;
};

template <typename T>
Binarytree<T>::iterator::iterator()
{
    queue = new std::queue<T>;
}
template <typename T>
Binarytree<T>::iterator::~iterator()
{
    // delete queue; // FIXME wyciek pamięci ??
}
template <typename T>
Binarytree<T>::iterator::iterator(T value)
{
    queue = getQueue();
    while (queue->front() != value && !queue->empty)
        queue->pop();
}
template <typename T>
Binarytree<T>::iterator::iterator(Binarytree<T> &tree)
{
    queue = getQueue(tree);
}

template <typename T>
int &Binarytree<T>::iterator::operator*()
{
    return queue->front();
}

template <typename T>
bool Binarytree<T>::iterator::operator==(const iterator &it)
{
    return !(*this != it);
}
template <typename T>
bool Binarytree<T>::iterator::operator!=(const iterator &it)
{
    if ((queue->empty() && !it.queue->empty()) || (!queue->empty() && it.queue->empty()))
        return true;
    else if ((queue->empty() && it.queue->empty()))
        return false;
    return queue->front() != it.queue->front();
}
template <typename T>
std::queue<T> *Binarytree<T>::iterator::getQueue(Binarytree<T> &tree)
{
    std::stack<BSTNode<T> *> s;
    std::queue<T> *result = new std::queue<T>();
    BSTNode<T> *node;
    node = tree.root;
    do
    {
        while (node != nullptr)
        {
            s.push(node);
            node = node->getChildren()[left];
        }
        result->push(s.top()->getValue());
        node = s.top()->getChildren()[right];
        s.pop();
    } while (!s.empty() || node != nullptr);
    return result;
}

#endif // !BINARYTREE_CPP
