#include "BinaryTree.cpp"
#include "test.cpp"
int main(int argc, char const *argv[])
{
    Binarytree<int> temp(1);
    temp.put(7);
    temp.put(2);
    temp.put(5);
    temp.put(0);
    temp.put(4);
    temp.put(6);
    int tempe = temp.search(6);

    temp.print();
    return 0;
}
