#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

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


Carplate* getCarplate(const std::string& text) {
	return new Carplate{ text.substr(1, 3), text.substr(0, 1) + text.substr(4, 2) };
} 

void printList(ListNode* head) {
	while (head) {
		std::cout << head->line_number << ' ';
		head = head->next;
	}
	std::cout << '\n';
	return;
}

void
inorder(Node* root) {
	if (!root) return;

	inorder(root->left); //+
	std::cout << root->data << "  \n";
	inorder(root->right);
}

int
main() {
	return 0;
}