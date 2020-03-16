#define CATCH_CONFIG_MAIN

#include "../lib/catch/catch.hpp"
#include "../src/Binarytree.hpp"
//test about sie
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
    int tab[] = {1,0,3,4,9,10,-10,7};
    Binarytree<int> tree;
    tree.put(tab,8)
    REQUIRE(tree.parent(-10) == 0);
    REQUIRE(tree.parent(3) == 1);

}

