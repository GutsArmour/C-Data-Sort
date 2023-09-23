#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>

#endif // DICTIONARY_H

struct node
{
      char data;
      node* next;
      node* root;
      node* right;
      node* left;
      node* parent;
      int key;
      std::string item;
      node(int key, std::string item);
};

class Dictionary
{
  public:
    //~Dictionary();

    Dictionary(Dictionary &);

    //Dictionary(const Dictionary &);

    //Dictionary(Dictionary &&);

    std::string* lookup(int);

    void insert(int key, std::string item);


    void displayEntries();

    void displayTree();

    void remove(int key);

    private:
    node* root;
    node* right;
    node* left;
    node* parent;

    void rotateLeft(node * &);
    void rotateRight(node * &);

    void removeWorker (node* &, int key);

    void displayEntriesWorker (node *);

    void displayTreeWorker (node *, int level);

    std::string* lookupWorker(int key, node *);

    void insertWorker(int key, std::string item, node * &);

    void deepDeleteWorker(node* &);

    void deepCopyWorker(const Dictionary &, node*);
};

