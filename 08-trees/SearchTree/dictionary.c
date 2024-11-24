#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../Tree/tree.h"

void addToTheDictionary(Node* node, const int key, const char* value, bool* errorCode) {
    if (getValue(node, errorCode).key == key) {
        free(getValue(node, errorCode).value);
        setValue(node, createNodeValue(key, value), errorCode);
        return;
    }

    if (getLeftChild(node, errorCode) == NULL && getValue(node, errorCode).key > key) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(createNodeValue(key, value), errorCode);
        if (*errorCode) {
            return;
        }
        addLeftChild(node, newNode, errorCode);
        return;
    }
    else if (getRightChild(node, errorCode) == NULL && getValue(node, errorCode).key < key) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(createNodeValue(key, value), errorCode);
        if (*errorCode) {
            return;
        }
        addRightChild(node, newNode, errorCode);
        return;
    }

    if (getValue(node, errorCode).key < key) {
        addToTheDictionary(getRightChild(node, errorCode), key, value, errorCode);
    }
    if (getValue(node, errorCode).key > key) {
        addToTheDictionary(getLeftChild(node, errorCode), key, value, errorCode);
    }
}

Node* nodeSearch(Node* node, const int key, bool* errorCode) {
    Node* theFoundNode = NULL;

    if (*errorCode) {
        return NULL;
    }

    if (getValue(node, errorCode).key == key) {
        return node;
    }

    if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL && getValue(node, errorCode).key != key) {
        return NULL;
    }

    if (getRightChild(node, errorCode) == NULL) {
        theFoundNode = nodeSearch(getLeftChild(node, errorCode), key, errorCode);
    }
    else if (getLeftChild(node, errorCode) == NULL) {
        theFoundNode = nodeSearch(getRightChild(node, errorCode), key, errorCode);
    }
    else if (getValue(node, errorCode).key < key) {
        theFoundNode = nodeSearch(getRightChild(node, errorCode), key, errorCode);
    }
    else if (getValue(node, errorCode).key > key) {
        theFoundNode = nodeSearch(getLeftChild(node, errorCode), key, errorCode);
    }
    return theFoundNode;
}

char* findValueByTheKey(Node* node, const int key, bool* errorCode) {
    Node* resultNodeSearch = nodeSearch(node, key, errorCode);
    if (resultNodeSearch == NULL) {
        return NULL;
    }
    char* theFoundString = getValue(resultNodeSearch, errorCode).value;
    if (*errorCode) {
        return NULL;
    }

    return theFoundString;
}

void deleteTheNode(Node* theNodeBeingDeleted, const int key, bool* errorCode) {

}

Node* deleteByKey(Node* node, const int key, bool* errorCode) {
    if (*errorCode) {
        return node;
    }

    if (getValue(node, errorCode).key == key) {
        if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL) {
            return NULL;
        }
        if (getLeftChild(node, errorCode) != NULL && getRightChild(node, errorCode) == NULL) {
            return getLeftChild(node, errorCode);
        }
        if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) != NULL) {
            return getRightChild(node, errorCode);
        }
        if (getLeftChild(node, errorCode) != NULL && getRightChild(node, errorCode) != NULL) {
            int absoluteDifferenceBetweenTheParentAndTheLeftSon = abs(abs(getValue(getLeftChild(node, errorCode), errorCode).key) - abs(getValue(node, errorCode).key));
            int absoluteDifferenceBetweenTheParentAndTheRightSon = abs(abs(getValue(getRightChild(node, errorCode), errorCode).key) - abs(getValue(node, errorCode).key));
            bool theRightSonIsCloserToTheParent = absoluteDifferenceBetweenTheParentAndTheLeftSon > absoluteDifferenceBetweenTheParentAndTheRightSon;
            if (theRightSonIsCloserToTheParent) {
                Node* replacementNode = deleteByKey(node, getValue(getRightChild(node, errorCode), errorCode).key, errorCode);
                Node* saveNode = copyNode(node, errorCode);
                NodeValue replacementNodeValue = getValue(replacementNode, errorCode);
                setValue(node, replacementNodeValue, errorCode);
                return saveNode;
            } else {
                Node* replacementNode = deleteByKey(node, getValue(getLeftChild(node, errorCode), errorCode).key, errorCode);
                Node* saveNode = copyNode(node, errorCode);
                NodeValue replacementNodeValue = getValue(replacementNode, errorCode);
                setValue(node, replacementNodeValue, errorCode);
                return saveNode;
            }
        }
    }

    if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL && getValue(node, errorCode).key != key) {
        return node;
    }

    if (getValue(node, errorCode).key < key) {
        Node* theReturnedNode = deleteByKey(getRightChild(node, errorCode), key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = copyNode(getRightChild(node, errorCode), errorCode);
            addRightChild(node, NULL, errorCode);
            return saveDeletedNode;
        }
        else if (theReturnedNode == getLeftChild(getRightChild(node, errorCode), errorCode) || theReturnedNode == getRightChild(getRightChild(node, errorCode), errorCode)) {
            Node* saveTheReturnedNode = copyNode(theReturnedNode, errorCode);
            Node* saveDeletedNode = copyNode(getRightChild(node, errorCode), errorCode);
            addRightChild(node, NULL, errorCode);
            addRightChild(node, saveTheReturnedNode, errorCode);
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
    if (getValue(node, errorCode).key > key) {
        Node* theReturnedNode = deleteByKey(getLeftChild(node, errorCode), key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = copyNode(getLeftChild(node, errorCode), errorCode);
            addLeftChild(node, NULL, errorCode);
            return saveDeletedNode;
        }
        else if (theReturnedNode == getLeftChild(getLeftChild(node, errorCode), errorCode) || theReturnedNode == getRightChild(getLeftChild(node, errorCode), errorCode)) {
            Node* saveTheReturnedNode = copyNode(theReturnedNode, errorCode);
            Node* saveDeletedNode = copyNode(getLeftChild(node, errorCode), errorCode);
            addLeftChild(node, NULL, errorCode);
            addLeftChild(node, saveTheReturnedNode, errorCode);
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
}