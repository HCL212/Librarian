#ifndef LIBRARY_CPP_INCLUDED
#define LIBRARY_CPP_INCLUDED
#include "library.h"

void Library::gatherData(string bookFilename, string acctFilename)
{
    localLibraryDatabase.getBooks(bookFilename); // populate the books
    localLibraryDatabase.getAcctData(acctFilename); // populate the users
    totalBooks = localLibraryDatabase.getNumOfBooksTotal();
    totalAccounts = localLibraryDatabase.getNumOfAcctsTotal();
    return;
}

void Library::browseBy(string userInput)
{
    if (userInput == "title" || userInput == "author" || userInput == "genre" ||
        userInput == "bookid" || userInput == "popularity")
    {
        sortHelper(userInput); // uses helper function to avoid same code for each
    }
    else
        cout << "Invalid value." << endl;

    cout << endl;
    return;
}

void Library::sortHelper(string functionName)
{
    // populates temporary vector with book pointers from the map
    vector<Book*> sortedBy = localLibraryDatabase.pullBooksToVec();
    int currentNum = 0;
    
    // sort vector of books by what user wants using sort function with 'compare'
    if (functionName == "title")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getTitle() < b->getTitle();
        }); 
    else if (functionName == "author")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getAuthor() < b->getAuthor();
        }); 
        
    else if (functionName == "genre")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getGenre() < b->getGenre();
        });         
    else if (functionName == "bookid")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getID() < b->getID();
        });         
    else if (functionName == "popularity")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getPopScore() > b->getPopScore();
        });         

    // outputs the library sorted by what user wants
    // ascending for all categories except popularity
    for (unsigned int i = 0; i < sortedBy.size(); i++)
    {
        currentNum += 1;
        cout << currentNum << ". \"" << sortedBy.at(i)->getTitle() << "\" ";
        cout << "by " << sortedBy.at(i)->getAuthor();
        cout << " (BookID# " << sortedBy.at(i)->getID() << ") ";
        cout << "[" << sortedBy.at(i)->getGenre() << "]. ";

        // if book is checked out, notify user, and vice versa
        if (sortedBy.at(i)->getStatus() == false)
            cout << "AVAILABLE." << endl;
        else
        {
            cout << "CHECKED OUT (AccountID# " << 
            sortedBy.at(i)->getIDofLastUser() << ")." << endl;
        }
    }
    return;
}

void Library::viewBook(int bookID)
{
    Book* tempBook;

    // checks if the book is in the library, if not, notify user
    if (localLibraryDatabase.checkIfBookExistsByID(bookID) == true)
        tempBook = localLibraryDatabase.accessBook(bookID);
    else
    {
        cout << "BookID#: " << bookID << " not found." << endl << endl;
        return;
    }

    // outputs details for user about the book
    cout << "Title: \"" << tempBook->getTitle() << "\"" << endl;
    cout << "Author: " << tempBook->getAuthor() << endl;
    cout << "BookID#: " << bookID << endl;
    cout << "Genre: " << tempBook->getGenre() << endl;
    cout << "Popularity Score: " << tempBook->getPopScore() << endl;
    if (tempBook->getStatus() == false)
        cout << "AVAILABLE" << endl;
    else
    {
        cout << "Borrower AccountID#: " << tempBook->getIDofLastUser() << endl;
        cout << "Due Date: " << tempBook->getDueDate() << endl;
        cout << "Times Renewed: " << tempBook->getNumOfRenews() << endl;

        if (checkIfOverdue(bookID) == true)
            cout << "OVERDUE" << endl;
    }
    cout << endl;
    return;
}

