# Assignment 3 - StackOverdue

## Background  
Most libraries run on ancient systems/code.  StackOverdue is a efficient easy to use sytem that any school or public library can use to make their lives much easier.  Loaded with various data structures and a combination of features (some to be patched in later), StackOverdue blows the competition out of the water.  
  
## Compilation/Execution Instructions  
Compile program with: **make**  
The program can take no arguments, one argument, or two arguments following below format:  
**./StackoverDue (book file name) (account file name)**  
  
The ordering of these arguments are final, both files are optional, but you cannot provide a account file without a book file, but you CAN provide a book file without a account file.  
  
## Class Functionality  
*The following inputs have to be in all caps*  
BROWSE: Provides the status of all the books.  
BOOK: Provides the status of a specific book.  
SEARCH: Searches for all books with a key-phrase in the title or author.  
ACCOUNTS: Provides account snapshots for all user accounts.  
ACCOUNT: Provides an account snapshot for a specific user account.  
CHECKOUT: Checks a book out to a user account.  
RENEW: Renews a checked out book. (Up to two times allowed)  
RETURN: Returns a checked out book.  
RECOMMEND: Generates a list of recommended books for a given user.  
ADDB: Adds a new book to the library.  
REMOVEB: Removes a specific book from the library.  
ADDA: Creates a new user account in the library.  
REMOVEA: Removes a specific user account from the library.  
SYSTEM: Provides diagnostic information about the system.  
TIME: Fast forwards the system time by a specified number of days.  
EXPORT: Exports the library’s books and accounts to files.  
HELP: Displays this help menu.  
EXIT: Exits the program.  
  
## Design Description  
*Note: This implementation uses only the C++ STL*  
  
### Book  
Book is a small class with getters and setters for the data members, such as the author, title, genre, popularity score and accounts who have held the book at one time or another. Book holds a vector of int's that hold the ID's of any users who have the book.  
  
### Account
Account is another small class with getters and setters for data members similar to book. User can see what books the account currently has, their name, id number, etc. Account has a list of int's that hold id's of the book's the user currently has.  The list is easy to add/remove any id's when a user returns or checks out a book without having to resize.  
  
### Database Manager  
The database manager holds two unordered maps for all the Books and Accounts in the library. The keys for both unordered maps are the id's of the accounts and books respectively matched against pointers to the accounts and books (which are the values). The map is o(1) on average for all operations which makes it quick and easy to find and modify any book or account when needed. The database manager relies on the Book and Account classes.  
  
### Library
The library handles the bulk of the work in this program using the database manager to help offload some of the work and to provide more efficient use of the functions.  All the functionality of this program is handled by the library.  The library relies on the database manager class in order to access and modify any books and accounts in the library.  
  
### Coordinator
The coordinator is a simple class that takes parameters to populate the library when the program first starts. It also starts the menu the user sees in order to use the program. The coordinator relies on the library class in order to be able to do anything within the program.
