#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"
#include "../Binarytree.cpp"

TEST_CASE( "size", "[single-file]" ) {
    Binarytree<int> tree;
    REQUIRE( tree.size() == 0 );
    tree.put(1);
    tree.put(2);
    tree.put(3);
    REQUIRE(tree.size() == 3);
}
TEST_CASE( "predecessor", "[single-file]" ) {


