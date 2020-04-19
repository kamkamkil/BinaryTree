#define CATCH_CONFIG_MAIN
#include "../lib/catch/catch.hpp"
#include "../src/Map.hpp"
#include <iterator>
#include <utility>
#include <iostream>
#include "../src/constPair.hpp"


TEST_CASE("const_iterator", "[iterator]")
{
}

TEST_CASE("insert")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    std::pair<int, int> p5(1, 3);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    map.insert(p5);
    REQUIRE(map.size() == 4);
}

TEST_CASE("find")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    std::pair<int, int> p5(1, 3);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    map.insert(p5);
    constPair<int,int> pair1(1,3);
    constPair<int,int> pair2(2,6);
    REQUIRE(*map.find(1) == pair1);
    REQUIRE(*map.find(2) == pair2);
}