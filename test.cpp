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
        tree.print();
    return true;
}
bool testAll(bool talk = true)
{
    bool result = true;
    result = true && testPutContain(talk);
    result = result && testPrint(talk);

    return result;
}
#endif // !TEST_BSTTREE