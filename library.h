#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include "databaseManager.h"

class Library{
public:
    void gatherData(string bookFilename, string acctFilename); // populates library
    void browseBy(string userInput); // let user browse a sorted library
    void sortHelper(string functionName); // helper function for sorting
    void viewBook(int bookID); // view full description of a book
    void search(string findInput); // searches library for author or book
    void listAccounts(string sortBy); // list sorted accounts
    void viewAcct(int acctID); // view account details
    void checkoutBook(int acctID, int bookID); // checks out book for user
    void renewBooks(int acctID); // renews valid books for user
    void returnBook(int bookID); // returns a book to the system
    void addBook(string title, string author, string genre); // add book to system
    void removeBook(int bookID); // removes book from system
    void addAccount(string username); // add an account to the system
    void removeAccount(int acctID); // removes account from system
    void system(); // display system statistics
    void timeTravel(int daysTraveled); // accepts positive integer to time travel
    void outputData(string books, string accounts); // exports data into a new file
    void displayHelp(); // displays all options to user
    bool checkIfOverdue(int bookID); // check if book is overdue
private:
    DatabaseManager localLibraryDatabase;
    int time = 1; // time starts at 1 on program startup
    int totalBooks = 0; // total # of books ever (including deleted)
    int totalAccounts = 0; // total # of accts (including deleted)
};

#endif
