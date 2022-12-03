#include "BST.h"

BST::BST(): root(nullptr), height(0),count(0)
{}

BST::BST(const website &aSite)
{
    root = new node(aSite);
    height = 1;
    count = 1;
}


BST::BST(const BST &aSearchTree): root(nullptr), height(0)
{
    *this = aSearchTree;
}

BST& BST::operator=(const BST &aTree)
{

    if(this == &aTree)
        return *this;

    destroy(root);

    if(!aTree.root)
    {
        root = nullptr;
        height = aTree.height;
        count = aTree.count;
        return *(this);
    }

    copyTree(this->root, aTree.root);
    height = aTree.height;
    count = aTree.count;

    return *this;
}

// in order traverse to copy the tree
void BST::copyTree(BST::node *&destTree, BST::node *sourceTree)
{
    if(!sourceTree) return;

    destTree = new node(*(sourceTree->data) );
    copyTree(destTree->leftChild, sourceTree->leftChild);
    copyTree(destTree->rightChild, sourceTree->rightChild);

}


BST::~BST()
{
    destroy(root);
}

/**
 * Destroy our BST by recursion.
 * to destroy a btree we must use post order traversal
 * @param tRoot
 */
void BST::destroy(node *& tRoot)
{
    if(!tRoot) return;


    // simply pass in left and right child of root
    // this ensures that every node in the tree is removed
    destroy(tRoot->leftChild);
    destroy(tRoot->rightChild);
    delete tRoot;

    tRoot =  nullptr;
}

void BST::destroyListLink(BST::listLink *&head)
{
    if(!head)
        return;
    destroyListLink(head->next);
    delete head;
    head = nullptr;
}


bool BST::print()
{
    if(isEmpty())
        return false;

    _print(root);
    return true;
}
/**
 * Print the BST in order by traversing left -> root -> right
 * @param tRoot - the root of our binary tree.
 * @return NULL
 */
void BST::_print(node * tRoot)
{
    if(!tRoot)
        return;

    _print(tRoot->leftChild);
    cout << *tRoot->data << endl;
    _print(tRoot->rightChild);
}

void BST::printTopics()
{
    if(isEmpty())
        return;

    listLink * topicsList = nullptr;
    int idx = 1;
    _getTopics( root, topicsList);

    for(auto *curr = topicsList; curr; curr = curr->next)
    {
        cout << idx << ".\t" << curr->topic << endl;
        idx++;

    }

    destroyListLink(topicsList);
    topicsList = nullptr;

}


void BST::printKeys()
{
    if(isEmpty())
        return;

    listLink *key = nullptr;
    int idx = 1;
    _getKeys(root, key);

    for(auto *curr = key; curr; curr = curr->next)
    {
        cout << idx << ".\t" << curr->siteKey << " => " << curr->topic
             << endl;
        idx++;
    }

    destroyListLink(key);
}


void BST::_getTopics(const node *tRoot, BST::listLink *&
topicsList)
{
    if(!tRoot)
        return;

    topicsList = new listLink(tRoot->data->getTopic(),
                               nullptr);
    _getTopics( tRoot->leftChild, topicsList->next);
    _getTopics(tRoot->rightChild, topicsList->next);

}


void BST::_getKeys(BST::node *tRoot, BST::listLink *& keyList)
{

    if(!tRoot)
        return;

    keyList = new listLink(tRoot->data->getKey(),
                            tRoot->data->getURL());

    _getKeys(tRoot->leftChild, keyList->next);
    _getKeys(tRoot->rightChild, keyList->next);

}



BST::node * BST::search(node * tRoot, char *key)

{
    if(!tRoot || strcmp(tRoot->data->getKey(), key) == 0)
        return tRoot;

    if(tRoot->data->getKey() > key)
    {
        return search(tRoot->leftChild, key);
    }

    return search(tRoot->rightChild, key);
}


bool BST::isEmpty() const
{
    return root == nullptr;
}