void Library::search(string findInput)
{
    // populates temporary vector with book pointers from the map
    vector<Book*> searchBy = localLibraryDatabase.pullBooksToVec();

    bool foundInVec = false;
    int numberOfBooks = 0;
    string userInput;

    // sorts the vector by title or author first before seeing if substring exists
    if (findInput == "title")
        sort (searchBy.begin(), searchBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getTitle() < b->getTitle();
        }); 
    else if (findInput == "author")
        sort (searchBy.begin(), searchBy.end(), 
        [](Book* & a, Book* & b)
        {
        return a->getAuthor() < b->getAuthor();
        });     

    // searches the vector for the substring in each Book, and outputs details if found 
    if (findInput == "title")
    {
        cout << "Enter the search phrase." << endl;
        cout << "> ";
        cin >> userInput;

        // searches the vector for the substring from user input
        for (unsigned int i = 0; i < searchBy.size(); i++)
        {
            // size_t found example taken from C++ STL
            size_t found = searchBy.at(i)->getTitle().find(userInput);

            // outputs the book details if found, otherwise notify user
            if (found != std::string::npos)
            {
                numberOfBooks += 1;
                cout << numberOfBooks << ". \"" << searchBy.at(i)->getTitle() << "\" ";
                cout << "by " << searchBy.at(i)->getAuthor();
                cout << " (BookID# " << searchBy.at(i)->getID() << ") ";
                cout << "[" << searchBy.at(i)->getGenre() << "]. ";
                if (searchBy.at(i)->getStatus() == false)
                    cout << "AVAILABLE." << endl;
                else
                {
                    cout << "CHECKED OUT (AccountID# " << 
                    searchBy.at(i)->getIDofLastUser() << ")." << endl;
                }
                foundInVec = true;
            }
        }
        if (foundInVec == false)
            cout << "No search results found." << endl;
    }
    // same function as the if statement but for authors
    else if (findInput == "author")
    {
        cout << "Enter the search phrase." << endl;
        cout << "> ";
        cin >> userInput;

        // searches temporary vector for substring from user input 
        for (unsigned int i = 0; i < searchBy.size(); i++)
        {
            size_t found = searchBy.at(i)->getAuthor().find(userInput);

            // outputs details if substring found, otherwise notify user
            if (found != std::string::npos)
            {
                numberOfBooks += 1;
                cout << numberOfBooks << ". \"" << searchBy.at(i)->getTitle() << "\" ";
                cout << "by " << searchBy.at(i)->getAuthor();
                cout << " (BookID# " << searchBy.at(i)->getID() << ") ";
                cout << "[" << searchBy.at(i)->getGenre() << "]. ";
                if (!searchBy.at(i)->getStatus())
                    cout << "AVAILABLE." << endl;
                else
                {
                    cout << "CHECKED OUT (AccountID# " << 
                    searchBy.at(i)->getIDofLastUser() << ")." << endl;
                }
                foundInVec = true;
            }
        }
        if (foundInVec == false)
            cout << "No search results found." << endl;
    }
    else
        cout << "Invalid value." << endl;

    cout << endl;
    return;
}

void Library::listAccounts(string sortBy)
{
    // populates temporary vector with account pointers from the map
    vector<Acct*> sortedBy = localLibraryDatabase.pullAcctsToVec();
    int accountNum = 0;
    
    // sort vector of books by what user wants using sort function with 'compare'
    if (sortBy == "name")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Acct* & a, Acct* & b)
        {
        return a->getName() < b->getName();
        }); 
    else if (sortBy == "accountid")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Acct* & a, Acct* & b)
        {
        return a->getID() < b->getID();
        }); 
    else if (sortBy == "checkouts")
        sort (sortedBy.begin(), sortedBy.end(), 
        [](Acct* & a, Acct* & b)
        {
        return a->getNumOfBooks() > b->getNumOfBooks();
        });        
    else
    {
        cout << "Invalid value." << endl << endl;
        return;
    }
       
    // outputs the library sorted by what user wants
    for (unsigned int i = 0; i < sortedBy.size(); i++)
    {
        accountNum += 1;
        cout << accountNum << ". " << sortedBy.at(i)->getName() << " (AccountID# ";
        cout << sortedBy.at(i)->getID() << "). ";

        // if user has books in posession, output details
        if (sortedBy.at(i)->getNumOfBooks() > 0)
        {            
            cout << sortedBy.at(i)->getNumOfBooks() << " books checked out:" << endl;
            Book* tempBook;
            int bookNum = 0;

            // pull bookID's from account "i" is currently at
            vector<int> temporaryVector = sortedBy.at(i)->pullBookIDsToVec();

            // vector holding bookID's need to be looped to output details
            for (unsigned int j = 0; j < temporaryVector.size(); j++)
            {
                cout << "\t";
                bookNum += 1;
                tempBook = localLibraryDatabase.accessBook(temporaryVector.at(j));
                
                // outputs book details
                cout << bookNum << ". \"" << tempBook->getTitle();
                cout << "\" by " << tempBook->getAuthor();
                cout << " (BookID# " << tempBook->getID();
                cout << ") [" << tempBook->getGenre() << "]." << endl;
            }
        }
        else
            cout << "No books checked out." << endl;
    }
    cout << endl;
    return;
}

