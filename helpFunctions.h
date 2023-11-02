#ifndef HELP_FUNCTIONS
#define HELP_FUNCTIONS

#include "libraries.h"
#include "RBTreeClass.h"

Carplate*
getCarplate(const std::string& text);

void
printList(ListNode* head);

void
inorderHelper(Node* root);

void
inorder(RBTree* tree);

bool
isLeaf(Node* root);

bool
isLastInList(ListNode* head);

void
narrowList(ListNode* head);

void
deleteList(ListNode* &head);

void
deleteTreeHelper(Node* &root);

void
deleteTree(RBTree* &tree);

bool
isvalid(const std::string& key);

#endif