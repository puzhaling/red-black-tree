#include "libraries.h"
#include "helpFunctions.h"
#include "RBTreeClass.h"

int main() {
	RBTree* tree{ new RBTree() };
	
	std::fstream fs("input.txt");

	short int line_number{ 1 };
	std::string str{};
	
	while (fs >> str) {
		if (isvalid(str)) {
			tree->insertValue(str, line_number++);
		}
	}
	tree->inorder();

	tree->deleteValue("a213aa", 5);

	std::cout << "\n\n\n\n";

	tree->inorder();
	return 0;
}