void Library::viewAcct(int acctID)
{
    Acct* tempAcct;

    // checks if account is in the library, if not, notify user
    if (localLibraryDatabase.checkIfAcctExists(acctID) == true)
        tempAcct = localLibraryDatabase.accessAcct(acctID);
    else 
    {
        cout << "AccountID#: " << acctID << " not found." << endl << endl;
        return;
    }

    // outputs details for user about the account
    cout << "Name: " << tempAcct->getName() << endl;
    cout << "AccountID#: " << acctID << endl;

    // if user has any books in posession, output the book details
    if (tempAcct->getNumOfBooks() > 0)
    {
        int num = 0;
        int numOfBooksOverdue = 0;
        bool anyOverdue = false;
        cout << tempAcct->getNumOfBooks() << " books checked out";

        vector<int> tempVec = tempAcct->pullBookIDsToVec();

        // loop to check if any books are overdue
        for (unsigned int i = 0; i < tempVec.size(); i++)
        {
            if (this->checkIfOverdue(tempVec.at(i)) == true)
            {
                numOfBooksOverdue++;
                anyOverdue = true;
            }
        }

        if (anyOverdue == true)
            cout << "(" << numOfBooksOverdue << " overdue):" << endl;

        cout << endl;

        // outputs book details
        for (unsigned int i = 0; i < tempVec.size(); i++)
        {
            num++;
            Book* tempBook = localLibraryDatabase.accessBook(tempVec.at(i));
            cout << "\t" << num << "." << endl;
            cout << "\t" << "Title: \"" << tempBook->getTitle() << "\"" << endl;
            cout << "\t" << "Author: " << tempBook->getAuthor() << endl;
            cout << "\t" << "BookID#: " << tempBook->getID() << endl;
            cout << "\t" << "Genre: " << tempBook->getGenre() << endl;
            cout << "\t" << "Popularity Score: " << tempBook->getPopScore() << endl;
            
            // if book has been checked out, output additional details
            if (tempBook->getStatus() == true)
            {
                cout << "\t" << "Due Date: " << tempBook->getDueDate() << endl;
                cout << "\t" << "Times Renewed: " << tempBook->getNumOfRenews() << endl;

                if (checkIfOverdue(tempBook->getID()) == true)
                    cout << "\t" << "OVERDUE" << endl;
            }            
        }
    }
    else
        cout << "No books checked out." << endl;
    
    cout << endl;
    return;
}
void Library::checkoutBook(int acctID, int bookID)
{
    Acct* tempUser;
    Book* tempBook;

    // checks if account exists, if not, notify user
    if (localLibraryDatabase.checkIfAcctExists(acctID) == true)
        tempUser = localLibraryDatabase.accessAcct(acctID);
    else
    {
        cout << "AccountID#: " << acctID << " not found." << endl << endl;
        return;
    }

    // checks if book exists, if not, notify user
    if (localLibraryDatabase.checkIfBookExistsByID(bookID) == true)
        tempBook= localLibraryDatabase.accessBook(bookID);
    else
    {
        cout << "BookID#: " << bookID << " not found." << endl << endl;
        return;
    }

    vector<int> userBooks = tempUser->pullBookIDsToVec();
    bool anyOverdue = false;

    // loop to check if any of users books are overdue
    if (tempUser->getNumOfBooks() != 0)
    {
        for (unsigned int i = 0; i < userBooks.size(); i++)
        {
            if (this->checkIfOverdue(userBooks.at(i)) == true)
                anyOverdue = true;
        }
    }

    // if user is unable to checkout books, notify user
    // otherwise, checks out book for user, changing relevant variables
    // for the book and the user
    if (tempUser->getNumOfBooks() == 10)
        cout << "Account already has 10 books checked out." << endl;
    else if (anyOverdue == true)
        cout << "Account has books overdue." << endl;
    else if (tempBook->getStatus() == true)
        cout << "Book is already checked out." << endl;
    else if (tempUser->getNumOfBooks() < 10)
    {
        // checks if user has rented book before, if not, add 1 to the popularity score
        if (tempBook->hasUserRentedBookBefore(acctID) == false)
            tempBook->addPopScore();

        // changes the data members of the book, and adds book to user's rented bookID
        // list
        tempBook->toggleCheckedOut();
        tempBook->addUserToBook(acctID);
        tempBook->changeDueDate(time+15);
        tempBook->changeRenew(0);
        tempUser->checkOutBook(tempBook->getID());

        // output details of the book that user just checked out
        cout << "Book successfully checked out." << endl;
        cout << "Name: \"" << tempBook->getTitle() << "\"" << endl;
        cout << "Author: " << tempBook->getAuthor() << endl;
        cout << "BookID#: " << tempBook->getID() << endl;
        cout << "Genre: " << tempBook->getGenre() << endl;
        cout << "Popularity Score: " << tempBook->getPopScore() << endl;
        cout << "Due Date: " << tempBook->getDueDate() << endl;
        cout << "Times Renewed: " << tempBook->getNumOfRenews() << endl;
    }
    cout << endl;
    return;    
}

