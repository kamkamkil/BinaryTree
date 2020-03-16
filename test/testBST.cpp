#ifndef TEST_BSTTREE
#define TEST_BSTTREE
#define CATCH_CONFIG_MAIN
#include "BinaryTree.cpp"
#include <iostream>
void visit(int k)
{
    std::cout << "i'm in ->" << k << std::endl;
}
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
bool testRemove(bool talk)
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
    tree.remove(1);
    if (tree.contains(1))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (leaf)" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass(leaf) " << std::endl;

    tree.remove(8);
    if (tree.contains(8))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (one child, still in tree)" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (one child, delated)" << std::endl;
    if (!tree.contains(10))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (one child, delate too much)" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (one child, child remain)" << std::endl;
    return result;
}
bool testRemoveTwoChild(bool talk)
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
    tree.remove(1);
    tree.remove(8);
    tree.put(15);
    tree.remove(14);

    if (tree.contains(14))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (two child,single successor as leaf and child)" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child,single successor as leaf and child)" << std::endl;
    if (!tree.testGoodTree())
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (two child,single successor as leaf and child),bad tree" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child,single successor as leaf and child),good tree" << std::endl;
    if (tree.size() != 10)
    {
        result = false;
        if (talk)
            std::cout << "test remove fail (two child,single successor as leaf and child) wrong size should be : 10 but is : " << tree.size() << std::endl;
    }
    Binarytree<int> tree2;
    tree2.put(20);
    tree2.put(10);
    tree2.put(5);
    tree2.put(7);
    tree2.put(3);
    tree2.put(1);
    tree2.put(2);
    tree2.put(8);
    tree2.put(9);
    tree2.remove(5);
    if (tree2.contains(5))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (two child,couple node in row )" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child,couple node in row)" << std::endl;
    if (!tree2.testGoodTree())
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (two child,couple node in row) bad tree" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child,couple node in row) good tree" << std::endl;
    if (tree2.size() != 8)
    {
        result = false;
        if (talk)
            std::cout << "test remove fail (two child,couple node in row) wrong size should be : 8 but is : " << tree2.size() << std::endl;
    }
    Binarytree<int> tree3;
    tree3.put(100);
    tree3.put(50);
    tree3.put(75);
    tree3.put(25);
    tree3.put(70);
    tree3.put(65);
    tree3.put(60);
    tree3.put(80);
    tree3.put(85);
    tree3.put(71);
    tree3.put(72);
    tree3.put(73);
    tree3.put(79);
    tree3.remove(75);
    if (tree3.contains(57))
    {
        result = false;
        if (talk)
            std::cout << "test delate fail (two child)" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child)" << std::endl;
    if (!tree3.testGoodTree())
    {
        result = false;
        if (talk)
            std::cout << "test delate (two child) fail bad tree" << std::endl;
    }
    else if (talk)
        std::cout << "test delate pass (two child) good tree" << std::endl;
    if (tree3.size() != 12)
    {
        result = false;
        if (talk)
            std::cout << "test remove fail (two child) wrong size should be : 12 but is : " << tree2.size() << std::endl;
    }
    return result;
}
bool testRemoveRoot(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    tree.put(1);
    tree.remove(1);
    if (tree.contains(1))
    {
        result = false;
        if (talk)
            std::cout << "test remove root fail (only one leaf in tree)" << std::endl;
    }
    else if (talk)
        std::cout << "test remove root pass (only one leaf in tree)" << std::endl;
    tree.put(1);
    tree.put(2);
    tree.put(3);
    tree.remove(1);
    if (tree.contains(1))
    {
        result = false;
        if (talk)
            std::cout << "test remove root fail (root with single child)" << std::endl;
    }
    else if (talk)
        std::cout << "test remove root pass (root with single child)" << std::endl;
    if (tree.size() != 2)
    {
        result = false;
        if (talk)
            std::cout << "test remove root fail (root with single child) wrong size should be : 2 but is : " << tree.size() << std::endl;
    }
    else if (talk)
        std::cout << "test remove root pass( with single child) right size" << std::endl;
    tree.put(0);
    tree.remove(2);
    if (tree.contains(2))
    {
        result = false;
        if (talk)
            std::cout << "test remove root fail (root with two child) object not delated " << tree.size() << std::endl;
    }
    else if (talk)
        std::cout << "test remove root pass (root with two child) object delated" << std::endl;
    if (tree.size() != 2)
    {
        result = false;
        if (talk)
            std::cout << "test remove root fail (root with two child) wrong size should be : 2 but is : " << tree.size() << std::endl;
    }
    else if (talk)
        std::cout
            << "test remove root pass( with two child) right size" << std::endl;
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
bool testSize(bool talk)
{
    bool result = true;
    Binarytree<int> tree;
    if (tree.size() != 0)
    {
        result = false;
        if (talk)
            std::cout << "size test fail (empty)" << std::endl;
    }
    else
    {
        std::cout << "size test pass (empty)" << std::endl;
    }

    tree.put(1);
    tree.put(3);
    tree.put(0);
    tree.put(2);
    if (tree.size() != 4)
    {
        result = false;
        if (talk)
            std::cout << "size test fail should be 4 but it is : " << tree.size() << std::endl;
    }
    if (result && talk)
        std::cout << "size test pass" << std::endl;
    return result;
}
bool testbreadthFirst(bool talk)
{
    Binarytree<int> tree;
    tree.put(5);
    tree.put(7);
    tree.put(4);
    tree.put(14);
    tree.put(13);
    tree.put(6);
    tree.put(2);
    tree.breadthFirst(visit);
    return true;
}
bool testTab()
{
    int tab[]= {1,2,3,4,5};
    Binarytree<int> tree(tab,5);
    tree.print();
}
bool testAll(bool talk = true)
{
    bool result = true;
    // result &= testPrint(talk);
    // result &= testPutContain(talk);
    // result &= testRemove(talk);
    // result &= testRemoveTwoChild(talk);
    // result &= testRemoveRoot(talk);
    // result &= testMin(talk);
    // result &= testMax(talk);
    // result &= testParent(talk);
    // result &= testSuccessor(talk);
    // result &= testPredecessor(talk);
    // result &= testSize(talk);
    // result &= testbreadthFirst(talk);
    testTab();
    return result;
}
#endif // !TEST_BSTTREE