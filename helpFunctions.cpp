#include "libraries.h"
#include "RBTreeClass.h"

bool
isvalid(std::string_view key) {
	size_t length{ key.length() };
	return (length == 6) ? (isalpha(key[0]) && isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) && isalpha(key[4]) && isalpha(key[5])) : false;
}

ListNode*
getListNode(size_t line_number) {
	return new ListNode(line_number);
}

Carplate* 
getCarplate(const std::string& key) {
	return new Carplate{ key.substr(1, 3), key.substr(0, 1) + key.substr(4, 2) };
}

void
printList(ListNode* head) {
	while (head != nullptr) {
		std::cout << head->line_number << ' ';
		head = head->next;
	}
	std::cout << std::endl;
}

bool
isTNULL(Node* node) {
	return (node->left == nullptr && node->right == nullptr);
}

bool
isLastInList(ListNode* head) {
	return (head->next == nullptr);
}

size_t 
getListLength(ListNode* head) {
	size_t res{};
	/*
	since the list is NEVER 
	empty - the length will be at least 1
	*/
	do {
		head = head->next;
		res++;
	} while (head != nullptr);

	return res;
}

void
writeDownInfo(std::ofstream& out, Node* node) {
	if (isTNULL(node)) {
		return;
	}

	writeDownInfo(out, node->left);
	writeDownInfo(out, node->right);

	size_t listLength{ getListLength(node->head) };
	while (listLength--)
		out << node->carplate << ' ';
	out << std::endl << std::endl;
}

/*
	RETURN VALUES:
		0: node with provided line_number 
			wasn't found => everything left the same
		1: head was deleted;
		2: other list node was deleted;
*/
std::uint16_t
deleteListNode(ListNode* head, size_t line_number) {
	if (line_number == head->line_number) {
		/*
		since we cannot move the head due to the copy 
		of the pointer, if it is necessary to delete 
		the head, we SWAP the values of the head and the head's neighbor and delete the neighbor
		*/
		if (head->next != nullptr) {
			std::swap(head->line_number, head->next->line_number);
			ListNode* nextToNeighbor{ head->next->next };
			delete(head->next);
			head->next = nextToNeighbor;
		}
		else {
			delete(head);
			head = nullptr;
		}

		return (head == nullptr) ? 1 : 2;
	}

	ListNode* current{ head };
	while (current->next != nullptr) {
		if (current->next->line_number == line_number) {
			ListNode* nextToNeighbor{ current->next->next };
			delete(current->next);
			current->next = nextToNeighbor;
			return 2;
		}
		else {
			current = current->next;
		}
	}
	return 0;
}

bool
isPresentInList(ListNode* head, size_t line_number) {
	while (head != nullptr) {
		if (head->line_number == line_number) {
			return true;
		}
		head = head->next;
	}
	return false;
}

void
deleteFullList(ListNode* head) {
	while (head != nullptr) {
		ListNode* currentNode{ head };
		head = head->next;
		delete(currentNode);
	}
}

void
deleteTreeHelper(Node* node) {
	if (isTNULL(node))
		return;

	deleteTreeHelper(node->left);
	deleteTreeHelper(node->right);

	delete(node->carplate);
	deleteFullList(node->head);
	delete(node);
}

void
deleteTree(RBTree* &tree) {
	if (tree != nullptr) {
		deleteTreeHelper(tree->root);
		delete(tree->TNULL);
		delete(tree);
		tree = nullptr;
	}
}

void
inorderTreeHelper(Node* node) {
	if (isTNULL(node)) 
		return;

	inorderTreeHelper(node->left);
	inorderTreeHelper(node->right);

	std::cout << node->carplate << ' ';
	std::cout << ((node->colour) ? "[RED]" : "[BLACK]") << std::endl;
	printList(node->head);
}

void
inorderTree(RBTree* tree) {
	if (tree != nullptr) {
		inorderTreeHelper(tree->root);	
	}
}

std::uint16_t
getNumberOfDescendants(Node* node) {
	return (static_cast<bool>(node->left) + static_cast<bool>(node->right));
}

void
drawTreeHelper(Node* root, size_t h) {
    if (!isTNULL(root)) {
        drawTreeHelper(root->right, h + 4);
        for (size_t i{ 1 }; i <= h; ++i) {
            std::cout << ' ';
        }
        std::cout << root->carplate << std::endl;
        drawTreeHelper(root->left, h + 4);
    }
}

void drawTree(RBTree* tree) {
	if (tree != nullptr) {
		std::cout << '\n';
		drawTreeHelper(tree->root, 0);
		std::cout << std::endl;
	}
}