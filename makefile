

set.o :  node.o BinaryTree.o
	g++ set.cpp -o set.exe -c
main.exe : node.o BinaryTree.o printWinFun.o test.o
	g++ main.cpp -o main.exe
node.o : node.cpp
	g++ node.cpp -c
printWinFun.o : printWinFun.cpp	
	g++ printWinFun.cpp -c
BinaryTree.o : BinaryTree.cpp
	g++ BinaryTree.cpp -c
testBST.o -o : testBST.cpp	
	g++ testBST.cpp -c
.PHONY : run 
run:
	make main.exe
	./main.exe
