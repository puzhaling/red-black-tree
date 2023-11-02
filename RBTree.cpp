
#include "libraries.h"
#include "RBTreeClass.h"
#include "helpFunctions.h"

int
main() {
	std::string file_name{ "input.txt" };
	std::fstream fs(file_name);

	RBTree* tree{ new RBTree() };
	std::uint32_t line_number{ 1 };

	std::string text{};
	while (fs >> text) {
	if (isvalid(text)) 
	 	tree->insert(text, line_number++);
	}

	inorder(tree);
	deleteTree(tree);

	std::cout << "\nAFTER DELETION:\n";
	inorder(tree);

	fs.close();
	return 0;
}