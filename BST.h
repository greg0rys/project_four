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
    bool removeWebsite(website &); // use a website ref to
    // copy deleted data for use to see
    bool retrieve(const char *, website &);
    bool print();
    int getHeight() const;
    int getCount() const;
    bool isEmpty() const;
    void printTopics();
    void printKeys();


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

    // a list link represents a forward linear SLL
    struct listLink
    {
        char * topic;
        char * siteKey;
        listLink * next;

        listLink()
        {
            topic = siteKey = nullptr;
            next = nullptr;
        }

        listLink(const char * siteTopic, const char *sitesKey)
        {
            if (!siteTopic) {
                topic = nullptr;

            } else {
                topic = new char[strlen(siteTopic) + 1];
                strcpy(topic, siteTopic);
            }

            if (!sitesKey) {
                siteKey = nullptr;
            }
            else {
                siteKey = new char[strlen(sitesKey) + 1];
                strcpy(siteKey, sitesKey);
            }
            next = nullptr;
        }

        ~listLink()
        {
            if(topic) delete []topic;
            if(siteKey) delete [] siteKey;
            topic = siteKey = nullptr;
            next = nullptr;
        }


    };


    node * root;
    int height,count;


    void destroy(node *&);
    void destroyListLink(listLink *&);
    void copyTree(node *& destTree, node * sourceTree);
    bool _remove(node *&, const char *, const bool );
    void _print(node *);
    void _getTopics(const node *, listLink *&);
    void _getKeys(BST::node *, BST::listLink *&);
    int getCurrentHeight(const node *) const;


    BST::node * inOrderSuccessor(node *);
	node * placeNode(node *, const website &); // recurse to place this node in the tree
	node * search( node * , char *) ; // search for a
    // node
    // return where it should be
};
