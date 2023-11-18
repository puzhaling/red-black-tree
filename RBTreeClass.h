#ifndef RBTREECLASS
#define RBTREECLASS

#include "libraries.h"
#include "RBTreeClass.h"

enum Colour_t {
	BLACK,
	RED,
};

struct ListNode {
	size_t line_number;
	ListNode* next;

	ListNode(size_t number) :
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
	Carplate* carplate;
	ListNode* head;

	Node* parent;
	Node* left;
	Node* right;

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
	Node* root;
	Node* TNULL;

	RBTree();
	void  insertValue(const std::string& key, size_t line_number);
	void  deleteValue(const std::string& key, size_t line_number);
	Node* findNode   (const std::string& key) const;

private:
	void push          	  (ListNode* head, size_t line_number);
	void insertValueFix	  (Node* node);
	void leftRotate    	  (Node* x);
	void rightRotate      (Node* x);

	/*replacing nodes with solving parent connections*/
	void transplant       (Node* x, Node* y);
	
	void deleteValueHelper(Node* node, const std::string& key, size_t line_number);
	void deleteValueFix   (Node* x);

	Node* minimum(Node* x) const;
	Node* maximum(Node* x) const;
};

#endif //RBTREECLASS