void Library::renewBooks(int acctID)
{
    Acct* tempUser;

    // checks if account exists in library, if not, notify user
    if (localLibraryDatabase.checkIfAcctExists(acctID) == true)
        tempUser = localLibraryDatabase.accessAcct(acctID);
    else
    {
        cout << "AccountID#: " << acctID << " not found." << endl << endl;
        return;
    }

    vector<int> userBooks = tempUser->pullBookIDsToVec();
    bool anyOverdue = false;

    // loop to check if any of users books are overdue
    if (tempUser->getNumOfBooks() != 0)
    {
        for (unsigned int i = 0; i < userBooks.size(); i++)
        {
            if (this->checkIfOverdue(userBooks.at(i)) == true)
                anyOverdue = true;
        }
    }

    // notify user of their status if unable to renew books
    // otherwise, renew the books for user
    if (anyOverdue == true)
        cout << "Account has books overdue." << endl;
    else if (tempUser->getNumOfBooks() == 0)
        cout << "User has no books to renew." << endl;
    else
    {
        int booksRenewed = 0;
        for (unsigned int i = 0; i < userBooks.size(); i++)
        {
            bool renewable = false;
            Book* tempBook = localLibraryDatabase.accessBook(userBooks.at(i));

            // if the book has max renews already, notify user
            // otherwise renew the book for user
            if (tempBook->getNumOfRenews() < 2)
            {
                renewable = true;
                booksRenewed++;
                tempBook->addRenew();
            }
            // outputs details of the book user just renewed
            cout << booksRenewed << " of " << tempUser->getNumOfBooks();
            cout << " books successfully renewed." << endl;
            cout << "\t" << i+1 << "." << endl;
            cout << "\t" << "Name: \"" << tempBook->getTitle() << "\"" << endl;
            cout << "\t" << "Author: " << tempBook->getAuthor() << endl;
            cout << "\t" << "BookID#: " << tempBook->getID() << endl;
            cout << "\t" << "Genre: " << tempBook->getGenre() << endl;
            cout << "\t" << "Popularity Score: " << tempBook->getPopScore() << endl;
            cout << "\t" << "Due Date: " << tempBook->getDueDate() << endl;
            cout << "\t" << "Times Renewed: " << tempBook->getNumOfRenews() << endl;
            if (renewable == true)
                cout << "\t" << "Book successfully renewed." << endl;
            else
                cout << "\t" << "Book already renewed twice." << endl;
        }
    }
    cout << endl;
    return;
}

void Library::returnBook(int bookID)
{
    Book* tempBook;
    Acct* tempAcct;

    // checks if book exists in the library, if not, notify user
    if (localLibraryDatabase.checkIfBookExistsByID(bookID) == true)
        tempBook = localLibraryDatabase.accessBook(bookID);
    else
    {
        cout << "BookID# " << bookID << " not found." << endl << endl;
        return;
    }

    bool returned = false;

    // returns book for the user if it is checked out, resetting book data members
    if (tempBook->getStatus() == true)
    {
        tempAcct = localLibraryDatabase.accessAcct(tempBook->getIDofLastUser());
        tempBook->toggleCheckedOut();
        tempBook->changeRenew(0);
        tempAcct->returnBook(tempBook->getID());
        returned = true;
    }

    // outputs details of book that was just returned
    if (returned == true)
    {
        cout << "Book successfully returned by AccountID# " << tempAcct->getID();
        if (tempBook->getDueDate() >= time)
            cout << " (on time)." << endl;
        else
        {
            int daysOverdue = time-tempBook->getDueDate();
            cout << " (overdue by " << daysOverdue << " days)." << endl;
        }
    }
    else
        cout << "Book is not currently checked out." << endl;
    cout << endl;
    return;
}

void Library::addBook(string title, string author, string genre)
{
    totalBooks += 1; // add to book total
    int ID = totalBooks;

    // if book does not exist already, add, otherwise ignore
    if (localLibraryDatabase.checkIfBookExists(title, author) == false)
        {
            localLibraryDatabase.addBook(ID, title, author, genre);
            cout << endl;
            return;
        }
    else
        cout << "Book with this title and author already exists." << endl;
    
    cout << endl;
    return;
}

