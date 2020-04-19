
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
    void clear(){delete root;};
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
    iterator begin() const
    {
        if (root == nullptr)
            throw "empty_tree_iterator_is_impossible";
        return iterator(root);
    };
    iterator end() const
    {
        if (root == nullptr)
            throw "empty_tree_iterator_is_impossible";
        return iterator();
    };
    iterator valIt(const T value) const
    {
       return iterator(searchNode(value));
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
        if (node->getChildren()[rightCH] != nullptr)
        {
            q.push(node->getChildren()[rightCH]);
        }
        if (node->getChildren()[leftCH] != nullptr)
        {
            q.push(node->getChildren()[leftCH]);
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
    print(root->getChildren()[rightCH], space);
    std::cout << std::endl;
    for (int i = gap; i < space; i++)
        std::cout << " ";
    std::cout << root->getValue() << std::endl;
    print(root->getChildren()[leftCH], space);
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
    BSTNode<T> *node = searchNode(value);
    if(node != nullptr)
        return searchNode(value)->getDataPointer();
    else
        return nullptr;
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
        if (parent->getChildren()[rightCH] == toDelete)
            parent->getChildren()[rightCH] = nullptr;
        else
            parent->getChildren()[leftCH] = nullptr;
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
    if (newNode != toDelete->getChildren()[rightCH])
    {
        tempNode->getChildren()[rightCH] = toDelete->getChildren()[rightCH];
        tempNode->getChildren()[leftCH] = toDelete->getChildren()[leftCH];
        remove(newNode->getValue());
    }
    else
    {
        tempNode->getChildren()[rightCH] = newNode->getChildren()[rightCH];
        tempNode->getChildren()[leftCH] = toDelete->getChildren()[leftCH];
        newNode->getChildren()[rightCH] = nullptr;
        delete newNode;
    }
    toDelete->getChildren()[rightCH] = nullptr;
    toDelete->getChildren()[leftCH] = nullptr;
    if (toDelete != root)
    {
        if (parent->getChildren()[rightCH] == toDelete)
            parent->getChildren()[rightCH] = tempNode;
        else
            parent->getChildren()[leftCH] = tempNode;
    }
    else
        root = tempNode;
    delete toDelete;
}
template <typename T>
BSTNode<T> *Binarytree<T>::predecessorNode(BSTNode<T> *node) const  
{
    if (node->getChildren()[leftCH] != nullptr)
        return (maximum(node->getChildren()[leftCH]));
    BSTNode<T> *parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (parent->getChildren()[rightCH] == node)
            return parent;
        node = parent;
        parent = parentNode(node);
    }
    return nullptr;
} 
template <typename T>  
BSTNode<T> *Binarytree<T>::successorNode(BSTNode<T> *node) const 
{
    if (node->getChildren()[rightCH] != nullptr)
        return (minimum(node->getChildren()[rightCH]));
    BSTNode<T> *parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (parent->getChildren()[leftCH] == node)
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
    if (node->getChildren()[rightCH] != nullptr)
        return maximum(node->getChildren()[rightCH]);
    else
        return node;
}
template <typename T>
BSTNode<T> *Binarytree<T>::minimum(BSTNode<T> *node) const 
{
    if (node->getChildren()[leftCH] != nullptr)
        return minimum(node->getChildren()[leftCH]);
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
        if (node->getChildren()[leftCH]->getValue() < node->getChildren()[rightCH]->getValue())
            return testGoodTree(node->getChildren()[leftCH]) && testGoodTree(node->getChildren()[rightCH]);
        else
            return false;
    }
    else
        return testGoodTree(node->getChildren()[leftCH]) && testGoodTree(node->getChildren()[rightCH]);
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
        if (node->getChildren()[leftCH] != nullptr)
            s.push(node->getChildren()[leftCH]);
        if (node->getChildren()[rightCH] != nullptr)
            s.push(node->getChildren()[rightCH]);
    }
}
template <typename T>
void Binarytree<T>::preOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    f(node->getValue());
    preOrder(f, node->getChildren()[leftCH]);
    preOrder(f, node->getChildren()[rightCH]);
}
template <typename T>
void Binarytree<T>::inOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    inOrder(f, node->getChildren()[leftCH]);
    f(node->getValue());
    inOrder(f, node->getChildren()[rightCH]);
}
template <typename T>
void Binarytree<T>::postOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    postOrder(f, node->getChildren()[leftCH]);
    postOrder(f, node->getChildren()[rightCH]);
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
    iterator(BSTNode<T> *node)
    {
        while(node != nullptr)
        {
            st.push(node);
            node = node->getChildren()[leftCH];
        }
    }
    iterator() = default;
    iterator &operator++()
    {
        if(st.empty())
            return *this;
        BSTNode<T> *node = st.top();
        st.pop();
        if(node->getChildren()[rightCH] != nullptr)
        {
            node = node->getChildren()[rightCH];
            while(node != nullptr)
            {
                st.push(node);
                node = node->getChildren()[leftCH];
            }
        }
        return *this;
    }
    iterator operator++(int)
    {
        iterator iterator = *this;
        ++*this;
        return iterator;
    }
    bool operator==(const iterator &rhs) const;
    bool operator!=(const iterator &rhs) const;
    int &operator*() const ;
    std::queue<T> *getQueue(const Binarytree<T> &tree  ) const ;
    operator bool() const;

private:
    std::stack<BSTNode<T> *> st;
};

template <typename T>
int &Binarytree<T>::iterator::operator*() const
{ 
    // if(st.empty())
        // return nullptr;
        //  error C2440: 'return': cannot convert from 'nullptr' to 'int &'
    return  *st.top()->getDataPointer();
}

template <typename T>
bool Binarytree<T>::iterator::operator==(const iterator &it) const
{
    return !(*this != it);
}
template <typename T>
bool Binarytree<T>::iterator::operator!=(const iterator &it) const 
{
    if ((st.empty() && !it.st.empty()) || (!st.empty() && it.st.empty()))
        return true;
    else if ((st.empty() && it.st.empty()))
        return false;
    return st.top() != it.st.top();
}
template <typename T>
Binarytree<T>::iterator::operator bool() const
{
    return(st.empty());
}

#endif // !BINARYTREE_CPP
