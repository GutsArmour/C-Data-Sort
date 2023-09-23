 #include "dictionary.h"
#include <iostream>
#include <map>
#define COUNT 10

node::node(int key,std::string item) {
    this->key = key;
    this->item = item;
}

Dictionary::Dictionary(Dictionary & dictToCopy)
{
    root = nullptr;
    left = nullptr;
    right = nullptr;
    this->root = dictToCopy.root;

    deepCopyWorker(dictToCopy, root);
}

void Dictionary::insert(int key, std::string item) {
    /*node* current = root;
    node* newNode = new node(key, item);
    if (!current){
        root = newNode;
        return;
    }
    while (current) {
        if (current->key == key) {
            current = newNode;
            return;
        }
        if (current->key < key) {
            if (current->right == nullptr) break;
            current = current->right;

        }
        else {
            if (current->left == nullptr) break;
            current = current->left;
        }
    }
    if (key > current->key) {
        current->right = newNode;
    }
    else {
        current->left = newNode;
    }
    return;*/
    insertWorker(key, item, root);
}

void Dictionary::insertWorker(int key, std::string item, node* & current) {
    node* newNode = new node(key, item);
    //Set root
    if (current == nullptr) {
        root = newNode;
        return;
    }
    if (key < current->key) {
        if (current->left != nullptr) {
            insertWorker(key, item, current->left);
        }
        else {
            current->left = newNode;
        }
    }
    else if (key > current->key) {
        if (current->right != nullptr) {
            insertWorker(key, item, current->right);
        }
        else {
            current->right = newNode;
        }
    }
    if (key == current->key) {
        current->item = item;
    }
}

std::string* Dictionary::lookup(int key) {
    lookupWorker(key, root);
}

std::string* Dictionary::lookupWorker(int key, node *current) {
    if (current->key > key) {
        lookupWorker(key, current->left);
    }
    if (current->key < key) {
        lookupWorker(key, current->right);
        }
    if (current->key == key)
        return &(current->item);
}

void Dictionary::remove(int key) {
    removeWorker(root, key);
}

struct node *minValueNode(struct node *node) {
  struct node *current = node;

  while (current && current->left != NULL)
    current = current->left;

  return current;
}

void Dictionary::removeWorker(node * & current, int key) {
    if (current == nullptr) {
        return;
    }
    if (key < current->key)
        removeWorker(current->left, key);
    if (key > current->key)
        removeWorker(current->right, key);
    if (key == current->key) {
        delete current;
        if (current->left && current->right == nullptr) {
            return;
        }
        if (current->right != nullptr && current->left == nullptr) {
            current = current->right;
            return;
        }
        if (current->right == nullptr && current->left != nullptr) {
            current = current->left;
            return;
        }

        struct node *temp = minValueNode(current->right);

        current->key = temp->key;

        removeWorker(current->right, temp->key);
    }
}

void Dictionary::displayEntries()
{
    displayEntriesWorker(root);
}

void Dictionary::displayEntriesWorker(node* currentNode)
{
    if (currentNode == nullptr) {
        return;
    }
        displayEntriesWorker(currentNode->left);
        std::cout << "Key: " << currentNode->key << " Item: " << currentNode->item << std::endl;

        displayEntriesWorker(currentNode->right);
        std::cout << "Key: " << currentNode->key << " Item: " << currentNode->item << std::endl;

}

void Dictionary::displayTree() {
    displayTreeWorker(root, 0);
}

void Dictionary::displayTreeWorker(node* currentNode, int level){
    if (currentNode == nullptr){
        return;
    }
    level += COUNT;
    displayTreeWorker(currentNode->right, level);
    std::cout << std::endl;
    for (int i = COUNT; i < level; i++)
        std::cout << " ";
    std::cout << currentNode->key << ", " << currentNode->item<< "\n";

    displayTreeWorker(currentNode->left, level);
}

void Dictionary::deepDeleteWorker(node * & current) {
    if (current) {
        deepDeleteWorker(current->left);
        deepDeleteWorker(current->right);
        delete current;
    }
}

//Dictionary::~Dictionary() {
//    deepDeleteWorker(root);
//}

void Dictionary::deepCopyWorker(const Dictionary & dictToCopy, node *) {
    while (dictToCopy.left || dictToCopy.right) {
        if (dictToCopy.left) {
            left = new node(*dictToCopy.left);
        }
        if (dictToCopy.right) {
            right = new node(*dictToCopy.right);
        }
        deepCopyWorker(dictToCopy, dictToCopy.right);
        deepCopyWorker(dictToCopy, dictToCopy.left);
    }
}

void Dictionary::rotateRight(node * &current) {
    node* a;
    node* b;

    b = current;
    a = b->left;
    if (a->right != nullptr) {
        a->right->parent = a;
    }
    a->parent = b->parent;

    if (b->parent == nullptr) {
        root = a;
    }
    else if (b == a->parent->right) {
       b->parent->right = a;
    }
    else b->parent->left = a;
    a->left = b;
    b->parent = a;
}

void Dictionary::rotateLeft(node *& current) {
    node* a;
    node* b;

    //https://stackoverflow.com/questions/4597650/code-with-explanation-for-binary-tree-rotation-left-or-right
    a = current;
    b = a->right;
    if (b->left != nullptr) {
        b->left->parent = a;
    }
    b->parent = a->parent;

    if (a->parent == nullptr) {
        root = b;
    }
    else if (a == a->parent->left) {
       a->parent->left = b;
    }
    else a->parent->right = b;
    b->left = a;
    a->parent = b;
}
