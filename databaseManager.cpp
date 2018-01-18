#ifndef DATABASEMANAGER_CPP_INCLUDED
#define DATABASEMANAGER_CPP_INCLUDED
#include "databaseManager.h"

void DatabaseManager::getAcctData(string acctData)
{
    int userID; // userID variable needs to be stored for the "book lines" after
    string acctInfo;

    ifstream inputfile;
    inputfile.open(acctData); 

    // if no valid acct file provided, tell user
    if (!inputfile.is_open())
    {
        cout << "Could not find file \"" << acctData << "\". Skipping." << endl;
        return;
    }
    else
        cout << "Loading accounts from \"" << acctData << "\"." << endl;

    // ignore first line (could be used to reserve data structure space)
    getline (inputfile,acctInfo);

    while (getline(inputfile,acctInfo))
    {
        // if > 8, since the lines with less than 8 lines are all 'usually'
        // for the books, could encounter errors here depending on line length
        if (acctInfo.size() > 8)
        {
            unsigned int i = 0;
            string newInfo;

            int acctID;
            string acctName;
            vector<string> tempAcctInfo;

            // parsing the acctInfo string into separate strings
            // and storing in the tempAcctInfo vector
            while (i < acctInfo.size())
            {
                if (acctInfo[i] == '|')
                    i++;
                while (acctInfo[i] != '|' && i < acctInfo.size())
                {
                    newInfo += acctInfo[i];
                    i++;
                }

                // each new string gets pushed back onto a temporary vector
                tempAcctInfo.push_back(newInfo);

                // resets newInfo string for next string
                newInfo = "";
            }

            // pulls information from temp vector for constructor variables
            acctID = stoi(tempAcctInfo[0]);
            acctName = tempAcctInfo[1];

            // creates an account for the database
            Acct* currAcct = new Acct(acctID, acctName);

            // store new account into map with ID matched with account
            AcctDatabase.insert({acctID,currAcct});

            // clear the temporary vector for next line
            tempAcctInfo.clear();
            
            // user ID needed to set book current owner
            userID = acctID;
        }
        else
        {
            unsigned int i = 0;
            string acctBookInfo;

            int bookID;
            int dueDate;
            int timesRenewed;
            vector<string> acctWithBook;

            // loop to parse the string into smaller strings and pushes onto
            // temporary vector
            while (i < acctInfo.size())
            {
                if (acctInfo[i] == '|')
                    i++;
                while (acctInfo[i] != '|' && i < acctInfo.size())
                {
                    acctBookInfo += acctInfo[i];
                    i++;
                }

                // push info to temporary vector
                acctWithBook.push_back(acctBookInfo);

                // reset to empty string for next use
                acctBookInfo = "";
            }

            // pull data from temp vector for variables
            bookID = stoi(acctWithBook[0]);
            dueDate = stoi(acctWithBook[1]);
            timesRenewed = stoi(acctWithBook[2]);

            // checks if book is in library, if not, do nothing and notify user
            if (BookLibrary.find(bookID) != BookLibrary.end())
            {
                // search for book in database and populate with information
                BookLibrary.at(bookID)->changeDueDate(dueDate);
                BookLibrary.at(bookID)->changeRenew(timesRenewed);
                BookLibrary.at(bookID)->addUserToBook(userID);
                BookLibrary.at(bookID)->toggleCheckedOut();
                BookLibrary.at(bookID)->addPopScore();

                // search for acct in databse and store books held in acct
                AcctDatabase.at(userID)->checkOutBook(bookID);
            }
            else
                cout << "Could not find library book with ID# " << bookID << "." << endl;
            
            // clear temporary vector for next line
            acctWithBook.clear();
        }
    }

    // close the file
    inputfile.close();
return;
}

