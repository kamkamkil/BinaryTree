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
    else
    {
        if (talk)
            std::cout << "put/contain test fail" << std::endl;
        return false;
    }
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
    tree.delate(10);
    tree.delate(4);
    if (tree.contains(10))
    {
        std::cout << "delate test fail : tree shouldn't contain 10" << std::endl;
        result == false;
    }
    if (tree.contains(4))
    {
        std::cout << "delate test fail : tree should contain 10" << std::endl;
        result == false;
    }
    if (talk && result)
        std::cout << "delate test pass" << std::endl;
    return result;
}
bool testMax(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(1);
    if (tree.maximum() != 1)
    {
        result = false;
        if (talk)
            std::cout << "max test fail should be 1 but it is : " << tree.maximum() << std::endl;
    }
    tree.put(0);
    tree.put(3);
    if (tree.maximum() != 3)
    {
        result = false;
        if (talk)
            std::cout << "max test fail should be 3 but it is : " << tree.maximum() << std::endl;
    }
    tree.put(4);
    tree.put(9);
    tree.put(10);
    tree.put(-10);
    tree.put(7);
    if (tree.maximum() != 10)
    {
        result = false;
        if (talk)
            std::cout << "max test fail should be 10 but it is : " << tree.maximum() << std::endl;
    }
    if (!result && talk)
    {
        std::cout << "max test fail" << std::endl;
    }
    if (result && talk)
    {
        std::cout << "max test pass" << std::endl;
    }
    return result;
}
bool testMin(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(1);
    if (tree.minimum() != 1)
        result = false;
    tree.put(0);
    tree.put(3);
    if (tree.minimum() != 0)
        result = false;
    tree.put(4);
    tree.put(9);
    tree.put(10);
    tree.put(-10);
    tree.put(7);
    if (tree.minimum() != -10)
        result = false;
    if (!result && talk)
    {
        std::cout << "min test fail" << std::endl;
    }
    if (result && talk)
    {
        std::cout << "min test pass" << std::endl;
    }
    return result;
}
bool testParent(bool talk = true)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(1);
    tree.put(0);
    tree.put(3);
    tree.put(4);
    tree.put(9);
    tree.put(10);
    tree.put(-10);
    tree.put(7);
    if (tree.parent(-10) != 0)
    {
        result = false;
        if (talk)
            std::cout << "parent test fail should be 0 but it is:" << tree.parent(-10) << std::endl;
    }
    if (tree.parent(3) != 1)
    {
        result = false;
        if (talk)
            std::cout << "parent test fail should be 1 but it is:" << tree.parent(-10) << std::endl;
    }
    if (result && talk)
        std::cout << "parent test pass" << std::endl;
    return result;
}
bool testSuccessor(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(5);
    tree.put(7);
    tree.put(4);
    tree.put(14);
    tree.put(13);
    tree.put(6);
    tree.put(2);
    tree.put(11);
    tree.put(8);
    tree.put(1);
    tree.put(3);
    tree.put(10);
    if (tree.successor(7) != 8)
    {
        result = false;
        if (talk)
            std::cout << "Successor test failed for 7 should be 8 but it is : " << tree.successor(14) << std::endl;
    }
    if (tree.successor(3) != 4)
    {
        result = false;
        if (talk)
            std::cout << "Successor test failed for 4 should be 4 but it is : " << tree.successor(14) << std::endl;
    }
    if (result && talk)
        std::cout << "successor test pass" << std::endl;

    return result;
}
bool testPredecessor(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(5);
    tree.put(7);
    tree.put(4);
    tree.put(14);
    tree.put(13);
    tree.put(6);
    tree.put(2);
    tree.put(11);
    tree.put(8);
    tree.put(1);
    tree.put(3);
    tree.put(10);
    if (tree.predecessor(4) != 3)
    {
        result = false;
        if (talk)
            std::cout << "predecessor test failed for 3 should be 3 but it is : " << tree.predecessor(4) << std::endl;
    }

    if (tree.predecessor(8) != 7)
    {
        result = false;
        if (talk)
            std::cout << "predecessor test failed for 8 should be 7 but it is : " << tree.predecessor(8) << std::endl;
    }
    if (result && talk)
        std::cout << "predecessor test pass" << std::endl;

    return result;
}
bool testAll(bool talk = true)
{
    bool result = true;
    // result &= testPrint(talk);
    result &= testPutContain(talk);
    // result &= testDelete(talk);
    result &= testMin(talk);
    result &= testMax(talk);
    result &= testParent(talk);
    result &= testSuccessor(talk);
    result &= testPredecessor(talk);

    return result;
}
#endif // !TEST_BSTTREE