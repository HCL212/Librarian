#ifndef STACKOVERDUECOORDINATOR_H_INCLUDED
#define STACKOVERDUECOORDINATOR_H_INCLUDED
#include "library.h"

class Coordinator{
public:
    void startProgram(string bookFile, string acctFile); // take user inputs and populate
    void menu(); // user menu to operate the program
private:
    Library localLibrary;
};

#endif
