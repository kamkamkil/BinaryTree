testBST.exe : testBST.o
	g++ testBST.cpp -o testBST.o -c
main.exe : node.o BinaryTree.o  testBST.o
	g++ main.cpp -o mmain.exe
set.o :  node.o BinaryTree.o
	g++ set.cpp -o set.exe -c
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
