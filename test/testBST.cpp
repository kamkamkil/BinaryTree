#define CATCH_CONFIG_MAIN

#include "../lib/catch/catch.hpp"
#include "../src/Binarytree.hpp"
#include <iterator>
#include <iostream>
TEST_CASE("size_put_contain")
{
    Binarytree<int> tree;
    REQUIRE(tree.size() == 0);
    tree.put(1);
    tree.put(2);
    tree.put(3);
    REQUIRE(tree.size() == 3);
    REQUIRE(tree.contains(2));
}
TEST_CASE("search")
{
    int tab[] = {1, 4, 2, 6, 3, 7};
    Binarytree<int> tree;
    tree.put(tab, 6);
    REQUIRE(*tree.search(1) == 1);
    REQUIRE(*tree.search(4) == 4);
    REQUIRE(*tree.search(6) == 6);
}
TEST_CASE("tab_put")
{
    int tab[] = {1, 4, 2, 6, 3, 7};
    Binarytree<int> tree;
    tree.put(tab, 6);
    REQUIRE(tree.size() == 6);
    REQUIRE(tree.contains(1));
    REQUIRE(tree.contains(3));
    REQUIRE(tree.contains(2));
}
TEST_CASE("remove_no/single_child", "[remove]")
{
    int tab[] = {5, 7, 4, 14, 13, 6, 2, 11, 8, 1, 3, 10};
    Binarytree<int> tree;
    tree.put(tab, 12);
    tree.remove(1);
    REQUIRE_FALSE(tree.contains(1));
    tree.remove(8);
    REQUIRE_FALSE(tree.contains(8));
    REQUIRE(tree.contains(10));
    REQUIRE(tree.size() == 10);
}
TEST_CASE("remove_two_child", "[remove]")
{
    int tab[] = {0, 10, 30, 5, 35, 2, 7, 32, 36, 50, 51, 52, 40, 41};
    Binarytree<int> tree;
    tree.put(tab, 14);
    REQUIRE(tree.size() == 14);
    SECTION("childe are leafs")
    {
        tree.remove(5);
        REQUIRE_FALSE(tree.contains(5));
        REQUIRE(tree.contains(2));
        REQUIRE(tree.contains(7));
        REQUIRE(tree.testGoodTree());
    }
    SECTION("middle of tree")
    {
        tree.remove(35);
        REQUIRE_FALSE(tree.contains(35));
        REQUIRE(tree.contains(32));
        REQUIRE(tree.testGoodTree());
    }
    SECTION("middle of tree2")
    {
        tree.remove(50);
        REQUIRE_FALSE(tree.contains(50));
        REQUIRE(tree.contains(52));
        REQUIRE(tree.testGoodTree());
    }
}
TEST_CASE("remove_root", "[remove]")
{
    Binarytree<int> tree(10);
    SECTION("only root")
    {
        tree.remove(10);
        REQUIRE(tree.size() == 0);
    }
    tree.put(13);
    tree.put(15);
    tree.put(12);
    SECTION("root with one leaf")
    {
        tree.remove(10);
        REQUIRE(tree.testGoodTree());
        REQUIRE_FALSE(tree.contains(10));
        REQUIRE(tree.contains(13));
        REQUIRE(tree.contains(15));
        REQUIRE(tree.contains(12));
    }
    tree.put(5);
    tree.put(1);
    tree.put(6);
    SECTION("root with two leafs")
    {
        tree.remove(10);
        REQUIRE(tree.testGoodTree());
        REQUIRE_FALSE(tree.contains(10));
        REQUIRE(tree.contains(13));
        REQUIRE(tree.contains(15));
        REQUIRE(tree.contains(5));
        REQUIRE(tree.contains(1));
    }
}
TEST_CASE("minimum")
{
    int tab[] = {1, 4, 2, 6, 3, 7};
    Binarytree<int> tree;
    tree.put(tab, 6);
    REQUIRE(tree.minimum() == 1);
}
TEST_CASE("maximum")
{
    int tab[] = {1, 4, 2, 6, 3, 7};
    Binarytree<int> tree;
    tree.put(tab, 6);
    REQUIRE(tree.maximum() == 7);
}
TEST_CASE("Successor")
{
    int tab[] = {5, 7, 4, 14, 13, 6, 2, 11, 8, 1, 3, 10};
    Binarytree<int> tree;
    tree.put(tab, 12);
    REQUIRE(tree.successor(7) == 8);
    REQUIRE(tree.successor(3) == 4);
}
TEST_CASE("Predecessor")
{
    int tab[] = {5, 7, 4, 14, 13, 6, 2, 11, 8, 1, 3, 10};
    Binarytree<int> tree;
    tree.put(tab, 12);
    REQUIRE(tree.predecessor(4) == 3);
    REQUIRE(tree.predecessor(8) == 7);
}
TEST_CASE("Parent")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    Binarytree<int> tree;
    tree.put(tab, 8);
    REQUIRE(tree.parent(-10) == 0);
    REQUIRE(tree.parent(3) == 1);
}
TEST_CASE("Copy_Constructor", "[Constructor]")
{
    Binarytree<int> tree;
    SECTION("empty tree")
    {
        Binarytree<int> copyTree(tree);
        REQUIRE(copyTree.size() == 0);
        REQUIRE(tree == copyTree);
    }
    SECTION("full tree")
    {
        int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
        tree.put(tab, 8);
        Binarytree<int> copyTree(tree);
        REQUIRE(copyTree.size() == 8);
        REQUIRE(tree == copyTree);
    }
}
TEST_CASE("move_constructor", "[Constructor]")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    Binarytree<int> tree;
    tree.put(tab, 8);
    Binarytree<int> moveTree = std::move(tree);
    REQUIRE(tree.empty());
    REQUIRE(moveTree.size() == 8);
    REQUIRE(moveTree.contains(3));
}
TEST_CASE("==_operator_same_tree", "[operator]")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    Binarytree<int> tree;
    Binarytree<int> tree2;
    REQUIRE(tree == tree2);
    tree.put(tab, 8);
    tree2.put(tab, 8);
    REQUIRE(tree == tree2);
}
TEST_CASE("==_operator_diffrent_tree", "[operator]")
{
    Binarytree<int> tree;
    Binarytree<int> tree2;
    SECTION("same tree shuffle order")
    {
        int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
        int tab2[] = {0, 1, 4, 3, -10, 10, 7, 1};
        tree.put(tab, 8);
        tree2.put(tab2, 8);
        REQUIRE_FALSE(tree == tree2);
    }
    SECTION("completely diffrent tree")
    {
        int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
        int tab2[] = {6, 3, 2, 9, 10, 22, -10, -5, 30, 12, 100};
        tree.put(tab, 8);
        tree2.put(tab, 11);
        REQUIRE_FALSE(tree == tree2);
    }
}
TEST_CASE("&=_operator", "[operator]")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    Binarytree<int> tree;
    Binarytree<int> tree2;
    SECTION("empty tree")
    {
        tree2 = tree;
        REQUIRE(tree == tree2);
    }
    SECTION("first tree full")
    {
        tree.put(tab, 8);
        tree2 = tree;
        REQUIRE(tree == tree2);
        tree2.remove(10);
        REQUIRE(tree.contains(10));
    }
    SECTION("secont tree full")
    {
        tree2.put(tab, 8);
        tree2 = tree;
        REQUIRE(tree == tree2);
    }
    SECTION("both tree full")
    {
        int tab2[] = {5, 7, 3, 1, 2, 5, -1, 21, 4};
        tree.put(tab, 8);
        tree2.put(tab2, 9);
        tree2 = tree;
        tree2.remove(10);
        REQUIRE(tree.contains(10));
    }
}
TEST_CASE("&&=_operator", "[operator]")
{

    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    Binarytree<int> tree;
    Binarytree<int> tree2;
    SECTION("empty tree")
    {
        tree = std::move(tree2);
        REQUIRE(tree2.size() == 0);
    }
    SECTION("first tree full")
    {
        tree.put(tab, 8);
        tree2 = std::move(tree);
        REQUIRE(tree.size() == 0);
        REQUIRE(tree2.size() == 8);
        for (size_t i = 0; i < 8; i++)
        {
            REQUIRE(tree2.contains(tab[i]));
        }
    }
    SECTION("secont tree full")
    {
        tree2.put(tab, 8);
        tree2 = std::move(tree);
        REQUIRE(tree.empty());
        REQUIRE(tree2.empty());
    }
    SECTION("both tree full")
    {
        int tab2[] = {5, 7, 3, 1, 2, 5, -1, 21, 4};
        tree.put(tab, 8);
        tree2.put(tab2, 9);
        tree2 = std::move(tree);
        REQUIRE(tree.empty());
        REQUIRE(tree2.size() == 8);
        for (size_t i = 0; i < 8; i++)
        {
            REQUIRE(tree2.contains(tab[i]));
        }
    }
}
TEST_CASE("iterator", "[iterator]")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    int correct[] = {-10, 0, 1, 3, 4, 7, 9, 10};
    Binarytree<int> tree;
    REQUIRE_THROWS(tree.begin());
    tree.put(tab, 8);
    int n = 0;
    for (Binarytree<int>::iterator iterator = tree.begin(); iterator != tree.end(); iterator++)
    {
        REQUIRE(*iterator == correct[n]);
        n++;
    }
    n = 0;
    for (const auto &e : tree)
    {
        REQUIRE(e == correct[n]);
        n++;
    }
}
