#define CATCH_CONFIG_MAIN
#include "../src/treeSet.hpp"
#include "../lib/catch/catch.hpp"


TEST_CASE("iterator")
{
    int tab[] = {1, 0, 3, 4, 9, 10, -10, 7};
    int correct[] = {-10, 0, 1, 3, 4, 7, 9, 10};
    Set<int> set;
    // CHECK_THROWS(set.begin());
    for (size_t i = 0; i < 8; i++)
    {
        set.insert(tab[i]);
    }
    int n = 0;
    for (Set<int>::iterator iterator = set.begin(); iterator != set.end(); iterator++)
    {
        CHECK(*iterator == correct[n]);
        n++;
    }
    n = 0;
    for (const auto &e : set)
    {
        CHECK(e == correct[n]);
        n++;
    }
}