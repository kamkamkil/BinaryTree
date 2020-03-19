#define CATCH_CONFIG_MAIN
#include "../src/treeSet.hpp"
#include "../lib/catch/catch.hpp"

TEST_CASE("insert")
{
    Set<int> s;
    
    REQUIRE(*(s.insert(1)) == 1);
}