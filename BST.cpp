#include "BST.h"

BST::BST():root(nullptr),height(0)
{}

BST::BST(const website &aSite)
{
    root = new node(aSite);
    height = 1;
}


BST::BST(const BST &aSearchTree):root(nullptr),height(0)
{
    *this = aSearchTree;
}

BST& BST::operator=(const BST &aTree)
{

    if(this == &aTree)
        return *this;
    destroy();

    copyTree(this->root, aTree.root);
    height = aTree.height;

    return *this;
}


void BST::copyTree(BST::node *&destTree, BST::node *sourceTree)
{
    if(!sourceTree) return;
    destTree = new node(*(sourceTree->data),sourceTree->leftChild,
                        sourceTree->rightChild);

}


BST::~BST()
{
    destroy(root);
}


void BST::destroy(node *& sTree)
{
    if(!sTree) return;

    // simply pass in left and right child of root
    // this ensures that every node in the tree is removed
    destroy(sTree->leftChild);
    destroy(sTree->rightChild);

    sTree = nullptr;
}

// recursive print in order
// to display a BST in order
// display all nodes in left tree of root first
// then root
// then the roots right child
// this is inorder because all nodes in left are less than
// root, and all nodes in right are greater than root
// leaving root as the middle value
void BST::_print(node * root)
{
    if(!root)
        return;

    _print(root->leftChild);
    cout << root->data << endl;
    _print(root->rightChild);
}

