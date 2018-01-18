#ifndef STACKOVERDUECOORDINATOR_CPP_INCLUDED
#define STACKOVERDUECOORDINATOR_CPP_INCLUDED
#include "stackOverdueCoordinator.h"

void Coordinator::startProgram(string bookFile, string acctFile)
{
    localLibrary.gatherData(bookFile, acctFile); // populate the library with user files
}

void Coordinator::menu()
{
    string userChoice;
    cout << "> ";
    cin >> userChoice;

    // as long as user does not enter "EXIT", user can operate the program's
    // following functions
    while (userChoice != "EXIT")
    {
        if (userChoice == "BROWSE")
        {
            string userInput;
            cout << "Enter the criteria to sort by. ";
            cout << "(title/author/genre/bookid/popularity)" << endl;
            cout << "> ";

            // ignores up to 200 inputs in the buffer, ignoring spaces
            cin.ignore(200, '\n');
            getline(cin,userInput);

            localLibrary.browseBy(userInput);

            cout << "> ";
            cin >> userChoice; 
        }
        else if (userChoice == "BOOK")
        {
            int id;
            cout << "Enter the book id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> id;

            // makes sure user enters valid input, if not, notify them and ask again
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.viewBook(id);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "SEARCH")
        {
            string userInput;
            cout << "Enter the criteria to search by. (title/author)" << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            getline(cin,userInput);

            localLibrary.search(userInput);            

            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "ACCOUNTS")
        {
            string userInput;
            cout << "Enter the criteria to sort by. (name/accountid/checkouts)" << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            getline(cin,userInput);

            localLibrary.listAccounts(userInput);

            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "ACCOUNT")
        {
            int id;
            cout << "Enter the account id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> id;

            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.viewAcct(id); 

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;            
        }
        else if (userChoice == "CHECKOUT")
        {
            int acctID;
            int bookID;
            cin.ignore(200, '\n');

            cout << "Enter the account id." << endl;
            cout << "> ";
            cin >> acctID;

            cout << "Enter the book id." << endl;
            cout << "> ";
            cin >> bookID;
     
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.checkoutBook(acctID, bookID);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "RENEW")
        {
            int acctID;

            cout << "Enter the account id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> acctID;

            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.renewBooks(acctID);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "RETURN")
        {
            int bookID;
            
            cout << "Enter the book id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> bookID;
            
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.returnBook(bookID);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "RECOMMEND")
        {
            cout << "This feature has not been enabled." << endl;

            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "ADDB")
        {
            string bookName;
            string bookAuthor;
            string bookGenre;
            
            cout << "Enter the new book's title." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            getline(cin,bookName);

            cout << "Enter the new book's author." << endl;
            cout << "> ";
            getline(cin,bookAuthor);

            cout << "Enter the new book's genre." << endl;
            cout << "> ";
            getline(cin,bookGenre);

            localLibrary.addBook(bookName, bookAuthor, bookGenre);
                
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "REMOVEB")
        {
            int bookID;

            cout << "Enter the book id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> bookID;

            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.removeBook(bookID);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "ADDA")
        {
            string username;
            cout << "Enter the user's name." << endl;
            cout << "> ";

            cin.ignore(200, '\n');    
            getline(cin,username);
            
            localLibrary.addAccount(username);
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "REMOVEA")
        {
            int acctID;

            cout << "Enter the account id." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> acctID;

            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.removeAccount(acctID);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "SYSTEM")
        {
            localLibrary.system();
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "TIME")
        {
            int days;
            cout << "Enter the number of days to time travel." << endl;
            cout << "> ";

            cin.ignore(200, '\n');
            cin >> days;
            
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid value." << endl << endl;
            }
            else
                localLibrary.timeTravel(days);

            cin.ignore(200, '\n');
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "EXPORT")
        {
            string bookFile;
            string accountFile;
            
            cout << "Enter the name of the books file. (This may overwrite a file)";
            cout << endl;
            cout << "> ";
            
            cin.ignore(200, '\n');
            getline(cin,bookFile);

            cout << "Enter the name of the accounts file. (This may overwrite a file)";
            cout << endl;
            cout << "> ";
            getline(cin,accountFile);

            localLibrary.outputData(bookFile, accountFile);
            cout << "> ";
            cin >> userChoice;
        }
        else if (userChoice == "HELP")
        {
            string userInput;

            localLibrary.displayHelp();
            cout << "> ";
            cin >> userChoice;
        }
        else
        {
            cout << "Invalid command." << endl << endl;
            cout << "> ";
            cin >> userChoice;
        }
    }
    if (userChoice == "EXIT")
    {
        cout << "Thank you for using StackOverdue!" << endl;
        return;
    }
}

#endif