void DatabaseManager::getBooks(string bookData)
{
    string bookInfo;
    ifstream inputfile;
    inputfile.open(bookData); 

    // if no valid book file provided, tell user
    if (!inputfile.is_open())
    {
        cout << "Could not find file \"" << bookData << "\". Skipping." << endl;
        return;
    }
    else
        cout << "Loading books from \"" << bookData << "\"." << endl;

    // ignore first line (could be used to reserve data structure space)
    getline (inputfile,bookInfo);

    while (getline(inputfile,bookInfo))
    {        
        unsigned int i = 0;
        int newID;
        int newPopScore;
        string newInfo;
        string newTitle;
        string newAuthor;
        string newGenre;
        vector<string> tempBookInfo;
        
        // parse the line from input file into relevant book information
        // and puts them in a temporary vector
        while (i < bookInfo.size())
        {
            if (bookInfo[i] == '|')
                i++;
            while (bookInfo[i] != '|' && i < bookInfo.size())
            {
                newInfo += bookInfo[i];
                i++;
            }
            
            // each new string gets pushed back onto a vector
            tempBookInfo.push_back(newInfo);

            // resets string to empty for next use
            newInfo = ""; 
        }  

        // pulling information from vector into variables
        newID = stoi(tempBookInfo[0]);
        newTitle = tempBookInfo[1];
        newAuthor = tempBookInfo[2];
        newGenre = tempBookInfo[3];
        newPopScore = stoi(tempBookInfo[4]);

        // creates a book into the library
        Book* currBook = new Book(newID, newTitle, newAuthor, newGenre, newPopScore);

        // store new book into a map with ID matched with a pointer to the book itself
        BookLibrary.insert({newID,currBook});
        
        // clearing vector information for next use
        tempBookInfo.clear();
    }

    // close the file
    inputfile.close();
return;
}

void DatabaseManager::addUser(string acctName, int newID)
{
    // creates a pointer to a new account created by user input
    Acct* currAcct = new Acct(newID, acctName);

    // add new account to database
    AcctDatabase.insert({newID,currAcct});

    cout << "AccountID# " << newID << " successfully created." << endl;
    return;
}

void DatabaseManager::addBook(int newID, string title, string author, string genre)
{
    // book has no popularity score to start with
    int popScore = 0;

    // creates a pointer to a new book created by user input
    Book* currBook = new Book(newID, title, author, genre, popScore);

    // add new book to database
    BookLibrary.insert({newID,currBook});

    cout << "BookID#" << newID << " successfully created." << endl;
    return;
}

void DatabaseManager::eraseBook(int bookID)
{
    BookLibrary.erase(bookID);
    return;
}

void DatabaseManager::eraseAcct(int acctID)
{
    AcctDatabase.erase(acctID);
    return;
}

int DatabaseManager::getNumOfBooksTotal()
{
    return BookLibrary.size();
}

int DatabaseManager::getNumOfAcctsTotal()
{
    return AcctDatabase.size();
}

bool DatabaseManager::checkIfBookExists(string title, string author)
{
    bool found = false;

    // iterate through the map and check if author and title match
    // if found, change bool to true
    for (auto it = BookLibrary.begin(); it != BookLibrary.end(); ++it)
    {
        if (it->second->getTitle() == title && it->second->getAuthor() == author)
            found = true;
    }
    return found;
}

bool DatabaseManager::checkIfBookExistsByID(int bookID)
{
    bool found = false;

    // iterate through the map and check if id matches
    // if found, change bool to true
    for (auto it = BookLibrary.begin(); it != BookLibrary.end(); ++it)
    {
        if (it->second->getID() == bookID)
            found = true;
    }
    return found;
}

bool DatabaseManager::checkIfAcctExists(int acctID)
{
    bool found = false;

    // iterate through the map and check if account id matches
    // if found, change bool to true
    for (auto it = AcctDatabase.begin(); it != AcctDatabase.end(); ++it)
    {
        if (it->second->getID() == acctID)
            found = true;
    }
    return found;
}

vector<Book*> DatabaseManager::pullBooksToVec()
{
    vector<Book*> vecOfBooks;

    // iterate through the map and pushes everything onto a vector
    for (auto it = BookLibrary.begin(); it != BookLibrary.end(); ++it)
        vecOfBooks.push_back(it->second);

    return vecOfBooks;
}

vector<Acct*> DatabaseManager::pullAcctsToVec()
{
    vector<Acct*> vecOfAccts;

    //iterate through the map and pushes everything onto a vector
    for (auto it = AcctDatabase.begin(); it != AcctDatabase.end(); ++it)
        vecOfAccts.push_back(it->second);

    return vecOfAccts;
}

Book* DatabaseManager::accessBook(int id)
{
    Book* bookWanted;

    // finds book by id, o(1)
    // if found, pass pointer to bookWanted and return to user
    auto it = BookLibrary.find(id);
    if (it == BookLibrary.end())
        cout << "BookID# " << id << " not found." << endl << endl;
    else
        bookWanted = it->second;
        
    return bookWanted;
}

Acct* DatabaseManager::accessAcct(int id)
{
    Acct* acctWanted;

    // finds acct by id, o(1)
    // if found, pass pointer to acctWanted and return to user
    auto it = AcctDatabase.find(id);
    if (it == AcctDatabase.end())
        cout << "AccountID# " << id << " not found." << endl << endl;
    else
        acctWanted = it->second;

    return acctWanted;
}

#endif
