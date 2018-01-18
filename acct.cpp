#ifndef ACCT_CPP_INCLUDED
#define ACCT_CPP_INCLUDED
#include "acct.h"

int Acct::getID()
{
    return ID;
}

int Acct::getNumOfBooks()
{
    return checkedOutBooks;
}

string Acct::getName()
{
    return acctName;
}

void Acct::returnBook(int bookID)
{
    checkedOutBooks--;
    booksHeld.remove(bookID);
}

void Acct::checkOutBook(int bookID)
{
    checkedOutBooks++;
    booksHeld.push_back(bookID);
}

vector<int> Acct::pullBookIDsToVec()
{
    vector<int> tempVec;
    
    //iterate through the list and pushes everything onto a vector
    for (auto it = booksHeld.begin(); it != booksHeld.end(); ++it)
        tempVec.push_back(*it);

    return tempVec;
}

#endif
