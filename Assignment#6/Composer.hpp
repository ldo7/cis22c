/*
 Header file for Composer class
 */
#ifndef Composer_hpp
#define Composer_hpp

#include <iostream>
#include <string>
using namespace std;

class Composer {
private:
    string name;
    int date;
public:
    Composer();
    Composer(string, int);
    ~Composer();
    void setName(string);
    void setDate(int);
    string getName() const;
    int getDate() const;
    bool operator< (const Composer&) const;
    bool operator> (const Composer&) const;
    bool operator== (const Composer&) const;
    friend ostream& operator<< (ostream&, const Composer&);
};

#endif /* Composer_hpp */
