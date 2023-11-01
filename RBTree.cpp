
#include <bits/stdc++.h>

enum Color_t { 
	RED, 	   /*0*/
	BLACK,   /*1*/
};

/*list node description*/
struct ListNode {
	std::uint32_t line_number{};
	ListNode* next{ nullptr };

	ListNode(std::uint32_t number, ListNode* nextNode = nullptr) : 
		line_number{ number }, next{ nextNode }
	{}
};

struct Carplate {
	std::string numbers{};
	std::string letters{};

	friend std::ostream& operator<<(std::ostream& out, const Carplate* a) {
		return out << '[' << a->numbers << ',' << a->letters << ']';
	}

	friend bool operator==(const Carplate& a, const Carplate& b) {
		return (a.numbers == b.numbers && a.letters == b.letters);
	}
	friend bool operator<(const Carplate& a, const Carplate& b) {
		return (a.numbers == b.numbers) ? a.letters < b.letters : a.numbers < b.numbers;
	}
	friend bool operator>(const Carplate& a, const Carplate& b) {
		return !(a < b);
	}
};   

/*red-black tree node description*/
struct Node {
	Node* parent{ nullptr };
	Node* left{ nullptr };
	Node* right{ nullptr };

	Color_t color{ RED };
	Carplate* data{};

	ListNode* head{ nullptr };
};

class RBTree {
public:
	Node* root;

	RBTree();

	void push(ListNode* head, std::uint32_t line_number);
	void rightRotate(Node* x);
	void leftRotate(Node* x);
	void insertFix(Node* node);
	void insert(const std::string& text, std::uint32_t line_number);
	void deleteNode(const std::string& str); /*delete tree node entirely with rebalancing the tree*/
	void deleteValue(const std::string& str); /*only remove information about in one line encounter*/
};

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