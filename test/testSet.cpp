#define CATCH_CONFIG_MAIN
#include "../src/treeSet.hpp"
#include "../lib/catch/catch.hpp"

TEST_CASE("test_na_zejecia")
{
    Set<int> s;
    {
        s.insert(8);
        s.insert(4);
        s.insert(10);
        s.insert(10);
        s.insert(2);
        s.insert(5);
        s.insert(9);
        s.insert(12);
        s.insert(12);
        s.insert(1);
        s.insert(14);
        s.insert(7);
        if (auto f = s.find(5))
            REQUIRE(*f == 5);
        s.remove(4);
        if (auto f = s.find(5))
            REQUIRE(*f == 5);
        s.remove(14);
        s.insert(0);
        s.insert(16);
        s.remove(8);
        //todo printSetSizeAndElems(s);
        std::vector<Set<int>> vs, vs2;
        vs.resize(1000);
        for (auto &e : vs)
        {
            e = s;
            e.insert(13);
        }
        vs2.resize(1000);
        for (std::size_t i = 0u; i < vs.size(); ++i)
        {
            vs2[i] = std::move(vs[i]);
        }
        for (auto &e : vs2)
        {
            e.remove(10);
        }
        vs = vs2;
        vs2.clear();
        const auto s2 = std::move(vs.front());
        if (auto f = s2.find(5))
            REQUIRE(*f == 5);
        auto s3 = s2;
        //printSetSizeAndElems(s3);
        s = s3;
        // todo const auto s2 = std::move(vs.front());
    }
    //todo printSetSizeAndElems(s);
}
