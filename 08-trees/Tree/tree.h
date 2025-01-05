#pragma once

// Structure for node values.
typedef int NodeValue;

// Node structure.
typedef struct Node Node;

// Creates a node and fills it with values from the user.
Node* createNode(NodeValue value, bool* errorCode);

// Adds a left son to the node (that is, a smaller value).
// If the left son was earlier, the error code will be equal to 1.
void addLeftChild(Node* node, Node* child, bool* errorCode);

// Adds a right son to the node (that is, a larger value).
// If the right son was earlier, the error code will be equal to 1.
void addRightChild(Node* node, Node* child, bool* errorCode);

// Returns a pointer to the left child of the node.
Node* getLeftChild(Node* node, bool* errorCode);

// Returns a pointer to the right child of the node.
Node* getRightChild(Node* node, bool* errorCode);

// Returns the value of the node.
NodeValue getValue(Node* node, bool* errorCode);

// Sets the value of the node.
void setValue(Node* node, NodeValue value, bool* errorCode);

// Deletes a subtree.
void disposeNode(Node** node);

// Copies the node, creating a new memory location.
Node* copyNode(const Node* source, bool* errorCode);