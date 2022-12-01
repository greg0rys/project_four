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
    destroy(root);

    copyTree(this->root, aTree.root);
    height = aTree.height;

    return *this;
}


void BST::copyTree(BST::node *&destTree, BST::node *sourceTree)
{
    if(!sourceTree) return;
    destTree = new node(*(sourceTree->data),sourceTree->leftChild,
                        sourceTree->rightChild);
    copyTree(destTree->next, sourceTree->next);

}


BST::~BST()
{
    destroy(root);
}

/**
 * Destroy our BST by recursion. Pass in both the left and right subtree and have all nodes deleted.
 * @param sTree
 */
void BST::destroy(node *& sTree)
{
    if(!sTree) return;

    // simply pass in left and right child of root
    // this ensures that every node in the tree is removed
    destroy(sTree->leftChild);
    destroy(sTree->rightChild);

    sTree = sTree->leftChild = sTree->rightChild =  nullptr;
}


/**
 * Print the BST in order by traversing left -> root -> right
 * @param root - the root of our binary tree.
 * @return NULL
 */
void BST::_print(node * root)
{
    if(!root)
        return;

    _print(root->leftChild);
    cout << root->data << endl;
    _print(root->rightChild);
}

BST::node * BST::search(node * start,  char *key, int &pos)

{
    if(!start || strcmp(start->data->getKey(), key) == 0)
        return start;

    if(root->data->getKey() > key)
    {
        return search(start->leftChild, key, ++pos);
    }

    return search(start->rightChild, key, ++pos);
}


bool BST::insert(const website &aSite)
{
    root = placeNode(root,aSite);

    return true;
}


BST::node * BST::placeNode(node * root, const website & aSite)
{


	if(!root)
		return new node(aSite,nullptr,nullptr);

	if(*root->data > aSite)
	{
		root->leftChild = placeNode(root->leftChild, aSite);
        return root;
	}


	root->rightChild = placeNode(root->rightChild, aSite);

	return root;
}


bool BST::remove(const char * topic)