void Library::removeBook(int bookID)
{
    Book* tempBook;
    Acct* tempAcct;

    // checks if book exists in the library, if not, notify user
    if (localLibraryDatabase.checkIfBookExistsByID(bookID) == true)
        tempBook = localLibraryDatabase.accessBook(bookID);
    else
    {     
        cout << "BookID# " << bookID << " not found." << endl << endl;
        return;
    }

    // if book is checked out, force return the book
    if (tempBook->getStatus() == true)
    {
        tempAcct = localLibraryDatabase.accessAcct(tempBook->getIDofLastUser());
        tempAcct->returnBook(tempBook->getID());

        cout << "Force returning book from AccountID# " << tempAcct->getID() << ".";
        cout << endl << "\"" << tempBook->getTitle() << "\"" << " by ";
        cout << tempBook->getAuthor() << " successfully removed." << endl;
    }
    else if (tempBook->getStatus() == false)
    {
        cout << "\"" << tempBook->getTitle() << "\"" << " by ";
        cout << tempBook->getAuthor() << " successfully removed." << endl;
    }

    // erase the book pointer from the map, and delete the pointer itself
    localLibraryDatabase.eraseBook(tempBook->getID());
    delete tempBook;

    cout << endl;
}

void Library::addAccount(string username)
{
    totalAccounts += 1; // add to account total
    int ID = totalAccounts;
    localLibraryDatabase.addUser(username, ID); // create user
    cout << endl;
    return;
}

void Library::removeAccount(int acctID)
{
    Acct* tempAcct;

    // checks if account exists in the library, if not, notify user
    if (localLibraryDatabase.checkIfAcctExists(acctID) == true)
        tempAcct = localLibraryDatabase.accessAcct(acctID);
    else
    {
    cout << "AccountID# " << acctID << " not found." << endl << endl;
        return;
    }

    // if user has any books in their position, force return them
    if (tempAcct->getNumOfBooks() > 0)
    {
        vector<int> booksHeld = tempAcct->pullBookIDsToVec();
        for (unsigned int i = 0; i < booksHeld.size(); i++)
        {
            this->returnBook(booksHeld.at(i));
        }
    }

    // erase the account pointer from the map, and delete the pointer itself
    localLibraryDatabase.eraseAcct(tempAcct->getID());
    delete tempAcct;

    cout << tempAcct->getName() << "'s account successfully removed." << endl << endl;
    return;
}

void Library::system()
{
    // pulls books and accounts into temporary vectors
    vector<Book*> tempBookList = localLibraryDatabase.pullBooksToVec();
    vector<Acct*> tempAcctList = localLibraryDatabase.pullAcctsToVec();
    int numOfOverdueBooks = 0;
    int numOfOverdueAccts = 0;

    // iterate through the book vector and determine how many are overdue
    for (unsigned int i = 0; i < tempBookList.size(); i++)
    {
        if (tempBookList.at(i)->getDueDate() < time && 
            tempBookList.at(i)->getDueDate() != 0)
            numOfOverdueBooks++;
    }

    // iterate through the account vector and determine how many accounts are overdue
    for (unsigned int i = 0; i < tempAcctList.size(); i++)
    {
        vector<int> userBooks = tempAcctList.at(i)->pullBookIDsToVec();

        // initialize bool as false for each new user we check
        bool anyBookForUserOverdue = false;
        for (unsigned int i = 0; i < userBooks.size(); i++)
        {
            // iterates through user's books and check if any overdue
            if (this->checkIfOverdue(userBooks.at(i)) == true)
                anyBookForUserOverdue = true;
        }
        // if account has at least one book overdue, iterate the # of accts overdue
        if (anyBookForUserOverdue == true)
            numOfOverdueAccts++;
    }

    // output system details for user
    cout << "System time: " << time << "." << endl;
    cout << "Number of books: " << localLibraryDatabase.getNumOfBooksTotal() << "." 
        << endl;
    cout << "Number of overdue books: " << numOfOverdueBooks << "." << endl;
    cout << "Number of accounts: " << localLibraryDatabase.getNumOfAcctsTotal() << ".";
    cout << endl;
    cout << "Number of overdue accounts: " << numOfOverdueAccts << "." << endl << endl;

    return;
}

