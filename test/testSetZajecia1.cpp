

#include <iostream>
#include "../src/treeSet.hpp"

using namespace std;

template <typename T>
void printSetSizeAndElems(const Set<T> &s)
{
    std::cout << "Size: " << s.size() << std::endl;
    s.inorder([](const T &e) { std::cout << e << ", "; });
    std::cout << std::endl;
}

int main()
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
            std::cout << "Found: " << *f << std::endl;
        s.remove(4);
        if (auto f = s.find(5))
            std::cout << "Found: " << *f << std::endl;
        s.remove(12);
        s.remove(14);
        s.insert(0);
        s.insert(16);
        s.remove(8);
        printSetSizeAndElems(s);
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
            std::cout << "Found: " << *f << std::endl;
        auto s3 = s2;
        printSetSizeAndElems(s3);
        s = s3;
    }
    printSetSizeAndElems(s);

    return 0;
}
