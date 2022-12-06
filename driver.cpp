#include "driver.h"

/*
 * filename: driver.cpp
 * the implementation file for driver.h
 */


/*
 * Create a menu of choices the user can select to invoke operations.
 */
void menu()
{
    BST theTree;
    int option = 0;
	menuOperations(theTree, option);

    do {
        cout <<  " ****** MENU: ****** " << endl;
        cout << "1.\t Add a Website to the tree." << endl
             << "2.\t Get a website by keyword." << endl
             << "3.\t Display [ all ] Websites in the table" << endl
             << "4.\t Remove [ all ] Websites of a topic." << endl
             << "5.\t Remove a Website by keyword." << endl
             << "6.\t Display the current height of the tree." << endl
             << "7.\t Quit the program" << endl
			 << "8.\t Print Levels" << endl;
        cout << "Please enter a menu choice [EX 1. to add]: ";
        option = getInteger();
        menuOperations(theTree, option);

    } while(option != 7);
}

/*
 * Call all the operations listed in the menu choices.
 * @param aTree the table we are going to operate on
 * @param opertionNo the number of the menu item to invoke.
 */
void menuOperations(BST &aTree, int & operationNo)
{
    website aWebsite;
    char * searchKey = nullptr;
    int totalCounted;
    bool removed = false;

    switch(operationNo)
    {
		case 0:
			totalCounted = aTree.loadFromFile("bst.txt");
			if(totalCounted <= 0)
			{
				cout << "Error no data loaded from bst.txt" << endl;
				break;
			}
			cout << "Loaded " << totalCounted 
				 << " websites into the tree\n";
			break;

        case 1:
            generateWebsite(aWebsite);
            if(aTree.insert(aWebsite))
                cout << "Success added: " << aWebsite.getKey() << endl
                     << "Tree now has: " << aTree.getCount() << " websites\n";
            break;

        case 2:
            if(aTree.isEmpty())
            {
                cout << "The tree is empty, nothing to search for.\n";
                break;
            }

            cout << "****** HERE'S A LIST OF SITE KEYS ****** \n";
            aTree.printKeys();
            cout << endl;
            cout << "Please enter the keyword of the website to retrieve: ";
            getInput(searchKey);
            if(aTree.retrieve(searchKey, aWebsite))
            {
                cout << "****** FOUND " << searchKey << " ****** " << endl;
                cout << aWebsite << endl;
            }
            else
            {
                cout << "There were no websites found for: " << searchKey <<
                     endl;
            }
            if(searchKey)
                delete []searchKey;
            searchKey = nullptr;
            break;
        case 3:
            if(!aTree.isEmpty())
                cout << aTree << endl;
            else
                cout << "The tree is empty!" << endl;
            break;

        case 4:
            if(aTree.isEmpty())
            {
                cout << "Error the tree is empty! " << endl;
                break;
            }

            cout << "**** HERES A LIST OF TOPICS **** " << endl;
            aTree.printTopics() ;

            cout << "Please enter the name of the topic you wish to remove: ";
            getInput(searchKey);

            totalCounted = aTree.getFrequency(searchKey);
            aTree.remove(searchKey,aWebsite,removed);
            if(removed)
            {
                cout << "Success " << totalCounted
                     << " websites removed for " << searchKey << endl;
            }
            else
            {
                cout << "Error no matching topic for " << searchKey << endl;
            }

            // if this switch statement is called search key will always !=
            // nullptr no check needed.
            if(searchKey)
                delete []searchKey;
            searchKey = nullptr;
            break;


        case 5:
            if(aTree.isEmpty())
            {
                cout << "The tree is empty nothing to remove\n";
                break;
            }

            cout << "*** Here's a list of keywords *** " << endl;
            aTree.printKeys();

            cout << "Please enter the key you want to remove: ";
            getInput(searchKey);
            aWebsite.setKey(searchKey);
            cout << aWebsite.getKey() << endl;
            aTree.removeWebsite(aWebsite,removed);
            if(removed)
            {

                cout << "Removed: " << aWebsite.getKey() << endl;
            }
            else
            {
                cout << "No matching website for given key: " << searchKey <<
                     endl;
            }


            if(searchKey)
                delete []searchKey;
            searchKey = nullptr;
            break;

        case 6:
            if(aTree.isEmpty())
            {
                cout << "The tree is empty! " << endl;
                break;
            }

            cout << "The current height of the tree is: " << aTree.getHeight()
                 << endl << "\tThis tree currently has " << aTree.getCount()
                 << " items in it" << endl;
            break;
        case 7:
            cout << "Thanks for using me! Goodbye!" << endl;
            break;
		case 8:
			cout << "HI";
			break;
        default:
            cout << "That is not a valid menu choice try again " << endl;

    }
}


