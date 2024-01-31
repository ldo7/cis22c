// Implementation file for the Park class
// Written By: A. Student
// Modified by:
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

// Friend Functions Definitions

// ***********************************************************
// hDisplay
// Displays code, state, and year data members of a Park object
// on one line (horizontal display)
// ***********************************************************
void hDisplay(const Park &item)
{
    cout << item.code  << "  ";
    cout << item.state << "  ";
    cout << item.year  << "  ";
    cout << endl;
}

// ***********************************************************
// vDisplay
// Displays name, description, state, and year of a Park object
// one per line (vertical display)
// ***********************************************************
void vDisplay (const Park &item)
{
    cout << "       Name: " << item.name << endl;
    cout << "Description: " << item.description << endl;
    cout << "      State: " << item.state << endl;
    cout << "       Year: " << item.year << endl;
}

// ***********************************************************
// iDisplay
// on one line, including the level number and
// ".." for each indentation level
// ***********************************************************
void iDisplay(const Park &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.code << endl;
}

// ***********************************************************
// kDisplay
// Displays the key: code of a Park object
// on one line (key display)
// ***********************************************************
void kDisplay(const Park &item){
    cout << item.code << endl;
}
