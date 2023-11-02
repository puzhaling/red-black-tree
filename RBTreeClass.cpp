
#include "libraries.h"
#include "RBTreeClass.h"
#include "helpFunctions.h"

RBTree::RBTree() :
	root{ nullptr }
{}

void
RBTree::push(ListNode* head, std::uint32_t line_number) {
	while (head->next != nullptr)
		head = head->next;
	head->next = new ListNode(line_number);
	return;
}

void
RBTree::deleteValue(const std::string& str) {
	if (this->root == nullptr)
		return;

	Carplate* data{ getCarplate(str) };

	if (*this->root->data == *data) {
		if (isLastInList(this->root->head)) {
			//deleteNode(root);
		}
		else {
			narrowList(this->root->head);
		}
		return;
	}

	Node* current{ this->root };
	while (current != nullptr) {
		if (*current->data == *data) {
			if (isLastInList(current->head)) {
				//deleteNode(current);
				return;
			}
			else {
				narrowList(current->head);
			}
			return;
		}
		else if (*current->data < *data) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return;
}

void
RBTree::rightRotate(Node* x) {
	Node* y{ x->left };
	x->left = y->right;
	if (y->right != nullptr)
		y->right->parent = x;

	y->parent = x->parent;
	/*x is a root node*/
	if (x->parent == nullptr)
		this->root = y;
	/*if x is in the right subtree*/
	else if (x->parent->right == x)
		x->parent->right = y;
	/*if x is in the left subtree*/
	else x->parent->left = y;

	y->right = x;
	x->parent = y;
	return;
}

void
RBTree::leftRotate(Node* x) {
    Node* y{ x->right };
    x->right = y->left;
    if (y->left != nullptr)
      y->left->parent = x;

    y->parent = x->parent;
    /*x is a root node*/
    if (x->parent == nullptr)
      this->root = y;
    /*if x is in the right subtree*/
    else if (x == x->parent->left)
      x->parent->left = y;
    /*is x is in the left subtree*/
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
    return;
}

void
RBTree::insertFix(Node* node) {
	Node* uncle{ nullptr };
	while (node->parent->color == RED) {
		/*
			a new node in the RIGHT subtree of it's grandfather...
		*/
		if (node->parent == node->parent->parent->right) {
			uncle = node->parent->parent->left;
			if (uncle->color == RED) {
				uncle->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				/*
					...and forms a triangle pattern. (RL rotation required)
				*/
				if (node == node->parent->left) {
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);
			}
		}
		/*
			a new node in the LEFT subtree of it's grandfather...
		*/
		else {
			uncle = node->parent->parent->right;
			if (uncle->color == RED) {
				uncle->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				/*
					...and forms a triangle pattern. (LR rotation required)
				*/
				if (node = node->parent->right) {
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
		}

		if (node == this->root)
			break;
	}
	this->root->color = BLACK;
	return;
}

void
RBTree::insert(const std::string& text, std::uint32_t line_number) {

	Node* newNode{ new Node{} };
	newNode->data = getCarplate(text);
	newNode->head = new ListNode(line_number);

	if (root == nullptr) {
		newNode->color = BLACK;
		this->root = newNode;
		return;
	}

	bool nodeIsPlaced{ false };
	Node* current{ root };

	while (nodeIsPlaced == false) {
		if (*current->data == *newNode->data) {
			delete(newNode);
			push(current->head, line_number);
			return;
		}
		else if (*newNode->data > *current->data) {
			if (current->right != nullptr) {
				Node* parent{ current };
				current = current->right;
				current->parent = parent;
			}
			else {
				current->right = newNode;
				newNode->parent = current;
				nodeIsPlaced = true;
			}
		}
		else if (*newNode->data < *current->data) {
			if (current->left != nullptr) {
				Node* parent{ current };
				current = current->left;
				current->parent = parent;
			}
			else {
				current->left = newNode;
				newNode->parent = current;
				nodeIsPlaced = true;
			}
		}
	}

	insertFix(newNode);
	return;
}
