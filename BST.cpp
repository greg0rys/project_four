#include "BST.h"



BST::BST() : root(nullptr), height(0), count(0)
{}



BST::BST(const website &aSite)
{
    root = new node(aSite);
    height = 1;
    count = 1;
}



BST::BST(const BST &aSearchTree) : root(nullptr), height(0)
{
    *this = aSearchTree;
}



BST &BST::operator=(const BST &aTree)
{

    if (this == &aTree)
        return *this;

    destroy(root);

    if (!aTree.root) {
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
    if (!sourceTree) return;

    destTree = new node(*(sourceTree->data));
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
void BST::destroy(node *&tRoot)
{
    if (!tRoot) return;


    // simply pass in left and right child of root
    // this ensures that every node in the tree is removed
    destroy(tRoot->leftChild);
    destroy(tRoot->rightChild);
    delete tRoot;

    tRoot = nullptr;
}



/*
 * Load saved CSV data to build a BST
 * @param filename a char array with the name
 * 		  of the file to load from.
 * @return the total # of loaded items.
 */

int BST::loadFromFile(const char *filename)
{
    fstream file(filename);
    int totalLoaded = 0, siteRating = 0;
    const int MAX_CHAR = 300;
    char siteTopic[MAX_CHAR], siteURL[MAX_CHAR],
            siteSummary[MAX_CHAR], siteReview[MAX_CHAR] = {0};
    website siteData;

    if (!file)
        return 0;

    file.get(siteTopic, MAX_CHAR, ';');

    do {
        file.get();
        file.get(siteURL, MAX_CHAR, ';');
        file.get();
        file.get(siteSummary, MAX_CHAR, ';');
        file.get();
        file.get(siteReview, MAX_CHAR, ';');
        file.get();
        file >> siteRating;
        file.ignore(MAX_CHAR, '\n');

        siteData.setTopic(siteTopic);
        siteData.setURL(siteURL);
        siteData.writeSummary(siteSummary);
        siteData.writeReview(siteReview);
        siteData.setRating(siteRating);

        insert(siteData);
        totalLoaded++;

        file.get(siteTopic, MAX_CHAR, ';');
    } while (!file.eof());
    file.close();
    return totalLoaded;
}



bool BST::print()
{
    if (isEmpty())
        return false;

    _print(root);
    return true;
}



/**
 * Print the BST in order by traversing left -> root -> right
 * @param tRoot - the root of our binary tree.
 * @return NULL
 */
void BST::_print(node *tRoot)
{
    if (!tRoot)
        return;

    _print(tRoot->leftChild);
    cout << *tRoot->data << endl;
    _print(tRoot->rightChild);
}



void BST::printTopics()
{
    if (isEmpty())
        return;
    node *topicsTree = nullptr;

    _getTopics(root, topicsTree);
    _printTopics(topicsTree);

    delete topicsTree;
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
    if (isEmpty())
        return;
    node *keysTree = nullptr;

    _getKeys(root, keysTree);
    _printKeys(keysTree);

    delete keysTree;
}



void BST::_printKeys(node *tRoot)
{
    if (!tRoot)
        return;
    _printKeys(tRoot->leftChild);
    cout << tRoot->data->getKey() << endl;
    _printKeys(tRoot->rightChild);
}



/*
 * Create a linear SLL of all topics in the tree.
 * Creating this list allows us to quickly traverse and print all topic names.
 */
void BST::_getTopics(const node *tRoot, node *&topicsTree)
{
    if (!tRoot)
        return;

    if(search(topicsTree, tRoot->data->getKey(),true))
    {
        topicsTree = placeNodeSorted(topicsTree, *tRoot->data);

    }
     _getTopics(tRoot->leftChild, topicsTree->leftChild);
     _getTopics(tRoot->rightChild, topicsTree->rightChild);



}



void BST::_printTopics(BST::node *tRoot)
{
    if (!tRoot)
        return;
    _printTopics(tRoot->leftChild);
    cout << tRoot->data->getTopic() << endl;
    _printTopics(tRoot->rightChild);
}



/*
 * get a linear SLL of all website keys in the tree.
 * Use of SLL here allows us to quickly print each key => url pair.
 */
void BST::_getKeys(BST::node *tRoot, node *&keysTree)
{

    if (!tRoot)
        return;


    keysTree = placeNode(keysTree, *tRoot->data);
    _getKeys(tRoot->leftChild, keysTree->leftChild);
    _getKeys(tRoot->rightChild, keysTree->rightChild);

}



/*
 * Find a website in our tree.
 * @param tRoot the root of the current BST
 * @param key the search key used to locate the item
 * @return a pointer to the website in the tree. nullptr if not found.
 */
BST::node *BST::search(node *tRoot, char *key, bool topics)
{

    if(!tRoot)
        return tRoot;

    int result;
    if(topics)
    {

        result = strcmp(key, tRoot->data->getTopic());

    }
    else
    {
        result = strcmp(key, tRoot->data->getKey());

    }

    if (result == 0)
        return tRoot;

    if (result < 0)
    {
        return search(tRoot->leftChild, key, topics);
    }

        return search(tRoot->rightChild, key, topics);



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
    int updatedCount, currentCount;

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
BST::node *BST::placeNode(node *tRoot, const website &aSite)
{


    if (!tRoot) {
        count++;
        return new node(aSite, nullptr, nullptr);
    }

    if (*tRoot->data > aSite) {
        tRoot->leftChild = placeNode(tRoot->leftChild, aSite);
    } else {
        tRoot->rightChild = placeNode(tRoot->rightChild, aSite);
    }
    return tRoot;


}

BST::node* BST::placeNodeSorted(BST::node *tRoot, const website &aSite)
{
    if(!tRoot)
        return new node(aSite);

    if(strcmp(aSite.getTopic(), tRoot->data->getTopic()) == 0)
    {
        return nullptr;
    }

    if(strcmp(aSite.getTopic(), tRoot->data->getTopic()) < 0)
    {
        tRoot->leftChild = placeNodeSorted(tRoot->leftChild,
                                           *tRoot->leftChild->data);
    }
    else
    {
        tRoot->rightChild = placeNodeSorted(tRoot->rightChild,
                                            *tRoot->rightChild->data);
    }
    return tRoot;
}








/*
 * When we remove a node with two children we must swap
 * it with its in order successor. This method traverses to
 * a given nodes in order successor and return sit.
 */
BST::node *BST::inOrderSuccessor(node *tRoot, node *successor,
                                 const char *key)
{
    if (!tRoot)
        return successor;

    if (strcmp(tRoot->data->getKey(), key) == 0) {
        if (tRoot->rightChild)
            return _findSuccessor(tRoot->rightChild);

    } else if (strcmp(key, tRoot->data->getKey()) < 0) {
        successor = tRoot;
        return inOrderSuccessor(tRoot->leftChild, successor, key);

    } else {
        return inOrderSuccessor(tRoot->rightChild, successor, key);
    }
    return successor;
}



BST::node *BST::_findSuccessor(BST::node *tRoot)
{

    while (tRoot->leftChild)
        tRoot = tRoot->leftChild;
    return tRoot;
}



/*
 * Remove all websites based on a given key
 * @param topic - the topic of websites you wish to remove
 * @return true if the node was removed false if else.
 */
bool BST::remove(const char *topic, website &aSite, bool &removed)
{
    return _remove(root, topic, aSite, false, removed);

}



/*
 * Remove a particular website based on its site key
 * @param aSite the website object we wish to remove from this struct
 * @return true if site was removed false if else.
 */
bool BST::removeWebsite(website &aSite, bool &removed)
{
    return _remove(root, aSite.getKey(), aSite, true, removed);
}



/*
 * Recursive removal of a node in the tree
 * This method covers the 3 cases we must watch for when removing a node
 * from a BST
 * a) no children b) one child c) two children
 * @param tRoot the root of the binary tree
 * @param key - the key we want to use to identify websites
 */
bool BST::_remove(node *&tRoot, const char *key, website &aSite,
                  bool singleSite, bool &removed)
{

    if (!tRoot) {
        removed = false;
        return removed;
    }


    if (singleSite) {
        int result = strcmp(key, tRoot->data->getKey());
        if (result == 0) {
            aSite = *(tRoot->data);
            deleteNode(tRoot);
            count--;
            return true;
        } else if (result < 0) {
            return _remove(tRoot->leftChild, key, aSite, singleSite, removed);
        } else {
            return _remove(tRoot->rightChild, key, aSite, singleSite, removed);
        }
    } else {
        int result = strcmp(key, tRoot->data->getTopic());

        if (result == 0) {
            node *tempL = nullptr, *tempR = nullptr;
            aSite = *tRoot->data;
            tempL = tRoot->leftChild;
            tempR = tRoot->rightChild;
            deleteNode(tRoot);
            removed = true;
            count--;
            if (tempL)
                return _remove(tempL, key, aSite, singleSite, removed);
            if (tempR)
                return _remove(tempR, key, aSite, singleSite, removed);

            return true;
        } else if (result < 0) {
            return _remove(tRoot->leftChild, key, aSite, singleSite, removed);
        } else {
            return _remove(tRoot->rightChild, key, aSite, singleSite, removed);
        }
    }
}



void BST::deleteNode(BST::node *&tRoot)
{
    node *temp = nullptr;
    node *curr, *prev = nullptr;
    if (!tRoot->leftChild && !tRoot->rightChild) {
        delete tRoot;
        tRoot = nullptr;
        return;
    } else if (!tRoot->rightChild) {
        temp = tRoot;
        tRoot = tRoot->leftChild;
        delete temp;
        temp = nullptr;
        return;
    } else if (!tRoot->leftChild) {
        temp = tRoot;
        tRoot = tRoot->rightChild;
        delete temp;
        return;
    } else {
        curr = tRoot->rightChild;
        if (!curr->leftChild) {
            tRoot->rightChild = curr->rightChild;
        } else {
            while (curr->leftChild) {
                prev = curr;
                curr = curr->leftChild;
            }
            prev->leftChild = curr->rightChild;
        }

        *tRoot->data = *curr->data;
        delete curr;
        return;
    }
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
int BST::getCurrentHeight(const node *tRoot) const
{
    int leftHeight, rightHeight = 0;

    if (!tRoot)
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
ostream &operator<<(ostream &out, BST &bTree)
{
    if (bTree.isEmpty())
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
bool BST::retrieve(const char *siteKey, website &theSite)
{
    node *searchSite = search(root, (char *) siteKey, false);
    if (searchSite)
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



int BST::getFrequency(BST::node *tRoot, const char *key)
{
    int total = 0;
    if (!tRoot)
        return 0;

    if (strcmp(tRoot->data->getTopic(), key) == 0)
        total++;

    total += getFrequency(tRoot->leftChild, key);
    total += getFrequency(tRoot->rightChild, key);

    return total;
}

















