// Specification file for the ListNode class
// Written by: A. Student
// Reviewed & Modified by: <Write your name here>
// IDE: 

#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
//#include "Park.h"
// ^^^  not included here anymore

template <class T>
class ListNode
{
private:
    T data;      // store data
    ListNode *forw;    // a pointer to the next node in the list
    ListNode *back;    // a pointer to the previous node in the list
public:
    //Constructor
    ListNode(){forw = back = NULL;}
    ListNode(const T &dataIn, ListNode *forw = NULL, ListNode *back = NULL){ data = dataIn;}
    
    // setters

    // getters

};


#endif
