#ifndef DATABASEMANAGER_H_INCLUDED
#define DATABASEMANAGER_H_INCLUDED
#include "book.h"

class DatabaseManager{
public:
    void getAcctData(string acctData); //  read from input file to fill out users
    void getBooks(string bookData); // read from input file to fill out books
    void addUser(string name, int newID); // add a user to the database
    void addBook(int newID, string title, string author, string genre); // add book
    void eraseBook(int bookID); // erases book from unordered map
    void eraseAcct(int acctID); // erases acct from unordered map
    int getNumOfBooksTotal(); // num of books in library system
    int getNumOfAcctsTotal(); // num of accts in library system
    bool checkIfBookExists(string title, string author); // searches by title/author
    bool checkIfBookExistsByID(int bookID); // searches by ID
    bool checkIfAcctExists(int acctID); // checks if acct exists
    vector<Book*> pullBooksToVec(); // pull books from map into a vector
    vector<Acct*> pullAcctsToVec(); // pull accounts from map into a vector
    Book* accessBook(int id); // locate and access book
    Acct* accessAcct(int id); // locate and access account
private:
    // unordered_map o(1) for most operations
    unordered_map <int, Acct*> AcctDatabase;
    unordered_map <int, Book*> BookLibrary;
};


#endif
