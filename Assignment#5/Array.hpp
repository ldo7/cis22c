/*
 CIS22B
 02/28/23
 Assignment #5

 This program declares the function headers and members of the Array object.
*/
#ifndef Array_hpp
#define Array_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

class Array {
private:
    int size = 0;
    int* ptr;
    static int numElem;
    static bool isSrand;
public:
    Array ();                        //default
    Array (int);                     //overloaded
    Array (const Array&);            //copy
    int& operator[] (int) const;              //subscript
    Array& operator= (const Array&);          //assignment
    bool operator== (const Array&) const;     //equality
    bool operator< (const Array&) const;      //less than
    Array& operator! ();
    int operator* () const;                  //smallest element
    Array& operator+= (const Array&);   //merge
    Array operator++ (int);             //incr. postfix
    Array& operator-- ();               //decr. prefix
    friend ostream& operator<< (ostream&, const Array&);
    ~Array();
    
    int getSize() const;
    static int getNumberOfElements();
};

#endif /* Array_hpp */
