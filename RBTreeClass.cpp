#include "RBTreeClass.h"
#include "helpFunctions.h"

RBTree::RBTree() {
	TNULL = new Node();
	TNULL->colour = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->parent = nullptr;
	TNULL->head = nullptr;
	TNULL->carplate = nullptr;
	root = TNULL;
}


void RBTree::rightRotate(Node* x) {
	Node* y{ x->left };
	x->left = y->right;

	if (y->right != TNULL) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		/*if x is in the right subtree*/
		this->root = y;
	}
	else if (x == x->parent->right) {
		/*if x is in the right subtree*/
		x->parent->right = y;
	}
	else { 
		/*if x is in the left subtree*/
		x->parent->left = y;
	}

	y->right = x;
	x->parent = y;
}

void RBTree::leftRotate(Node* x) {
	Node* y{ x->right };
	x->right = y->left;

	if (y->left != TNULL) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		/*x is a root node*/
		this->root = y;
	}
	else if (x == x->parent->left) {
		/*if x is in the right subtree*/
		x->parent->left = y;
	}
	else { 
		/*is x is in the left subtree*/
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void RBTree::insertValueFix(Node* node) {
	Node* uncle{ nullptr };
	while (node->parent->colour == RED) {
		/*
			a new node in the RIGHT subtree of it's grandfather...
		*/
		if (node->parent == node->parent->parent->right) {
			uncle = node->parent->parent->left;
			if (uncle->colour == RED) {
				uncle->colour = BLACK;
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED; 
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
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED;
				leftRotate(node->parent->parent);
			}
		}
		/*
			a new node in the LEFT subtree of it's grandfather...
		*/
		else {
			uncle = node->parent->parent->right;

			if (uncle->colour == RED) {
				uncle->colour = BLACK;
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED;
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
				node->parent->colour = BLACK;
				node->parent->parent->colour = RED;
				rightRotate(node->parent->parent);
			}
		}

		if (node == this->root) 
			break;
	}
	this->root->colour = BLACK;
}

void RBTree::push(ListNode* head, short int line_number) {
	while (head->next)
		head = head->next;
	head->next = new ListNode(line_number);
}


void RBTree::insertValue(std::string key, short int line_number) {

    Node* newNode{ new Node() };
    newNode->carplate = getCarplate(key);
    newNode->head = new ListNode(line_number);
    newNode->left = TNULL;
    newNode->right = TNULL;

    if (this->root == TNULL) {
    	this->root = newNode;
    	return;
    }

    bool nodeIsPlaced{ false };
    Node* current{ this->root };

    while (nodeIsPlaced != true) {
    	if (*newNode->carplate == *current->carplate) {
    		/*
			There may be cases when the new key is 
			already contained in the tree. Then the SEPARATE 
			CHAINING method comes in to handle collisions.
    		*/
    		delete(newNode->carplate);
    		delete(newNode);
    		push(current->head, line_number);
    		nodeIsPlaced = true;
    	}
    	else if (*newNode->carplate > *current->carplate) {
    		if (current->right != TNULL) {
    			current = current->right;
    		}
    		else {
    			current->right = newNode;
    			nodeIsPlaced = true;
    		}
    	}
    	else {
    		if (current->left != TNULL) {
    			current = current->left;
    		}
    		else {
    			current->left = newNode;
    			nodeIsPlaced = true;
    		}
    	}
    }
    newNode->parent = current;

    if (newNode->parent->parent == nullptr) {
    	return;
    }

	insertValueFix(newNode);
}

Node* RBTree::maximum(Node* x) const {
	if (x == nullptr || x == TNULL) 
		return x;

	while (x->right != TNULL)
		x = x->right;
	return x;
}

Node* RBTree::minimum(Node* x) const {
	if (x == nullptr || x == TNULL) 
		return x;

	while (x->left != TNULL)
		x = x->left;
	return x;
}

void RBTree::transplant(Node* x, Node* y) {
	if (x->parent == nullptr) {
    	/*node to delete is a root node*/
    	this->root = y;
  	}
	else if (x == x->parent->left) {
		/*node to delete is in left subtree of it's parent*/
		x->parent->left = y;
	} 
	else {
		/*node to delete is in right subtree of it's parent*/
		x->parent->right = y;
	}
	y->parent = x->parent;
}

void RBTree::deleteValueFix(Node* x) {
	Node* s{ nullptr };

	while (x != this->root && x->colour == BLACK) {
		if (x == x->parent->left) {
			s = x->parent->right;

			if (s->colour == RED) {
				s->colour = BLACK;
				x->parent->colour = RED;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->colour == BLACK && s->right->colour == BLACK) {
				s->colour = RED;
				x = x->parent;
			} 
			else {

				if (s->right->colour == BLACK) {
					s->left->colour = BLACK;
					s->colour = RED;
					rightRotate(s);
					s = x->parent->right;
				}

				s->colour = x->parent->colour;
				x->parent->colour = BLACK;
				s->right->colour = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		} 
		else {
			s = x->parent->left;

			if (s->colour == RED) {
				s->colour = BLACK;
				x->parent->colour = RED;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->colour == BLACK && s->right->colour == BLACK) {
				s->colour = RED;
				x = x->parent;
			} 
			else {

				if (s->left->colour == BLACK) {
					s->right->colour = BLACK;
					s->colour = RED;
					leftRotate(s);
					s = x->parent->left;
				}

				s->colour = x->parent->colour;
				x->parent->colour = BLACK;
				s->left->colour = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->colour = BLACK;
}

void RBTree::deleteValueHelper(Node* node, std::string key, short int line_number) {
	Node* z{ TNULL };
	Node* x{ nullptr };
	Node* y{ nullptr };

	struct Carplate* carplate{ getCarplate(key) };

	bool nodeIsFound{ false };
	while (node != TNULL && nodeIsFound == false) {
		if (*node->carplate == *carplate) {
			z = node;
			nodeIsFound = true;
		}
		else if (*node->carplate < *carplate) {
			node = node->right;
		} 
		else {
			node = node->left;
		}
	}

	if (z == TNULL) {
		//key is not present inside of the tree
		return;
	}

	if (isLastInList(z->head) == false) {
		/*
		if there are several references to the same key in one file, 
		then when deleting it is only necessary to remove information 
		about the appearance of this key in the transmitted line number
		*/
		deleteListNode(z->head, line_number);
		return;
	}

	if (isPresentInList(z->head, line_number) == false) {
		/*
		if such a key is found, but there is no such 
		key in the selected file line, the deletion will not occur
		*/
		return;
	}

	y = z;

	Colour_t y_original_colour{ y->colour };
	if (z->left == TNULL) {
		x = z->right;
		transplant(z, z->right);
	} 
	else if (z->right == TNULL) {
		x = z->left;
		transplant(z, z->left);
	} 
	else {
		y = minimum(z->right);
		y_original_colour = y->colour;
		x = y->right;

		if (y->parent == z) {
			x->parent = y;
		} 
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->colour = z->colour;
	}

	delete z;

	if (y_original_colour == BLACK) {
		deleteValueFix(x);
	}
}

void RBTree::deleteValue(std::string key, short int line_number) {
	deleteValueHelper(this->root, key, line_number);
}