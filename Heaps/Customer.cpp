/* *~*~*
Implementation file for the Customer class
Written By: A. Student
Changed by:
IDE:
*~**/
#include <iostream>
#include <string> 
#include "Customer.h"

using namespace std;

Customer::Customer() {
    year = 0;
    mileage = 0;
    seq = 0;
    name = "";
}

Customer::Customer(int y, int m, int s, const string& n) {
    year = y;
    mileage = m;
    seq = s;
    name = n;
    serial = (mileage / 1000 + year - seq) * 100 + (100 - seq);
}

void display(const Customer &c){
    cout << c.year << " ";
    cout << c.mileage << " ";
    cout << "(" << c.serial << ") ";
    cout << "[" << c.name  << "]";
    cout << endl;
}
