#ifndef RBTREECLASS
#define RBTREECLASS

#include "libraries.h"

enum Color_t {
	RED, 	 /*0*/
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
	//void deleteNode(const std::string& str); /*delete tree node entirely with rebalancing the tree*/
	void deleteValue(const std::string& str); /*only remove information about in one line encounter*/
};

#endif
