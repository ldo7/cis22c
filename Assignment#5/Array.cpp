/*
 CIS22B
 02/28/23
 Assignment #5
 
 This program defines the functions and static members of an Array object
 and overloads binary and unary operators.
*/
#include <iostream>
#include "Array.hpp"
using namespace std;

//static definitions
int Array::numElem = 0;
bool Array::isSrand = false;

/*
 default constructor
 */
Array::Array() {
    //cout << "Default constructor." << endl;
    ptr = nullptr;
    size = 0;
}
/*
 overloaded constructor
 */
Array::Array(int s) {
    //cout << "Overloaded constructor." << endl;
    ptr = new int[s];
    size = s;
    numElem += s;
}
/*
 copy constructor
 */
Array::Array(const Array& arr) {
    //cout << "Copy constructor." << endl;
    numElem = numElem - size + arr.size;
    ptr = new int[arr.size];
    //*ptr = *arr.ptr; //pretty sure this creates shallow copy?
    size = arr.size;
    for (int i = 0; i < size; i++) {
        ptr[i] = arr[i];
    }
}
/*
 destructor
 */
Array::~Array() {
    //cout << "Destructor" << endl;
    delete[] ptr;
}
/* []INDEX
 Paramters: index of element to access
 Returns: element at index
 Summary: find element at given index
 */
int& Array::operator[] (int idx) const{
    if (size < idx || idx < 0)
        cout << "array index out of bounds" << endl;
    return ptr[idx];
}
/* =ASSIGNMENT
 Paramters: another Array object
 Returns: a duplicate array
 Summary: assigns new array object that is a copy of another array
 */
Array& Array::operator= (const Array& arr) {
    if(this != &arr) { //check address to make sure not same object
        delete[] ptr;
        numElem = numElem - size + arr.size;
        ptr = new int[arr.size];
        //*ptr = *arr.ptr;
        size = arr.size;
        for (int i = 0; i < size; i++) {
            ptr[i] = arr[i];
        }
    }
    return *this;
}
/* ==EQUALITY
 Paramters: another Array object
 Returns: true if array is ordered subset of other array, else false
 Summary: compare two arrays via size & elements
 */
bool Array::operator== (const Array& arr) const {
    
    int temp;
    if (size <= arr.size) //find smallest array
        temp = size;
    else
        temp = arr.size;
    
    for (int i = 0; i < temp; i++) {
        if(ptr[i] != arr[i])
            return false;
    }
    return true;
}
/* < LESS THAN
 Paramters: another Array object
 Returns: true if element in same index is less than other array element
 Summary: compare two arrays by elements from left to right
 */
bool Array::operator< (const Array& arr) const{
    //assuming same size...
    for (int i = 0; i < size; i++) {
        if (ptr[i] < arr[i])
            return true;
    }
    return false;
}
/* !SHUFFLE
 Paramters: an Array object
 Returns: a randomly shuffled Array object
 Summary: randomly shuffle the elements in the array
 */
Array& Array::operator! () {
    if (!isSrand) {
        srand(time(0)); //seed only once
        isSrand = true;
    }
    int x, y;
    for (int i = size-1; i > 0; i--) {
        y = rand() % size; //pick random element
        x = ptr[i];        //swap with current element
        ptr[i] = ptr[y];
        ptr[y] = x;
    }
    return *this;
        
}
/* *SMALLEST
 Paramters: an Array object
 Returns: smallest value in Array object
 Summary: find smallest element in array
 */
int Array::operator* () const{
    int min = ptr[0];
    for (int i = 1; i < size; i++) {
        if(ptr[i] < min)
            min = ptr[i];
    }
    return min;
}
/* +=MERGE
 Paramters: an Array object
 Returns: return combined array
 Summary: combine elements in 2 array objects, update size variable
 */
Array& Array::operator+= (const Array& arr) {
    numElem -= size;
    int* ptr2 = new int[size + arr.size]; //create new array
    for (int i = 0; i < size; i++) {      //populate w/left array
        ptr2[i] = ptr[i];
    }
    for (int i = size; i < size + arr.size; i++){ //populate w/right array
        ptr2[i] = arr[i-size];
    }
    delete[] ptr; //delete before reassigning or else memory leak
    ptr = ptr2; //call assignment op
    size += arr.size;
    numElem += size;
    return *this;
}
/* ++INCREMENT POST-FIX
 Paramters: none
 Returns: incremeneted array
 Summary: increments all elements in array by 1
 */
Array Array::operator++ (int dummy) {
    Array temp = *this;
    for (int i = 0; i < size; i++) {
        ptr[i]++;
    }
    //postfix passes by value, calls copy constructor
        //so adjust numElements
    numElem -= size;
    return temp;
}
/* --DECREMENT PRE-FIX
 Paramters: none
 Returns: decremeneted array
 Summary: decrements all elements in array by 1
 */
Array& Array::operator-- () {
    for (int i = 0; i < size; i++) {
        ptr[i]--;
    }
    return *this;
} 
ostream& operator<< (ostream& out, const Array& arr) {
    for (int i = 0; i < arr.size; i++) {
        out << arr[i] << " ";
    }
    out << endl;
    return out;
}
/* getSize
 Paramters: none
 Returns: number of elements in Array object
 Summary: getter function to return number of elements in array object
 */
int Array::getSize() const{
    return size;
}
/* --DECREMENT PRE-FIX
 Paramters: none
 Returns: total number of elements in all Array objects
 Summary: getter function to return total number of
          elements in all Array objects
 */
int Array::getNumberOfElements(){
    return numElem;
}
