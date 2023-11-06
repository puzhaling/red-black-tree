#include "libraries.h"
#include "RBTreeClass.h"

bool isvalid(std::string key) {
	short int length{ static_cast<short int>(key.length()) };
	return (length == 6) ? (isalpha(key[0]) && isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) && isalpha(key[4]) && isalpha(key[5])) : false;
}

Carplate* getCarplate(std::string key) {
	return new Carplate{ key.substr(1, 3), key.substr(0, 1) + key.substr(4, 2) };
}

void printList(ListNode* head) {
	while (head) {
		std::cout << head->line_number << ' ';
		head = head->next;
	}
	std::cout << std::endl;
}

bool isTNULL(Node* node) {
	return (node->colour == BLACK && node->carplate == nullptr && node->head == nullptr && 
		node->left == nullptr && node->right == nullptr && node->parent == nullptr);
}

bool isLastInList(ListNode* head) {
	return (head->next == nullptr);
}

void deleteListNode(ListNode* head, short int line_number) {
	if (line_number == head->line_number) {
		/*
		since we cannot move the head due to the copy 
		of the pointer, if it is necessary to delete 
		the head, we SWAP the values of the head and the head's neighbor and delete the neighbor
		*/
		std::swap(head->line_number, head->next->line_number);
		ListNode* nextToNeighbor{ head->next->next };
		delete(head->next);
		head->next = nextToNeighbor;
		return;
	}

	ListNode* current{ head };
	while (current->next != nullptr) {
		if (current->next->line_number == line_number) {
			ListNode* nextToNeighbor{ current->next->next };
			delete(current->next);
			current->next = nextToNeighbor;
		}
		else {
			current = current->next;
		}
	}
}

bool isPresentInList(ListNode* head, short int line_number) {
	while (head != nullptr) {
		if (head->line_number == line_number) {
			return true;
		}
		head = head->next;
	}
	return false;
}

// void deleteFullList(ListNode* head) {
// 	if (head != nullptr) {
// 		ListNode* prev{ nullptr };
// 		std::cout << "deleting list....";
// 		while (head != nullptr) {
// 			prev = head;
// 			head = head->next;
// 			delete(prev);
// 		}
// 		delete(prev);
// 		std::cout << "deletion was successfully done.\n";
// 	}
// }

// void deleteTreeHelper(Node* node) {
// 	if (node == nullptr) {
// 		return;
// 	}

// 	deleteTreeHelper(node->left);
// 	deleteTreeHelper(node->right);

// 	if (isTNULL(node) == false) {
// 		deleteFullList(node->head);
// 		delete(node->carplate);
// 	}
// 	delete(node);
// }

// void deleteTree(RBTree* &tree) {
// 	if (tree != nullptr) {
// 		deleteTreeHelper(tree->root);
// 		delete(tree);
// 		tree = nullptr;
// 	}
// }
