#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"

typedef struct NodeValue {
    const char* key;
    const char* value;
} NodeValue;

typedef struct Node {
    NodeValue value;
    Node* left;
    Node* right;
    short balance;
} Node;

Node* createTree(const char* key, const char* value, bool* errorCode) {
    Node* root = calloc(1, sizeof(Node));
    if (root == NULL) {
        *errorCode = true;
        return NULL;
    }
    const char* copyOfKey = strdup(key);
    if (copyOfKey == NULL) {
        free(root);
        *errorCode = true;
        return NULL;
    }
    root->value.key = copyOfKey;
    const char* copyOfValue = strdup(value);
    if (copyOfValue == NULL) {
        free(root->value.key);
        free(root);
        *errorCode = true;
        return NULL;
    }
    root->value.value = copyOfValue;
    return root;
}

void deleteTree(Node** root) {
    if (*root == NULL) {
        return;
    }
    deleteTree((&(*root)->left));
    deleteTree((&(*root)->right));

    if ((*root)->value.key != NULL) {
        free((*root)->value.key);
    }
    if ((*root)->value.value != NULL) {
        free((*root)->value.value);
    }

    free(*root);
    *root = NULL;
}

Node* getLeftChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->left;
}

Node* getRightChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->right;
}

NodeValue getValue(Node* node, bool* errorCode) {
    if (node == NULL) {
        NodeValue incorrectNodeValues = { .key = -1, .value = NULL };
        *errorCode = true;
        return incorrectNodeValues;
    }
    return node->value;
}

const char* searchByKey(Node* node, const char* key) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(node->value.key, key) == 0) {
        return node->value.value;
    }

    if ((node->left == NULL && strcmp(node->value.key, key) > 0) || (node->right == NULL && strcmp(node->value.key, key) < 0)) {
        return NULL;
    }

    if (strcmp(node->value.key, key) < 0) {
        return searchByKey(node->right, key);
    }
    return searchByKey(node->left, key);
}

Node* rotateLeft(Node* a) {
    Node* b = a->right;
    Node* c = b->left;
    b->left = a;
    a->right = c;
    return b;
}

Node* rotateRight(Node* a) {
    Node* b = a->left;
    Node* c = b->right;
    b->right = a;
    a->left = c;
    return b;
}

Node* bigRotateLeft(Node* a) {
    a->right = rotateRight(a->right);
    return rotateLeft(a);
}

Node* bigRotateRight(Node* a) {
    a->left = rotateLeft(a->left);
    return rotateRight(a);
}

Node* balance(Node* node) {
    if (node->balance == 2) {
        if (node->right->balance >= 0) {
            if (node->right->balance == 1) {
                node->balance = 0;
                node->right->balance = 0;
            } else {
                node->balance = 1;
                node->right->balance = -1;
            }
            return rotateLeft(node);
        }

        if (node->right->balance == -1 && node->right->left->balance == -1) {
            node->balance = 0;
            node->right->balance = 1;
            node->right->left->balance = 0;
        }
        if (node->right->balance == -1 && node->right->left->balance == 1) {
            node->balance = -1;
            node->right->balance = 0;
            node->right->left->balance = 0;
        }
        if (node->right->balance == -1 && node->right->left->balance == 0) {
            node->balance = 0;
            node->right->balance = 0;
            node->right->left->balance = 0;
        }
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->left->balance <= 0) {
            if (node->left->balance == -1) {
                node->balance = 0;
                node->left->balance = 0;
            } else {
                node->balance = -1;
                node->left->balance = 1;
            }
            return rotateRight(node);
        }

        if (node->left->balance == 1 && node->left->right->balance == 1) {
            node->balance = 0;
            node->left->balance = -1;
            node->left->right->balance = 0;
        }
        if (node->left->balance == 1 && node->left->right->balance == -1) {
            node->balance = 1;
            node->left->balance = 0;
            node->left->right->balance = 0;
        }
        if (node->left->balance == 1 && node->left->right->balance == 0) {
            node->balance = 0;
            node->left->balance = 0;
            node->left->right->balance = 0;
        }
        return bigRotateRight(node);
    }
    return node;
}

