// Specification file for the Park class
// Written By: A. Student
// IDE: Xcode
// Modified by:

#ifndef PARK_H
#define PARK_H

#include<iostream>
#include<string>
 
// using namespace std;
    //^^^^^ This statement
    // in a header file of a complex project could create
    // namespace management problems for the entire project
    // (such as name collisions).
    // Do not write using namespace at the top level in a header file!

using std::string;

class Park; // Forward Declaration

// Function Prototypes for friend functions
void hDisplay(const Park &);
void vDisplay(const Park &);
void iDisplay(const Park &, int);
/* Write your code here */
void kDisplay(const Park &);


class Park
{
    private:
    string code;  // the unique park identifier
    string state;
    string name;
    string description;
    int year;
        
    public:
    //constructors
    Park();
    Park(string, string, string, string, int);

    //setters
    void setCode(string cd){ code = cd;}
    void setState(string st){ state = st;}
    void setName(string nm){ name = nm;}
    void setDesc(int dsc){ description = dsc;}
    void setYear(int yr){ year = yr;}

    //getters
    string getCode() const {return code;}
    string getState() const {return state;}
    string getName() const {return name;}
    string getDesc() const {return description;}
    int getYear() const {return year;}

    
    // overloaded operators
    bool operator > (const Park &right) {return (code> right.code);}     // Overloaded >
    bool operator < (const Park &right) {return (code < right.code);}    // Overloaded <
    bool operator == (const Park &right) {return (code == right.code);}  // Overloaded ==
    
    // friend functions
    friend void hDisplay(const Park &);
    friend void vDisplay(const Park &);
    friend void iDisplay(const Park &item, int level);
    /* Write your code here */
    friend void kDisplay(const Park &);
    
};

#endif
