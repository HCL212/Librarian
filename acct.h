#ifndef ACCT_H_INCLUDED
#define ACCT_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Acct{
public:
    Acct(int idNum, string name)
    {
        ID = idNum;
        acctName = name;
    }
    int getID(); // retrieve ID
    int getNumOfBooks(); // retrieve # of books user currently has
    string getName(); // retrieve acct "name"
    void returnBook(int bookID); // returns book
    void checkOutBook(int bookID); // checks out book for user
    vector<int> pullBookIDsToVec(); // pulls from list into a vector
private:
    int ID = 0;
    int checkedOutBooks = 0; // max = 10
    string acctName = "";
    list<int> booksHeld; // o(1) to add, o(n) to remove
};

#endif
