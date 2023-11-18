#ifndef HELP_FUNCTIONS
#define HELP_FUNCTIONS

#include "libraries.h"
#include "RBTreeClass.h"

Carplate* getCarplate  (const std::string& key);
ListNode* getListNode  (size_t line_number);
size_t    getListLength(ListNode* head);

//write the keys to a file
void writeDownInfo(std::ofstream& out, Node* node);

void printList        (ListNode* head);
void inorderTreeHelper(Node* node);
void inorderTree      (RBTree* tree);

bool isvalid        (std::string_view key);
bool isTNULL        (Node* node);
bool isLastInList   (ListNode* head);
bool isPresentInList(ListNode* head, size_t line_number);

//tree memory deallocation
void deleteTreeHelper(Node* node);
void deleteTree      (RBTree* &tree);
void deleteFullList  (ListNode* head);

std::uint16_t deleteListNode        (ListNode* head, size_t line_number);
std::uint16_t getNumberOfDescendants(Node* node);

//procedures to draw a tree lied on it's left side
void drawTreeHelper(Node* root, size_t h);
void drawTree      (RBTree* tree);

#endif //HELP_FUNCTIONS