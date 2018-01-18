#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include "acct.h"

//book object class
class Book{
public:
    Book(int idNum, string title, string author, string genre, int popScoreNum)
    {
        ID = idNum;
        bookTitle = title;
        bookAuthor = author;
        bookGenre = genre;
        popScore = popScoreNum;
    }
    void toggleCheckedOut(); // switches between true/false for checked out variable
    void addUserToBook(int id); // adds userID to list of people who have had the book
    void changeDueDate(int a); // change due date
    void changeRenew(int b); // change timesRenewed variable
    void addRenew(); // renew book
    void addPopScore(); // add 1 to popularity score
    int getPopScore(); // retrieve popularity score
    int getID(); // retrieve book ID
    int getDueDate(); // retrieve due date
    int getNumOfRenews(); // retrieve # of times renewed
    int getIDofLastUser(); // get ID of last person that has/had the book
    string getTitle(); // retrieve title
    string getAuthor(); // retrieve author
    string getGenre(); // retrive genre
    bool getStatus(); // returns checkedOut bool
    bool hasUserRentedBookBefore(int userID); // determines if the userid has ever rented
private:
    int ID = 0;
    int popScore = 0;
    int dueDate = 0;
    int timesRenewed = 0;
    string bookTitle = "";
    string bookAuthor = "";
    string bookGenre = "";
    // stores id of all users who rented book
    // o(1) to check last user ID, o(n) to search all user ID's
    vector<int> idsOfUsersWhoReadBook; 
    bool checkedOut = false;
};


#endif

