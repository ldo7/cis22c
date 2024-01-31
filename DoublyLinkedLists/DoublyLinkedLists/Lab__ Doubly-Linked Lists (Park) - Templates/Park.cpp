// Implementation file for the Park class
// Written By: A. Student
// Reviewed & Modified by: <Write your name here>
// IDE: Xcode

#include <iostream>
#include <iomanip>
#include <string>

#include "Park.h"

using namespace std;

// **************************************************
// Constructor
// **************************************************
Park::Park()
{
    code = "";
    state = "";
    name = "";
    description = "";
    year = -1;
}

// **************************************************
// Overloaded Constructor
// **************************************************
Park::Park(string cd, string st, string nm, string dsc, int yr)
{
    code = cd;
    state = st;
    name = nm;
    description = dsc;
    year = yr;
}

// ***********************************************************
// Displays the values of a Park object member variables
// on one line (horizontal display)
// ***********************************************************
void Park::hDdisplay() const
{
    cout << code  << " ";
    cout << state << " ";
    cout << year  << " ";
    cout << name << " ";
    //cout << "(" << description << ")";
    cout << endl;
}

// ***********************************************************
// Displays the values of a Park object member variables
// one per line (vertical display)
// ***********************************************************
void Park::vDisplay() const
{
    cout << name << endl;
    cout << description << endl;
    cout << state << endl;
    cout << year << endl;
    
}

// overloaded operators
/* Write your code here to define the following oveloaded operator:
    - the stream insertion operator ( << )
 */
 