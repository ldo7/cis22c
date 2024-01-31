/*
 Function definitions for Composer class
 */
#include <iostream>
#include "Composer.hpp"
#include <string>
using namespace std;
/*
 default constructor
 */
Composer::Composer(){
    name = "";
    date = 0;
}
/*
 overloaded constructor
 */
Composer::Composer(string n, int d){
    name = n;
    date = d;
}
/*
 destructor
    no dynamic allocation in class, so does nothing
 */
Composer::~Composer(){}

/* LESS THAN
 Paramters: Composer object
 Returns: true if this Composer object is more than parameter object
 Summary: compare Composer objects by date
 */
bool Composer::operator< (const Composer& c) const{
    return date < c.date;
}

/* GREATER THAN
 Paramters: Composer object
 Returns: true if this Composer object is less than parameter object
 Summary: compare Composer objects by date
 */
bool Composer::operator> (const Composer&c) const{
    return date > c.date;
}

/* EQUAL
 Paramters: Composer object
 Returns: true if 2 Composer objects are equal, else false
 Summary: compare Composer objects by name
 */
bool Composer::operator== (const Composer&c) const{
//    return date == c.date && name == c.name; //search doesn't work...?
    return name == c.name;
}

/* PRINT
 Paramters: ostream and Composer objec, Returns: none
 Summary: displays Composer object's name & date
 */
ostream& operator<< (ostream& out, const Composer& c){
    out << c.name << " - " << c.date << endl;
    return out;
}

/*
  getters & setters
 */
void Composer::setName(string n){
    name = n;
}
void Composer::setDate(int d){
    date = d;
}
string Composer::getName() const{
    return name;
}
int Composer::getDate() const{
    return date;
}
