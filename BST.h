#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
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

    bool insert(const website &);
    bool remove(const char *);
    bool removeWebsite(const char *, website &); // use a website ref to
    // copy deleted data for use to see
    bool retrieve(const char *, website *&, int &);
    bool print();
    int getHeight() const;

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
    };
    node * root;
    int height;
    void destroy(node *&);
    void copyTree(node *& destTree, node * sourceTree);
    bool _insert(node *&, const website &);
    bool _remove(node *&, const char *);
    bool _removeWebsite(node *&, const char *);
    void _print(node *);
    int getCurrentHeight() const;
	node * placeNode(node *, const website &); // recurse to place this node in the tree
	bool search(const char *, int &) const; // search for a node return where it should be
};
