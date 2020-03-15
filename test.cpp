#ifndef TEST_BSTTREE
#define TEST_BSTTREE
#include "BinaryTree.cpp"
#include "test.cpp"
#include <iostream>

bool testPutContain(bool talk)
{
    Binarytree<int> tree;
    tree.put(1);
    tree.put(0);
    tree.put(3);
    tree.put(4);
    if (tree.contains(3) && tree.contains(1))
    {
        if (talk)
            std::cout << "put/contain test pass" << std::endl;
        return true;
    }
    return false;
}
bool testPrint(bool talk)
{
    Binarytree<int> tree;
    tree.put(1);
    tree.put(0);
    tree.put(3);
    tree.put(4);
    if (talk)
        {
            tree.print();
            std::cout << "print Test pass" << std::endl;
        }
    return true;
}
bool testDelete(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(1);
    tree.put(0);
    tree.put(3);
    tree.put(4);
    tree.put(9);
    tree.put(10);
    tree.print();
    tree.delate(10);
    tree.delate(4);
    if(tree.contains(10))
        {
            std::cout << "delate test fail : tree shouldn't contain 10" << std::endl;
            result == false;
        }
    if(tree.contains(4))
        {
            std::cout << "delate test fail : tree should contain 10" << std::endl;
            result == false;
        }
    if(talk && result)
        std::cout << "delate test pass" << std::endl;
        return result;
}
bool testAll(bool talk = true)
{
    bool result = true;
    // result = true && testPutContain(talk);
    result = result && testPrint(talk);
    // result = result && testDelete(talk);
    return result;
}
#endif // !TEST_BSTTREE