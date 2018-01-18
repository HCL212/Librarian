#ifndef BOOK_CPP_INCLUDED
#define BOOK_CPP_INCLUDED
#include "book.h"

void Book::toggleCheckedOut()
{
    if (checkedOut == false)
        checkedOut = true;
    else
        checkedOut = false;
    return;
}

void Book::addUserToBook(int id)
{
    idsOfUsersWhoReadBook.push_back(id);
    return;
}

void Book::changeDueDate(int a)
{
    dueDate = a;
    return;
}

void Book::changeRenew(int b)
{
    timesRenewed = b;
    return;
}

void Book::addRenew()
{
    timesRenewed += 1;
    dueDate += 5;
    return;
}

void Book::addPopScore()
{
    popScore++;
    return;
}

int Book::getPopScore()
{
    return popScore;
}

int Book::getID()
{
    return ID;
}

int Book::getDueDate()
{
    return dueDate;
}

int Book::getNumOfRenews()
{
    return timesRenewed;
}

int Book::getIDofLastUser()
{
    return idsOfUsersWhoReadBook.back();
}

string Book::getTitle()
{
    return bookTitle;
}

string Book::getAuthor()
{
    return bookAuthor;
}

string Book::getGenre()
{
    return bookGenre;
}

bool Book::getStatus()
{
    return checkedOut;
}

bool Book::hasUserRentedBookBefore(int userID)
{
    bool found = false;

    // iterate through the vector of ID's and determine if user ever rented book before
    for (unsigned int i = 0; i < idsOfUsersWhoReadBook.size(); i++)
    {
        // if user ID is found, change bool to true
        if (idsOfUsersWhoReadBook.at(i) == userID)
            found = true;
    }
    return found;
}

#endif
