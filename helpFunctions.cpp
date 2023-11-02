
#include "RBTreeClass.h"
#include <bits/stdc++.h>

Carplate*
getCarplate(const std::string& text) {
	return new Carplate{ text.substr(1, 3), text.substr(0, 1) + text.substr(4, 2) };
}

void
printList(ListNode* head) {
	while (head) {
		std::cout << head->line_number << ' ';
		head = head->next;
	}
	std::cout << '\n';
	return;

}

void
inorderHelper(Node* root) {
	if (!root) return;

	inorderHelper(root->left);

	std::cout << root->data << "  \n";
	printList(root->head);
	if (root->color == BLACK)
		std::cout << "BLACK\n";
	else std::cout << "RED\n";

	inorderHelper(root->right);

	return;
}

void
inorder(RBTree* tree) {
	if (tree == nullptr)
		return;
	inorderHelper(tree->root);
	std::cout << '\n';
	return;
}

bool
isLeaf(Node* root) {
	return (root->left == nullptr && root->right == nullptr);
}

bool
isLastInList(ListNode* head) {
	return head->next == nullptr;
}

void
narrowList(ListNode* head) {
	ListNode* current{ head };
	while (current->next->next)
		current = current->next;
	delete(current->next);
	current->next = nullptr;
	return;
}

void
deleteList(ListNode* &head) {
	ListNode* current{ nullptr };
	while (head != nullptr) {
		current = head;
		head = head->next;
		delete(current);
	}
	head = nullptr;
	return;
}

void
deleteTreeHelper(Node* &root) {
	if (root == nullptr) return;

	deleteTreeHelper(root->left);
	deleteTreeHelper(root->right);

	delete(root->data);
	deleteList(root->head);
	root->head = nullptr;
	delete(root);
	root = nullptr;

	return;
}

void
deleteTree(RBTree* &tree) {
	deleteTreeHelper(tree->root);
	tree = nullptr;
	return;
}

bool
isvalid(const std::string& key) {
	std::uint16_t length{ static_cast<std::uint16_t>(key.length()) };
	return (length == 6) ? (isalpha(key[0]) && isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) && isalpha(key[4]) && isalpha(key[5])) : false;
}
