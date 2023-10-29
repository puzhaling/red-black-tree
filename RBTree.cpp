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

	inorder(root->left);
	std::cout << root->data << "  \n";
	printList(root->head);
	inorder(root->right);

	return;
}

void
push(ListNode* head, std::uint32_t line_number) {
	while (head->next != nullptr)
		head = head->next;
	head->next = new ListNode(line_number);
	return;
}

void
insert(Node* &root, const std::string& text, std::uint32_t line_number) {

	Node* newNode{ new Node{} };
	newNode->data = getCarplate(text);
	newNode->head = new ListNode(line_number);

	if (!root) {
		root = newNode;
		return;
	}


	bool nodeIsPlaced{ false };
	Node* current{ root };

	while (nodeIsPlaced == false) {
		if (*current->data == *newNode->data) {
			delete(newNode);
			push(current->head, line_number);
			nodeIsPlaced = true;
		}
		else if (*newNode->data > *current->data) {
			if (current->right != nullptr) {
				current = current->right;
			}
			else {
				current->right = newNode;
				nodeIsPlaced = true;
			}
		}
		else if (*newNode->data < *current->data) {
			if (current->left != nullptr) {
				current = current->left;
			}
			else {
				current->left = newNode;
				nodeIsPlaced = true;
			}
		}
	}
}

int
main() {
	std::string file_name{ "input.txt" };
	std::fstream fs(file_name);

	Node* root{ nullptr };
	std::uint32_t line_number{ 1 };

	std::string text;
	while (fs >> text) 
		insert(root, text, line_number++);


	inorder(root);

	fs.close();
	return 0;
}