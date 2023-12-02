#ifndef RBTREECLASS
#define RBTREECLASS

#include "libraries.h"
#include "RBTreeClass.h"

enum Colour_t {
	BLACK,
	RED,
};

struct ListNode {
	size_t line_number{};
	ListNode* next{};

	ListNode(size_t number);
};

struct Carplate {
	char  		leftChar{};
	short 		numbers{};
	std::string rightString{};
};

std::ostream& operator<< (std::ostream& out, const Carplate* a);
bool 		  operator== (const Carplate& a, const Carplate& b);
bool          operator<  (const Carplate& a, const Carplate& b);
bool          operator>  (const Carplate& a, const Carplate& b);

struct Node {
	Carplate* carplate{};
	ListNode* head{};

	Node* parent{};
	Node* left{};
	Node* right{};

	Colour_t colour{};

	Node();
};

class RBTree {
public:
	Node* root{};
	Node* TNULL{};

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