bool BST::insert(const website &aSite)
{
    int updatedCount,currentCount;

    currentCount = count; // get the count before the insert
    root = placeNode(root, aSite);
    updatedCount = getCount(); // get the newly updated count

    // true if we added an item updated will be +1 currentCount
    // false if current = updated. (ie no change in count = no addition to
    // struct)
    return currentCount != updatedCount;
}


BST::node * BST::placeNode(node * tRoot, const website & aSite)
{


	if(!tRoot)
    {
        count++;
        return new node(aSite,nullptr,nullptr);

    }

	if(*tRoot->data > aSite)
	{
        tRoot->leftChild = placeNode(tRoot->leftChild, aSite);
        return tRoot;
	}


    tRoot->rightChild = placeNode(tRoot->rightChild, aSite);

	return tRoot;
}

/*
 * When we remove a node with two children we must swap
 * it with its in order successor. This method traverses to
 * a given nodes in order successor and return sit.
 */
BST::node* BST::inOrderSuccessor(node * tRoot)
{
    node * curr = tRoot->rightChild;
    while(curr->leftChild)
        curr = curr->leftChild;
    return curr;
}


/*
 * Remove all websites based on a given key
 * @param topic - the topic of websites you wish to remove
 * @return true if the node was removed false if else.
 */
bool BST::remove(const char * topic)
{
    return _remove(root, topic);

}

/*
 * Remove a particular website based on its site key
 * @param aSite the website object we wish to remove from this struct
 * @return true if site was removed false if else.
 */
bool BST::removeWebsite(website &aSite)
{
    return _remove(root, aSite.getKey());
}

/*
 * Recursive removal of a node in the tree
 * This method covers the 3 cases we must watch for when removing a node
 * from a BST
 * a) no children b) one child c) two children
 * @param tRoot the root of the binary tree
 * @param key - the key we want to use to identify websites
 */
bool BST::_remove(node *& tRoot, const char * key)
{
    node * temp = nullptr;

    if(!tRoot)
        return false;

    // current nodes key is > search key; remove from left subtree
    if(strcmp(tRoot->data->getTopic(), key) < 0)
        return _remove(tRoot->leftChild, key);
    // current nodes key is < search key; remove from right subtree.
    if(strcmp(tRoot->data->getTopic(), key) > 0)
        return _remove(tRoot->rightChild, key);

    if(!tRoot->leftChild && !tRoot->rightChild)
    {
        delete tRoot;
        tRoot = nullptr;
        return true;
    }
    else if(tRoot->rightChild)
    {
        temp = tRoot->leftChild;
        delete tRoot;
        tRoot = temp;
        return true;
    }
    else if(tRoot->leftChild)
    {
        temp = tRoot->rightChild;
        delete tRoot;
        tRoot = temp;
        return true;
    }

    // node has two children
    temp = inOrderSuccessor(tRoot);
    tRoot->data = temp->data;
    _remove(tRoot->rightChild, temp->data->getTopic());

    return true;
}



int BST::getHeight() const
{
    return getCurrentHeight(root);
}



int BST::getCurrentHeight(const node * tRoot) const
{
    int leftHeight, rightHeight = 0;

    if(!tRoot)
        return 0;

    // get the height of roots right and left trees
    // the height of the tree is the total height of its
    // largest subtree
    leftHeight = getCurrentHeight(tRoot->leftChild);
    rightHeight = getCurrentHeight(tRoot->rightChild);

    return (leftHeight >= rightHeight ? (leftHeight + 1) : (rightHeight + 1));
}


ostream& operator<<(ostream &out, BST & bTree)
{
    if(bTree.isEmpty())
        return out << "Nothing to display " << endl;
    out << bTree.print() << endl;

    return out;
}



bool BST::retrieve(const char *siteKey, website & theSite)
{
    node * searchSite = search(root, (char*)siteKey);
    if(searchSite)
        theSite = *searchSite->data;

    return searchSite != nullptr;
}


int BST::getCount() const
{
    return count;
}










