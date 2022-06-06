#include <iostream>
#include "Tridy.h"

int main() {
	BinaryTree tree;
	tree.Insert(6);
	tree.Print();
	tree.Insert(9);
	tree.Print();
	tree.Insert(10);
	tree.Print();
	tree.Insert(3);
	tree.Print();
	tree.Insert(1);
	tree.Print();
	tree.Insert(5);
	tree.Print();
	tree.Insert(8);
	tree.Print();
	tree.Insert(0);
	tree.Insert(6);
	tree.Insert(4);
	tree.Insert(2);

	tree.Print();

	tree.Delete(0);
	tree.Print();

	tree.Delete(9);
	tree.Print();

	return 0;
}
