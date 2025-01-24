#ifndef LBST_H
#define LBST_H

#include <iostream>
using namespace std;

template <class T>
class TreeNode {
public:
    TreeNode(T k);
    TreeNode();
    virtual ~TreeNode();

    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent; // Add parent pointer
    int leftDepth;
    int rightDepth;
};

template <class T>
TreeNode<T>::TreeNode(T k) {
    left = NULL;
    right = NULL;
    parent = NULL; // Initialize parent pointer
    key = k;
    leftDepth = 0;
    rightDepth = 0;
}
template <class T>
TreeNode<T>::TreeNode() {
    left = NULL;
    right = NULL;
    parent = NULL; // Initialize parent pointer
    key = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

template <class T>
TreeNode<T>::~TreeNode() {
    left = NULL;
    right = NULL;
    parent = NULL;
}

template <class T>
class lbst {
public:
    lbst();
    virtual ~lbst();
    void insert(T value);
    bool deleteNode(T k);
    void rebalance();

    bool isEmpty();

    T* getMin();
    T* getMax();
    bool contains(T value);

    void printTree(); //print tree
    void recPrint(TreeNode<T> *node);

    int size(); // size method
    TreeNode<T>* get(T value); //  get method

private:
    void buildFromSortedArray(T* arr, int start, int end);
    void storeInOrder(TreeNode<T>* node, T* arr, int& index);
    TreeNode<T>* getSuccessor(TreeNode<T> *d);
    void updateDepths(TreeNode<T>* node);
    TreeNode<T> *root;
    int treeSize; // Add size member
};

template <class T>
lbst<T>::lbst() {
    root = NULL;
    treeSize = 0; // Initialize size
}

template <class T>
lbst<T>::~lbst() {}

template <class T>
void lbst<T>::recPrint(TreeNode<T> *node) {
    if (node == NULL)
        return;

    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}

template <class T>
void lbst<T>::printTree() {
    recPrint(root);
}

template <class T>
bool lbst<T>::isEmpty() {
    return (root == NULL);
}

template <class T>
TreeNode<T>* lbst<T>::get(T value) {
    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;

    while (current != NULL && current->key != value) {
        if (value < current->key)
            current = current->left;
        else   
            current = current->right;
    }
    return current;
}


template <class T>
T* lbst<T>::getMin() {
    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return &(current->key);
}

template <class T>
T* lbst<T>::getMax() {
    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return &(current->key);
}

template <class T>
bool lbst<T>::contains(T value) {
    if (isEmpty())
        return false;

    TreeNode<T> *current = root;

    while (current->key != value) {
        if (value < current->key)
            current = current->left;
        else
            current = current->right;

        if (current == NULL)
            return false;
    }
    return true;
}

template <class T>
void lbst<T>::insert(T value) {
    TreeNode<T> *node = new TreeNode<T>(value);
    if (this->root == NULL) {
        this->root = node;
    } else {
        TreeNode<T> *current = this->root;
        TreeNode<T> *parent = NULL;
        while (true) {
            parent = current;
            if (value < current->key) {
                current = current->left;
                if (current == NULL) {
                    parent->left = node;
                    node->parent = parent; // Set parent pointer
                    break;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = node;
                    node->parent = parent; // Set parent pointer
                    break;
                }
            }
        }
    }

    treeSize++; // Increase size

    // Update depths from node to root
    updateDepths(node);

    // Rebalance the tree if necessary
    rebalance();
}

template <class T>
void lbst<T>::updateDepths(TreeNode<T>* node) {
    TreeNode<T> *current = node;
    while (current != NULL) {
        int leftDepth = (current->left != NULL) ? max(current->left->leftDepth, current->left->rightDepth) + 1 : 0;
        int rightDepth = (current->right != NULL) ? max(current->right->leftDepth, current->right->rightDepth) + 1 : 0;

        current->leftDepth = leftDepth;
        current->rightDepth = rightDepth;
        current = current->parent; // Update parent pointer logic
    }
}

template <class T>
bool lbst<T>::deleteNode(T k) {
    if (this->root == NULL) return false;

    TreeNode<T> *current = this->root;
    TreeNode<T> *parent = NULL;
    bool isLeftChild = true;

    // Find the node to delete
    while (current != NULL && current->key != k) {
        parent = current;
        if (k < current->key) {
            isLeftChild = true;
            current = current->left;
        } else {
            isLeftChild = false;
            current = current->right;
        }
    }

    if (current == NULL) return false; // Node not found

    // Case 1: Node with no child
    if (current->left == NULL && current->right == NULL) {
        if (current == this->root) this->root = NULL;
        else if (isLeftChild) parent->left = NULL;
        else parent->right = NULL;
    }

    // Case 2: Node with one child
    else if (current->right == NULL) { // Node has only left child
        if (current == this->root) this->root = current->left;
        else if (isLeftChild) parent->left = current->left;
        else parent->right = current->left;
        current->left->parent = parent; // Update parent pointer
    }
    else if (current->left == NULL) { // Node has only right child
        if (current == this->root) this->root = current->right;
        else if (isLeftChild) parent->left = current->right;
        else parent->right = current->right;
        current->right->parent = parent; // Update parent pointer
    }

    // Case 3: Node with two children
    else {
        TreeNode<T> *successor = getSuccessor(current);
        if (current == this->root) this->root = successor;
        else if (isLeftChild) parent->left = successor;
        else parent->right = successor;

        successor->left = current->left;
        successor->left->parent = successor; // Update parent pointer
    }

    // Update depths from parent to root
    updateDepths(parent);

    // Rebalance the tree if necessary
    rebalance();

    delete current;
    treeSize--; // Decrease size
    return true;
}

template <class T>
TreeNode<T>* lbst<T>::getSuccessor(TreeNode<T> *d) {
    TreeNode<T> *current = d->right;
    TreeNode<T> *sp = d; // successor's parent
    TreeNode<T> *successor = d;

    while (current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }

    if (successor != d->right) {
        sp->left = successor->right;
        if (successor->right != NULL) {
            successor->right->parent = sp; // Update parent pointer
        }
        successor->right = d->right;
        successor->right->parent = successor; // Update parent pointer
    }
    return successor;
}

template <class T>
void lbst<T>::rebalance() {
    if (this->root == NULL) return;

    // Check imbalance and rebuild if necessary
    if (abs(this->root->leftDepth - this->root->rightDepth) > 1.5 * min(this->root->leftDepth, this->root->rightDepth)) {
        T* temp = new T[this->size()]; // Assuming size() returns number of nodes
        int index = 0;
        storeInOrder(this->root, temp, index);
        this->root = NULL;
        treeSize = 0; // Reset size
        buildFromSortedArray(temp, 0, index - 1);
        delete[] temp;
    }
}

template <class T>
void lbst<T>::storeInOrder(TreeNode<T>* node, T* arr, int& index) {
    if (node == NULL) return;
    storeInOrder(node->left, arr, index);
    arr[index++] = node->key;
    storeInOrder(node->right, arr, index);
}

template <class T>
void lbst<T>::buildFromSortedArray(T* arr, int start, int end) {
    if (start > end) return;
    int mid = (start + end) / 2;
    this->insert(arr[mid]);
    buildFromSortedArray(arr, start, mid - 1);
    buildFromSortedArray(arr, mid + 1, end);
}

template <class T>
int lbst<T>::size() {
    return treeSize;
}

#endif
