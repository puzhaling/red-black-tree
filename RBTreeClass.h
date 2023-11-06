#ifndef RBTREECLASS
#define RBTREECLASS

#include "libraries.h"
#include "RBTreeClass.h"

enum Colour_t {
	BLACK,
	RED,
};

struct ListNode {
	short int line_number;
	ListNode* next;

	ListNode(short int number) :
		line_number{ number }, next{ nullptr }
	{}
};

struct Carplate {
	std::string numbers;
	std::string letters;

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

struct Node {
	struct Carplate* carplate;
	struct ListNode* head;
	Node *parent, *left, *right;
	Colour_t colour;

	Node() {
		carplate = nullptr;
		head = nullptr;
		parent = left = right = nullptr;
		colour = RED;
	}
};

class RBTree {
public:
	Node *root, *TNULL;

	RBTree();
	void insertValue(std::string key, short int line_number);
	void deleteValue(std::string key, short int line_number);

private:
	void push(ListNode* head, short int line_number);
	void insertValueFix(Node* node);
	void leftRotate(Node* x);
	void rightRotate(Node* x);
	void transplant(Node* x, Node* y);
	void deleteValueHelper(Node* node, std::string key, short int line_number);
	void deleteValueFix(Node* x);

	Node* minimum(Node* x) const;
	Node* maximum(Node* x) const;
};

#endif //RBTREECLASS