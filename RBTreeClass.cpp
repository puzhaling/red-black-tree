#include "RBTreeClass.h"
#include "helpFunctions.h"

RBTree::RBTree() {
	TNULL           = new Node();
	TNULL->colour   = BLACK;
	root            = TNULL;
}

ListNode::ListNode(size_t number) :
	line_number{ number }, next{ nullptr }
{}

Node::Node() {
	carplate = nullptr;
	parent = left = right = nullptr;
	colour = RED;
	head   = nullptr;
}

std::ostream&
operator<<(std::ostream& out, const Carplate* a) {
	return out << '[' << a->leftChar << ',' << a->numbers << ',' << a->rightString << ']';
}

bool
operator==(const Carplate& a, const Carplate& b) {
	return (a.leftChar == b.leftChar && a.numbers == b.numbers && a.rightString == b.rightString);
}

bool
operator<(const Carplate& a, const Carplate& b) {
	if (a.numbers != b.numbers) {
		return a.numbers < b.numbers;
	}
	else if (a.leftChar != b.leftChar) {
		return a.leftChar < b.leftChar;
	}
	else if (a.rightString != b.rightString) {
		return a.rightString < b.rightString;
	}
	else {
		return a == b;
	}
}

bool
operator>(const Carplate& a, const Carplate& b) {
	return !(a < b) && !(a == b);
}

void
RBTree::rightRotate(Node* x) {
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

void 
RBTree::leftRotate(Node* x) {
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

void
RBTree::insertValueFix(Node* node) {
    Node* uncle{ nullptr };
    while (node->parent->colour == RED) {
    	/*
			a new node in the LEFT subtree of it's grandfather...
		*/
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;

            if (uncle->colour == RED) {
                node->parent->colour = BLACK;
                uncle->colour = BLACK;
                node->parent->parent->colour = RED;
                node = node->parent->parent;
            }
            else {
            	/*
					...and forms a triangle pattern. (LR rotation required)
				*/
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }

                node->parent->colour = BLACK;
                node->parent->parent->colour = RED;
                rightRotate(node->parent->parent);
            }
        }
        /*
			a new node in the RIGHT subtree of it's grandfather...
		*/
        else {
            uncle = node->parent->parent->left;

            if (uncle->colour == RED) {
                node->parent->colour = BLACK;
                uncle->colour = BLACK;
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

        if (node == this->root) break;
 	}
 	this->root->colour = BLACK;
}

void 
RBTree::push(ListNode* head, size_t line_number) {
	while (head->next)
		head = head->next;

	head->next = getListNode(line_number);
	head->next->next = nullptr;
}

void 
RBTree::insertValue(const std::string& key, size_t line_number) {

    Node* newNode{ new Node() };

    newNode->carplate   = getCarplate(key);
    newNode->head 	    = getListNode(line_number);
    newNode->head->next = nullptr;
    newNode->left       = this->TNULL;
    newNode->right      = this->TNULL;
    newNode->colour     = RED;

    if (this->root == this->TNULL) {
    	newNode->colour = BLACK;
    	this->root = newNode;
    	return;
    }

    bool nodeIsPlaced{ false };
    Node* current{ this->root };

    while (!nodeIsPlaced) {
    	if (*newNode->carplate == *current->carplate) {
    		/*
			There may be cases when the new key is 
			already contained in the tree. Then the SEPARATE 
			CHAINING method comes in to handle collisions.
    		*/
    		delete(newNode->carplate);
    		delete(newNode->head);
    		delete(newNode);
    		newNode = nullptr;

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

    // if new key is unique
    if (newNode != nullptr) {
    	newNode->parent = current;

    	// if we have an opportunity to access newNode's uncle, function call takes place
    	if (newNode->parent->parent != nullptr) {
    		insertValueFix(newNode);
    	}
    }
}

Node* 
RBTree::maximum(Node* x) const {
	while (x->right != TNULL) {
		x = x->right;
	}
	return x;
}

Node* 
RBTree::minimum(Node* x) const {
	while (x->left != TNULL) {
		x = x->left;
	}
	return x;
}

/*replacing nodes with solving parent connections*/
void 
RBTree::transplant(Node* x, Node* y) {
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

Node*
RBTree::findNode(const std::string& key) const {
	if (this->root == TNULL) 
		return TNULL;

	Carplate* carplate{ getCarplate(key) };

	Node* node{ this->root };
	while (node != TNULL) {
		if (*node->carplate == *carplate) {
			break;
		}
		else if (*node->carplate < *carplate) {
			node = node->right;
		} 
		else {
			node = node->left;
		}
	}
	delete(carplate);
	return node;
}

void 
RBTree::deleteValueFix(Node* x) {
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

			if (s->right->colour == BLACK) {
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

void 
RBTree::deleteValueHelper(Node* node, const std::string& key, size_t line_number) {

	Node* foundNode{ findNode(key) };

	if (foundNode == TNULL)
		return; //key is not present inside of the tree

	/*
	RETURN VALUES:
		0: node with provided line_number 
		 wasn't found => everything left the same
		1: head was deleted;
		2: other list node was deleted;
	*/
	std::uint16_t resultOfDeletion{ deleteListNode(foundNode->head, line_number) }; 
	switch (resultOfDeletion) {
		case 0: 
		case 2:	
			return;
		case 1: 
			break;
	}

	Node* x{  nullptr  };
	Node* y{ foundNode };
	Node* z{ foundNode };

	Colour_t y_original_colour{ y->colour };
	/*
	first 2 conditional statements 
	works simultaneously for 0/1 descendants cases
	*/
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

	delete(z->carplate);
	delete z;
	z = nullptr;

	if (y_original_colour == BLACK) {
		/*
		if black height is violated, then the tree need reballancing
		(X) is a node, which we use as a replacement node for deleted one
		*/
		deleteValueFix(x);
	}
}

void 
RBTree::deleteValue(const std::string& key, size_t line_number) {
	deleteValueHelper(this->root, key, line_number);
}