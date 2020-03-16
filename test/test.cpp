#define CATCH_CONFIG_MAIN

#include "../lib/catch/catch.hpp"
#include "../src/Binarytree.hpp"

TEST_CASE( "size", "[single-file]" ) {
    Binarytree<int> tree;
    REQUIRE( tree.size() == 0 );
    tree.put(1);
    tree.put(2);
    tree.put(3);
    REQUIRE(tree.size() == 3);
}
//

