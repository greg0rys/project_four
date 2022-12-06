#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include "website.h"
using namespace std;

class BST
{
public:
    BST();
    BST(const website &);
    BST(const BST &);
    ~BST();
    BST& operator=(const BST &);
    friend ostream& operator<<(ostream &, BST &);

	int loadFromFile(const char *);
    bool insert(const website &);
    bool remove(const char *, website &, bool &);
    bool removeWebsite(website &, bool &); // use a website ref to
    // copy deleted data for use to see
    bool retrieve(const char *, website &);
    bool print();
    int getHeight() const;
    int getCount() const;
    bool isEmpty() const;
    void printTopics();
    void printKeys();
	int getFrequency(const char *);


private:
    struct node
    {
        website * data;
        node *leftChild,*rightChild;

        node()
        {
            data = nullptr;
            leftChild = rightChild = nullptr;
        }

        node(const website &aWebsite)
        {
            data = new website(aWebsite);
            leftChild = rightChild = nullptr;
        }

        node(const website &aWebsite, node * left, node *right)
        {
            data = new website(aWebsite);
            leftChild = left;
            rightChild = right;
        }

        ~node()
        {
            if(data)
                delete data;
            leftChild = rightChild = nullptr;
            data = nullptr;
        }

        node(const node &aNode)
        {
            if (data)
                delete data;
            data = nullptr;
            leftChild = rightChild = nullptr;

            if (aNode.data) {
                data = new website(*aNode.data);
            }

            leftChild = aNode.leftChild;
            rightChild = aNode.rightChild;
        }
    };




    node * root;
    int height,count;


    void destroy(node *&);
    void copyTree(node *& destTree, node * sourceTree);
    bool _remove(node *&, const char *, bool &);
    bool checkArray(website *, const char *, int &arraySize);
    BST::node* deleteNode(node *& tRoot, const char *, bool);
    void _print(node *);
    void _printTopics(node *, int &);
    void _printKeys(node *,int &);
    int getCurrentHeight(const node *) const;
    int getFrequency(node * tRoot, const char * key);
    int _getCount(node *) const;


    BST::node * inOrderSuccessor(node *);
    BST::node * placeNode(node *, const website &);
	BST::node * search( node * , char *);

    // node
    // return where it should be
};