void Library::timeTravel(int daysTraveled)
{
    if (daysTraveled > 0)
    {
        cout << "Travelled " << daysTraveled << " days through time (";
        cout << time << " --> " << time+daysTraveled << ")." << endl;
        time += daysTraveled;
    }
    else
        cout << "CANNOT TRAVEL BACK IN TIME" << endl;

    cout << endl;
    return;
}

void Library::outputData(string books, string accounts)
{
    vector<Book*> tempBookList = localLibraryDatabase.pullBooksToVec();
    vector<Acct*> tempAcctList = localLibraryDatabase.pullAcctsToVec();

    ofstream outputAccts;
    outputAccts.open(accounts);
    if (!outputAccts.is_open())
    {
        cout << "Error" << endl;
        return;
    }

    // sort the book and acct vectors by ID
    sort (tempBookList.begin(), tempBookList.end(), 
    [](Book* & a, Book* & b)
    {
    return a->getID() < b->getID();
    });  

    sort (tempAcctList.begin(), tempAcctList.end(), 
    [](Acct* & a, Acct* & b)
    {
    return a->getID() < b->getID();
    }); 

    // outputs # of accounts to new file first
    outputAccts << tempAcctList.size() << endl;

    // iterate through the accounts and output them to new file
    for (unsigned int i = 0; i < tempAcctList.size(); i++)
    {
        outputAccts << tempAcctList.at(i)->getID() << "|";
        outputAccts << tempAcctList.at(i)->getName() << "|";
        outputAccts << tempAcctList.at(i)->getNumOfBooks() << endl;
        
        // if accounts have any books, output the book details to new file
        if (tempAcctList.at(i)->getNumOfBooks() != 0)
        {
            vector<int> booksUserHas = tempAcctList.at(i)->pullBookIDsToVec();
            for (unsigned int j = 0; j < booksUserHas.size(); j++)
            {
                Book* tempBook = localLibraryDatabase.accessBook(booksUserHas.at(j));
                outputAccts << tempBook->getID() << "|";
                outputAccts << tempBook->getDueDate() << "|";
                outputAccts << tempBook->getNumOfRenews() << endl;
            }
        }
    }

    // close the file
    outputAccts.close();

    // exporting books code
    ofstream outputBooks;
    outputBooks.open(books);
    if (!outputBooks.is_open())
    {
        cout << "Error" << endl;
        return;
    }

    // output # of books to new file
    outputBooks << tempBookList.size() << endl;

    // iterates through the books, and outputs the details of each book to new file
    for (unsigned int i = 0; i < tempBookList.size(); i++)
    {
        outputBooks << tempBookList.at(i)->getID() << "|";
        outputBooks << tempBookList.at(i)->getTitle() << "|";
        outputBooks << tempBookList.at(i)->getAuthor() << "|";
        outputBooks << tempBookList.at(i)->getGenre() << "|";
        outputBooks << tempBookList.at(i)->getPopScore() << endl;
    }
    cout << endl;

    // close the file
    outputBooks.close();
    return;
}

void Library::displayHelp()
{
    cout << "BROWSE: Provides the status of all the books." << endl;
    cout << "BOOK: Provides the status of a specific book." << endl;
    cout << "SEARCH: Searches for all books with a key-phrase in the title or author." << endl;
    cout << "ACCOUNTS: Provides account snapshots for all user accounts." << endl;
    cout << "ACCOUNT: Provides an account snapshot for a specific user account." << endl;
    cout << "CHECKOUT: Checks a book out to a user account." << endl;
    cout << "RENEW: Renews a checked out book. (Up to two times allowed)" << endl;
    cout << "RETURN: Returns a checked out book." << endl;
    cout << "RECOMMEND: Generates a list of recommended books for a given user." << endl;
    cout << "ADDB: Adds a new book to the library." << endl;
    cout << "REMOVEB: Removes a specific book from the library." << endl;
    cout << "ADDA: Creates a new user account in the library." << endl;
    cout << "REMOVEA: Removes a specific user account from the library." << endl;
    cout << "SYSTEM: Provides diagnostic information about the system." << endl;
    cout << "TIME: Fast forwards the system time by a specified number of days." << endl;
    cout << "EXPORT: Exports the library’s books and accounts to files." << endl;
    cout << "HELP: Displays this help menu." << endl;
    cout << "EXIT: Exits the program." << endl << endl;  
    return;
}

bool Library::checkIfOverdue(int bookID)
{
    if (localLibraryDatabase.accessBook(bookID)->getDueDate() < time)
        return true;
    else
        return false;
}

#endif
