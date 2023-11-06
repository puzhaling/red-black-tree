#include "libraries.h"
#include "helpFunctions.h"
#include "RBTreeClass.h"

int main() {
	RBTree* tree{ new RBTree() };
	
	std::ifstream in("input.txt");

	short int line_number{ 1 };
	std::string str{};
	
	while (in >> str) {
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

	std::ofstream out;
	out.open("output.txt");

	writeDownInfo(out, tree->root);

	deleteTree(tree);
	inorderTree(tree);

	in.close();
	out.close();
	return 0;
}

