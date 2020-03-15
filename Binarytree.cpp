
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "Node.cpp"
#include <queue>
#include <stack>
#include <iostream>
//to nie działa na linux
// #include "printWinFun.cpp"//!!
//

template <typename T>
class Binarytree
{
private:
    BSTNode <T>*root;
    void put(T data,BSTNode<T> *node);
    void print(BSTNode<T> *root, int space);
public:
    Binarytree(T head);
    Binarytree(); //todo
    ~Binarytree();
    void put(T data);
    int hight();
    void print();
};

template <typename T>
Binarytree<T>::Binarytree(T head)
{
    root = new BSTNode<T>(head);
}
template<typename T>
Binarytree<T>::~Binarytree()
{
    delete root;
}
template<typename T>
void Binarytree<T>::put(T data)
{
    put(data,root);
}
template<typename T>
void Binarytree<T>::put(T data,BSTNode<T> *node)
{
    while (node->getChildren()[data < (node->getData())] != nullptr)
    {
        node = node->getChildren()[data < node->getData()];
    }
    node->put(data);
}
template<typename T>
void Binarytree<T>::print(BSTNode<T> *root, int space)
{
    const int gap = 5;
    if (root == NULL)  
        return;  
    space += gap;  
    print(root->getChildren()[0], space);  
    std::cout<<std::endl;  
    for (int i = gap; i < space; i++)  
        std::cout<<" ";  
    std::cout<<root->getData()<<std::endl;  
    print(root->getChildren()[1], space);  
}







template<typename T>
void Binarytree<T>::print()
{
    print(root,0);
}
template<typename T>
int Binarytree<T>::hight()
{
    return 0;
}

#endif // !BINARYTREE_CPP
