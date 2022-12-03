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


/*
 * Print all the current keys for each website along with the URL
 * they go with. Outputting the URL the key belongs to is needed as the user
 * is not supplying the key, the website ADT is creating its own key
 * based on some random cstring in the URL
 *
 * EX: linked-list-notes => https://www.greg.com/linked-list-notes
 * <KEY => URL>
 */
void BST::printKeys()
{
    if(isEmpty())
        return;

    listLink *key = nullptr;
    int idx = 1;
    _getKeys(root, key);

    for(auto *curr = key; curr; curr = curr->next)
    {
        cout << idx << ".\t" << curr->topic << " => " << curr->siteKey
             << endl;
        idx++;
    }

    destroyListLink(key);
}


/*
 * Create a linear SLL of all topics in the tree.
 * Creating this list allows us to quickly traverse and print all topic names.
 */
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


/*
 * get a linear SLL of all website keys in the tree.
 * Use of SLL here allows us to quickly print each key => url pair.
 */
void BST::_getKeys(BST::node *tRoot, BST::listLink *& keyList)
{

    if(!tRoot)
        return;

    keyList = new listLink(tRoot->data->getKey(),
                            tRoot->data->getURL());

    _getKeys(tRoot->leftChild, keyList->next);
    _getKeys(tRoot->rightChild, keyList->next);

}


/*
 * Find a website in our tree.
 * @param tRoot the root of the current BST
 * @param key the search key used to locate the item
 * @return a pointer to the website in the tree. nullptr if not found.
 */
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

/*
 * Check if the tree is empty
 * @return true if the root node is nullptr false if else.
 */
bool BST::isEmpty() const
{
    return root == nullptr;
}


/*
 * Insert a website into our tree in a sorted way.
 * @param website & a ref to the website we wish to add to the tree.
 * @return true if node count increased by 1 false if else.
 */
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


/*
 * recurse our binary tree to find the proper place to insert the new website
 * @param tRoot the root of the binary tree we wish to add too
 * @param aSite a ref to a website we wish to place in the tree.
 */
BST::node * BST::placeNode(node * tRoot, const website & aSite)
{


	if(!tRoot)
    {
        cout << "Adding root node\n";
        count++;
        return new node(aSite,nullptr,nullptr);

    }

	if(*tRoot->data > aSite)
	{
        cout << "Adding as left child \n";
        tRoot->leftChild = placeNode(tRoot->leftChild, aSite);
        return tRoot;
	}

    cout << "Adding as right child \n";
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
    return _remove(root, topic,false);

}

/*
 * Remove a particular website based on its site key
 * @param aSite the website object we wish to remove from this struct
 * @return true if site was removed false if else.
 */
bool BST::removeWebsite(website &aSite)
{
    return _remove(root, aSite.getKey(), true);
}

/*
 * Recursive removal of a node in the tree
 * This method covers the 3 cases we must watch for when removing a node
 * from a BST
 * a) no children b) one child c) two children
 * @param tRoot the root of the binary tree
 * @param key - the key we want to use to identify websites
 */
bool BST::_remove(node *& tRoot, const char * key, const bool singleSite)
{
    node * temp = nullptr;

    if(!tRoot)
        return false;

    // remove a single website based on site key and not site topic
    if(singleSite)
    {
        if(strcmp(tRoot->data->getKey(), key) == 0)
        {
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
            else
            {
                temp = inOrderSuccessor(tRoot);
                tRoot->data = temp->data;
                _remove(tRoot->rightChild, key, singleSite);
            }
        }
    }
    else // remove all websites of a given topic.
    {
        // current nodes key is > search key; remove from left subtree
        if(strcmp(tRoot->data->getTopic(), key) < 0)
            return _remove(tRoot->leftChild, key, singleSite);
        // current nodes key is < search key; remove from right subtree.
        if(strcmp(tRoot->data->getTopic(), key) > 0)
            return _remove(tRoot->rightChild, key, singleSite);

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
        _remove(tRoot->rightChild, key, singleSite);
    }



    return true;
}


/*
 * Get the current height of the BST
 * @return the length of the longest path from root to leaf.
 */
int BST::getHeight() const
{
    return getCurrentHeight(root);
}


/*
 * recurse our tree and get the height of each of its subtrees
 * the subtree with the largest height = the height of the bst.
 * @param tRoot a node that represents the root of the binary search tree.
 * @return the height of the binary search tree int.
 */
int BST::getCurrentHeight(const node * tRoot) const
{
    int leftHeight, rightHeight = 0;

    if(!tRoot)
        return 0;

    // get the height of roots right and left trees
    // the height of the tree is the total height of its
    // largest subtree
    // these count the number of times current height is called.
    leftHeight = getCurrentHeight(tRoot->leftChild);
    rightHeight = getCurrentHeight(tRoot->rightChild);

    // return which ever tree is bigger as the height of the BST.
    return (leftHeight >= rightHeight ? (leftHeight + 1) : (rightHeight + 1));
}


/*
 * Overloaded out stream operator; Allows easy output of a bst.
 */
ostream& operator<<(ostream &out, BST & bTree)
{
    if(bTree.isEmpty())
        return out << "Nothing to display " << endl;
    out << bTree.print() << endl;

    return out;
}


/*
 * Get a website from our tree based on its keyword
 * @param siteKey the char pointer with the site key we wish to obtrain
 * @param theSite, a ref to the site if found, return nullptr if else
 *
 */
bool BST::retrieve(const char *siteKey, website & theSite)
{
    node * searchSite = search(root, (char*)siteKey);
    if(searchSite)
        theSite = *searchSite->data;

    return searchSite != nullptr;
}


/*
 * Get the total number of items on this binary search tree.
 */
int BST::getCount() const
{
    return count;
}

















