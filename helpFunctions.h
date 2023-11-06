#ifndef HELP_FUNCTIONS
#define HELP_FUNCTIONS

#include "libraries.h"
#include "RBTreeClass.h"

Carplate* getCarplate(std::string key);

void printList(ListNode* head);
void deleteListNode(ListNode* head, short int line_number);

bool isvalid(std::string key);
bool isTNULL(Node* node);
bool isLastInList(ListNode* head);
bool isPresentInList(ListNode* head, short int line_number);

//tree memory dealloaction
void deleteTreeHelper(Node* node);
void deleteTree(RBTree* &tree);
void deleteFullList(ListNode* head);

#endif //HELP_FUNCTIONS