Node* addNode(Node* node, const char* key, const char* value, bool* isHeightChanged, bool* errorCode) {
    if (strcmp(key, node->value.key) == 0) {
        free(node->value.value);
        const char* copyOfValue = strdup(value);
        if (copyOfValue == NULL) {
            *errorCode = true;
            return NULL;
        }
        node->value.value = copyOfValue;
        *isHeightChanged = false;
        return node;
    }

    if (node->left == NULL && strcmp(key, node->value.key) < 0) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            *isHeightChanged = false;
            return node;
        }
        node->left = newNode;

        --node->balance;
        node = balance(node);
        if (node->balance == 0) {
            *isHeightChanged = false;
            return node;
        }
        *isHeightChanged = true;
        return node;
    }
    else if (node->right == NULL && strcmp(key, node->value.key) > 0) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            *isHeightChanged = false;
            return node;
        }
        node->right = newNode;

        ++node->balance;
        node = balance(node);
        if (node->balance == 0) {
            *isHeightChanged = false;
            return node;
        }
        *isHeightChanged = true;
        return node;
    }

    if (strcmp(key, node->value.key) > 0) {
        addNode(node->right, key, value, isHeightChanged, errorCode);
        if (*isHeightChanged) {
            ++node->balance;
            node = balance(node);
            if (node->balance == 0) {
                *isHeightChanged = false;
                return node;
            }
            else {
                *isHeightChanged = true;
                return node;
            }
        }
        *isHeightChanged = false;
        return node;
    }
    if (strcmp(key, node->value.key) < 0) {
        addNode(node->left, key, value, isHeightChanged, errorCode);
        if (*isHeightChanged) {
            --node->balance;
            node = balance(node);
            if (node->balance == 0) {
                *isHeightChanged = false;
                return node;
            }
            *isHeightChanged = true;
            return node;
        }
        *isHeightChanged = false;
        return node;
    }
}

Node* copyNode(const Node* source, bool* errorCode) {
    if (source == NULL) {
        *errorCode = true;
        return NULL;
    }

    Node* destination = createTree(source->value.key, source->value.value, errorCode);
    if (*errorCode) {
        return NULL;
    }

    return destination;
}

Node* deleteNode(Node* node, const char* key, bool* isHeightChanged, bool* errorCode) {
    if (*errorCode) {
        return node;
    } 

    if (strcmp(node->value.key, key) == 0) {
        if (node->left == NULL && node->right == NULL) {
            *isHeightChanged = true;
            return NULL;
        }
        if (node->left != NULL && node->right == NULL) {
            *isHeightChanged = true;
            return node->left;
        }
        if (node->left == NULL && node->right != NULL) {
            *isHeightChanged = true;
            return node->right;
        }
        if (node->left != NULL && node->right != NULL) {
            Node* replacementNode = deleteNode(node, node->right->value.key, isHeightChanged, errorCode);
            Node* saveNode = copyNode(node, errorCode);
            node->value.key = replacementNode->value.key;
            node->value = replacementNode->value;
            free(replacementNode);
            return saveNode;
        }
    }

    if (node->left == NULL && node->right == NULL && strcmp(node->value.key, key) != 0) {
        return node;
    }

    Node* returnedNode = NULL;
    if (strcmp(node->value.key, key) < 0) {
        returnedNode = deleteNode(node->right, key, isHeightChanged, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = NULL;
            if (*isHeightChanged) {
                --node->balance;
                node = balance(node);
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }
        else if (returnedNode == node->right->left || returnedNode == node->right->right) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = returnedNode;
            if (*isHeightChanged) {
                --node->balance;
                node = balance(node);
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }

        if (*isHeightChanged) {
            --node->balance;
            node = balance(node);
            if (abs(node->balance) >= 1) {
                *isHeightChanged = false;
            }
        }
        return returnedNode;
    }
    if (strcmp(node->value.key, key) > 0) {
        returnedNode = deleteNode(node->left, key, isHeightChanged, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = NULL;
            if (*isHeightChanged) {
                ++node->balance;
                node = balance(node);
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }
        else if (returnedNode == node->left->left || returnedNode == node->left->right) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = returnedNode;
            if (*isHeightChanged) {
                ++node->balance;
                node = balance(node);
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }

        if (*isHeightChanged) {
            ++node->balance;
            node = balance(node);
            if (abs(node->balance) >= 1) {
                *isHeightChanged = false;
            }
        }
        return returnedNode;
    }
    if (returnedNode != NULL) {
        free(returnedNode);
    }
    return node;
}