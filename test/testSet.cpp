#define CATCH_CONFIG_MAIN
#include "../src/treeSet.hpp"
#include "../lib/catch/catch.hpp"

TEST_CASE("insert")
{
    Set<int> s;
    REQUIRE(*(s.insert(1)) == 1);
    REQUIRE(*(s.insert(2)) == 2);
    REQUIRE(*(s.insert(1)) == 1);
    REQUIRE(*(s.insert(4)) == 4);
    REQUIRE((s.insert(4)) == (s.insert(4)));
    REQUIRE(s.size() == 3);
}
TEST_CASE("remove")
{
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(1);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    REQUIRE(s.size() == 5);
    REQUIRE(s.remove(1));
    REQUIRE(s.size() == 4);
    REQUIRE(s.remove(6));
    REQUIRE(s.size() == 3);
    REQUIRE_FALSE(s.remove(1));
}

TEST_CASE("find")
{
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(1);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(12);
    s.insert(13);
    s.insert(14);
    s.insert(15);
    REQUIRE(*(s.find(1)) == 1);
    REQUIRE(*(s.find(2)) == 2);
    REQUIRE(*(s.find(12)) == 12);
    REQUIRE(s.find(100) == nullptr);
}
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