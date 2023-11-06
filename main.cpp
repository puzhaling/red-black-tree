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

	std::cout << "\n#INORDER TRAVERSAL:\n\n";
	inorderTree(tree);
	std::cout << std::endl << std::endl;

	tree->deleteValue("a213aa", 2);

	std::cout << "\n#INORDER TRAVERSAL AFTER DELETION:\n\n";
	inorderTree(tree);
	std::cout << std::endl << std::endl;

	deleteTree(tree);

	inorderTree(tree);

	fs.close();
	return 0;
}

