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
	void printLevels();


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
    bool _remove(node *&, const char *,  website &, bool, bool &);
    void deleteNode(node *& tRoot);
    BST::node* _findSuccessor(node * tRoot);
    void _print(node *);
    void _printKeys(node *);
    void _printTopics(node *);
    void _getTopics(const node *, node *&);
    void _getKeys(BST::node *, node *&);
    int getCurrentHeight(const node *) const;
    int getFrequency(node * tRoot, const char * key);


    BST::node * inOrderSuccessor(node *, node *, const char *);
	node * placeNode(node *, const website &); // recurse to place this node in the tree
    BST::node* placeNodeSorted(node * tRoot, const website &);
	node * search( node * , char *, bool ) ; // search for a

    // node
    // return where it should be
};
