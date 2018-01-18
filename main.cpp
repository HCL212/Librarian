#include "stackOverdueCoordinator.h"

int main(int argc, char* argv[]){

    string bookFile;
    string acctFile;

    if (argc > 1)
        bookFile = argv[1];
    if (argc > 2)
        acctFile = argv[2];

    Coordinator StackOverdue;
    StackOverdue.startProgram(bookFile, acctFile);
    StackOverdue.menu();

}
