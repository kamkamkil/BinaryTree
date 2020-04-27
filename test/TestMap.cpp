#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/Map.hpp"
#include <iterator>
#include <utility>
#include <iostream>
#include "../src/constPair.hpp"
#include <string>

TEST_CASE("string")
{
    Map<int, std::string> m;
    std::pair<Map<int,std::string>::Iterator,bool> pair(m.insert({8, "eight"}));
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) == "eight");

    pair = m.insert({4, "four"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "four");
    
    pair = m.insert({10, "ten"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "ten");
    
    pair = m.insert({10, "2nd ten"});
    REQUIRE (pair.second == false);
    REQUIRE(*(pair.first) ==  "ten");
    
    pair = m.insert({2, "two"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "two");

    pair = m.insert({5, "five"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "five");

    pair = m.insert({9, "nine"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "nine");

    pair = m.insert({12, "twelve"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "twelve");

    pair = m.insert({12, "2nd twelve"});
    REQUIRE (pair.second == false);
    REQUIRE(*(pair.first) ==  "twelve");
    
    pair = m.insert({1, "one"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "one");

    pair = m.insert({14, "fourteen"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "fourteen");
    
    pair = m.insert({7, "seven"});
    REQUIRE (pair.second == true);
    REQUIRE(*(pair.first) ==  "seven");
    
    SECTION("size")
    {
        REQUIRE(m.size() == 10);
    }
    SECTION("find")
    {
        CHECK(*m.find(2) == "two");
        CHECK(*m.find(7) == "seven");
        CHECK(*m.find(14) == "fourteen");
        CHECK(*m.find(10) == "ten");
        CHECK(*m.find(1) == "one");
        CHECK(*m.find(12) == "twelve");
    }
    SECTION("remove")
    {
        REQUIRE(m.remove(1) == true);
        REQUIRE(m.remove(2) == true);
        REQUIRE(m.remove(4) == true);
        REQUIRE(m.remove(7) == true);
        REQUIRE(m.remove(8) == true);
        REQUIRE(m.remove(20) == false);
        REQUIRE(m.remove(1) == false);
    }
    // SECTION("printing")
    // {
    //     for (auto it = m.begin(); it != m.end(); ++it)
    //     {
    //         std::cout << *it << ", ";
    //     }
    //     std::cout << std::endl;
    //     for (auto &e : m)
    //     {
    //         std::cout << e << ", ";
    //     }
    // }
}
TEST_CASE("insert")
{
    SECTION("int,int")
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
    };
    SECTION("char,int")
    {
        Map<char, int> map;
        map.insert({1, 'a'});
        map.insert({2, 'b'});
        map.insert({3, 'c'});
        map.insert({4, 'd'});
        map.insert({5, 'e'});
        REQUIRE(map.size() == 5);
    }
}

TEST_CASE("find")
{
    SECTION("int,int")
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
        constPair<int, int> pair1(1, 3);
        constPair<int, int> pair2(2, 6);
        REQUIRE(*map.find(1) == 2);
        REQUIRE(*map.find(2) == 6);
    }
    SECTION("int,char")
    {
        Map<char, int> map;
        map.insert({1, 'a'});
        map.insert({2, 'b'});
        map.insert({3, 'c'});
        map.insert({4, 'd'});
        map.insert({5, 'e'});
        REQUIRE(*map.find(1) == 'a');
        REQUIRE(*map.find(2) == 'b');
        REQUIRE(*map.find(3) == 'c');
        REQUIRE(*map.find(4) == 'd');
    }
}

TEST_CASE("remove")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    REQUIRE(map.remove(1) == true);
    REQUIRE(map.remove(2) == true);
    REQUIRE(map.remove(3) == true);
    REQUIRE(map.remove(1) == false);
    REQUIRE(map.size() == 1);
}

TEST_CASE("member_acces", "[operator]")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    REQUIRE(map[1] == 2);
    REQUIRE(map[2] == 6);
    REQUIRE(map[3] == 5);
    REQUIRE(map[4] == 4);
    map[1] = 1;
    REQUIRE(map[1] == 1);
    map[5] = 10;
    map[5] = 10;
    REQUIRE(map[5] == 10);
}
TEST_CASE("constIterator", "[iterator]")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    int i = 0;
    int n[] = {2, 6, 5, 4};
    for (const auto &e : map)
    {
        REQUIRE(e == n[i]);
        i++;
    }
}

TEST_CASE("Iterator", "[iterator]")
{
    Map<int, int> map;
    std::pair<int, int> p1(1, 2);
    std::pair<int, int> p2(2, 6);
    std::pair<int, int> p3(3, 5);
    std::pair<int, int> p4(4, 4);
    map.insert(p1);
    map.insert(p2);
    map.insert(p3);
    map.insert(p4);
    int i = 0;
    int n[] = {2, 6, 5, 4};
    for (auto &e : map)
    {
        REQUIRE(e == n[i]);
        e = 1;
        REQUIRE(e == 1);
        i++;
    }
}
// TEST_CASE("-> operator", "[operator]") //todo
// {
//     Map<int, int> map;
//     std::pair<int, int> p1(1, 2);
//     std::pair<int, int> p2(2, 6);
//     std::pair<int, int> p3(3, 5);
//     std::pair<int, int> p4(4, 4);
//     map.insert(p1);
//     map.insert(p2);
//     map.insert(p3);
//     map.insert(p4);
//     auto *it = &map.find(1);
// }