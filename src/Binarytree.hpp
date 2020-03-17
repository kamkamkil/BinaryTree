
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

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
    class iterator : public std::iterator<std::input_iterator_tag, const T>
    {
    public:
        iterator() = default;
        iterator(Binarytree<T> &tree);
        ~iterator();
        iterator(T value);
        void iteratorBack()
        {
            delete queue;
            queue = new std::queue<T>;
        }
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

private:
    BSTNode<T> *root;
    BSTNode<T> *searchNode(T value) const;
    BSTNode<T> *parentNode(BSTNode<T> *node);
    BSTNode<T> *successorNode(BSTNode<T> *node);
    BSTNode<T> *predecessorNode(BSTNode<T> *node);
    BSTNode<T> *maximum(BSTNode<T> *node);
    BSTNode<T> *minimum(BSTNode<T> *node);
    void put(T data, BSTNode<T> *node);
    void preOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    void print(BSTNode<T> *root, int space);
    void inOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    void postOrder(std::function<void(const T &)> f, BSTNode<T> *node) const;
    bool testGoodTree(BSTNode<T> *node);

public:
    Binarytree(T head);
    Binarytree(const Binarytree<T> &obj);
    Binarytree(Binarytree<T> &&obj);
    Binarytree();
    ~Binarytree();
    void put(T data);
    void put(T *data, int size);
    void print();
    void remove(T value);
    void breadthFirst(std::function<void(const T &)> f);
    void preOrder(std::function<void(const T &)> f) const { preOrder(f, root); };
    void inOrder(std::function<void(const T &)> f) const { inOrder(f, root); };
    void postOrder(std::function<void(const T &)> f) const { postOrder(f, root); };
    int hight(); //todo
    std::size_t size() const;
    bool contains(T value);
    bool testGoodTree() { return testGoodTree(root); };
    bool empty() { return root == nullptr; };
    T *search(T value) const;
    T parent(T value) { return parentNode(searchNode(value))->getValue(); };
    T predecessor(T value) { return predecessorNode(searchNode(value))->getValue(); }
    T successor(T value) { return successorNode(searchNode(value))->getValue(); }
    T minimum() { return minimum(root)->getValue(); };
    T maximum() { return maximum(root)->getValue(); };
    bool operator==(const Binarytree<T> &tree) const;
    iterator begin()
    {
        return iterator(*this);
    }
    iterator end()
    {
        iterator i;
        i.iteratorBack();
        return i;
    }
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
Binarytree<T>::Binarytree(Binarytree<T> &&obj)
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
void Binarytree<T>::print(BSTNode<T> *root, int space)
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
BSTNode<T> *Binarytree<T>::searchNode(T value) const
{
    if (root == nullptr)
        return nullptr;
    BSTNode<T> *node = root;
    while (node != nullptr && node->getValue() != value)
    {
        node = node->getChildren()[value < node->getValue()];
    }
    return node;
}

template <typename T>
T *Binarytree<T>::search(T value) const
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
        if (_parent->getChildren()[right] == toDelete)
        {
            _parent->getChildren()[right] = nullptr;
        }
        else
        {
            _parent->getChildren()[left] = nullptr;
        }
        return;
        delete toDelete;
    }

    if (toDelete->oneChildren())
    {
        int side = toDelete->whichChildren();
        if (toDelete != root)
            _parent->getChildren()[value < _parent->getValue()] = toDelete->getChildren()[side];
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
        if (_parent->getChildren()[right] == toDelete)
            _parent->getChildren()[right] = tempNode;
        else
            _parent->getChildren()[left] = tempNode;
    }
    else
        root = tempNode;
    delete toDelete;
}
template <typename T>
BSTNode<T> *Binarytree<T>::predecessorNode(BSTNode<T> *node)
{
    if (node->getChildren()[left] != nullptr)
        return (maximum(node->getChildren()[left]));
    BSTNode<T> *_parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (_parent->getChildren()[right] == node)
            return _parent;
        node = _parent;
        _parent = parentNode(node);
    }
    return nullptr;
}
template <typename T>
BSTNode<T> *Binarytree<T>::successorNode(BSTNode<T> *node)
{
    if (node->getChildren()[right] != nullptr)
        return (minimum(node->getChildren()[right]));
    BSTNode<T> *_parent = parentNode(node);
    while (parentNode(node) != nullptr)
    {
        if (_parent->getChildren()[left] == node)
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
BSTNode<T> *Binarytree<T>::maximum(BSTNode<T> *node)
{
    if (node->getChildren()[right] != nullptr)
        return maximum(node->getChildren()[right]);
    else
        return node;
}
template <typename T>
BSTNode<T> *Binarytree<T>::minimum(BSTNode<T> *node)
{
    if (node->getChildren()[left] != nullptr)
        return minimum(node->getChildren()[left]);
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
        if (node->getChildren()[left]->getValue() < node->getChildren()[right]->getValue())
        {
            return testGoodTree(node->getChildren()[left]) && testGoodTree(node->getChildren()[right]);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return testGoodTree(node->getChildren()[left]) && testGoodTree(node->getChildren()[right]);
    }
}
template <typename T>
void Binarytree<T>::breadthFirst(std::function<void(const T &)> f)
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
    preOrder(f, node->getChildren()[left]);
    f(node->getValue());
    preOrder(f, node->getChildren()[right]);
}
template <typename T>
void Binarytree<T>::postOrder(std::function<void(const T &)> f, BSTNode<T> *node) const
{
    if (node == nullptr)
        return;
    preOrder(f, node->getChildren()[left]);
    preOrder(f, node->getChildren()[right]);
    f(node->getValue());
}
template <typename T>
bool Binarytree<T>::operator==(const Binarytree<T> &tree) const
{
    return *root == *(tree.root);
}
template <typename T>
Binarytree<T>::iterator::~iterator()
{
    delete queue;
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
// template <typename T>
// Binarytree<T>::iterator &Binarytree<T>::iterator::operator++()

// template <typename T>
// iterator Binarytree<T>::iterator::operator++(int)

template <typename T>
int &Binarytree<T>::iterator::operator*()
{
    return queue->front();
}

template <typename T>
bool Binarytree<T>::iterator::operator==(const iterator &it)
{
    return queue->front() == it.queue->front();
}
template <typename T>
bool Binarytree<T>::iterator::operator!=(const iterator &it)
{
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
        node = s.top();
        s.pop();
    } while (!s.empty() || node == nullptr);
    return result;
}
// template <typename T>
// Binarytree<T>::iterator Binarytree<T>::end()
// {
//     return iterator(nullptr_t);
// }

// template <typename T>
// Binarytree<T>::iterator Binarytree<T>::begin()
// {
//     return iterator(root);
// }

#endif // !BINARYTREE_CPP