/*
 * Generate a website object
 * @param aSite, a reference to a website that we will setup
 */
void generateWebsite(website & aSite)
{
    typedef char* charC;
    charC topicName = nullptr;
    charC siteURL = nullptr;
    charC siteSummary = nullptr;
    charC siteReview = nullptr;
    int siteRating;

    cout << "Please enter the topic of the website [EX Programming]: ";
   while(!getInput(topicName))
   {
        cout << "Please enter the topic of the website [EX Programming]: ";
        getInput(topicName);
   }

    cout << "Please enter the URL of the website [ LIKE https://www.google"
         << ".com ]: ";
   while(!getInput(siteURL))
   {
       cout << "Please enter the URL of the website [ LIKE https://www.google"
            << ".com ]: ";
       getInput(siteURL);
   }
    cout << "Please enter a summary of this websites content: [ Like Linked "
         <<   "Lists ]: ";
    while(!getInput(siteSummary))
    {
        cout << "Please enter a summary of this websites content: [ Like Linked "
             <<   "Lists ]: ";
        getInput(siteSummary);
    }
    cout << "Please enter a review for this website [ EX How helpful you find"
         <<  " this websites content ]: ";
    while(!getInput(siteReview))
    {
        cout << "Please enter a review for this website [ EX How helpful you find"
             <<  " this websites content ]: ";
             getInput(siteReview);
    }
    cout << "How would you rate this website on a scale of 5 [ EX 1 not very"
         <<   " helpful 5 very helpful ]: ";
    siteRating = getInteger();

    // set the website up.
    aSite.setTopic(topicName);
    aSite.setURL(siteURL);
    aSite.writeSummary(siteSummary);
    aSite.writeReview(siteReview);
    aSite.setRating(siteRating);

    if(topicName)
        delete []topicName;
    if(siteURL)
        delete []siteURL;
    if(siteSummary)
        delete [] siteSummary;
    if(siteReview)
        delete []siteReview;
    topicName = siteURL = siteSummary = siteReview = nullptr;
}



/*
 * Get character input dynamically from the user.
 */
bool getInput(char *& chars) {
    char *input = nullptr; // store the input from input stream
    char *temp = nullptr; // store a temp copy of the input each time input
    // grows
    int wordSize = 0; // the size of the word we got from input

    while (cin.good() && cin.peek() != EOF) {
        char letter = cin.get(); // grabs the current character in the input

        if (letter == '\n') {
            break;
        }

        if (!input) {
            input = new char[2];
            input[0] = letter;
            input[1] = '\0';
            wordSize = 1;
        } else {
            wordSize = strlen(input);
            // +2 so we can get the letter plus have enough space to append
            // cstrings null node terminator to the end.
            temp = new char[wordSize + 2]{0};
            strcpy(temp, input);
            delete[]input;
            input = temp;
            input[wordSize] = letter;
            input[wordSize + 1] = '\0';
        }

    }


    if(input)
    {
        chars = new char[strlen(input) + 1];
        // copy the users input into the passed in pointer.
        strcpy(chars, input);
        // get rid of our dynamic input pointer.
        if(input)
            delete[]input;
        return true;
    }
    else
    {
        cerr << "You didn't provide any input\ttry again!\n";

        return false;
    }

}


/*
 * Get validated integer input from the user. ensures that the user did in
 * fact enter a valid input, or it will keep prompting until satisfied.
 */
int getInteger()
{
    int numberIn;
    cin >> numberIn;


    while(cin.fail())
    {
        cin.clear();
        cin.ignore(101, '\n');
        cerr << "Please enter a whole number as input "
             << "(EX 100 or 379) " << endl;
        cin >> numberIn;
    }

    cin.ignore(101, '\n');
    return numberIn;
}





int main()
{
    cout << "Starting the program " << endl;
    menu();
    cout << endl << "[ Done ]\n";
}
