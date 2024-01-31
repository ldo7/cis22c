/*
 Cafe Simulator
 Written By: Jacky, Jharell
 Summary: Drink Object used in cafe simulator, and used as datatype for hash table and BST
 */
#ifndef Drink_h
#define Drink_h

#include<iostream>
#include<string>

using std::string;

class Drink; // Forward Declaration

//Function Prototype for friend functions
int _hash(const Drink& key, int size);
void iDisplay(const Drink &item, int level);
void vDisplay(const Drink &);

class Drink
{
private:
    string name;
    string type;
    double rating;
    string dairy;
    double price;
        
public:
    //constructors
    Drink() {name = ""; type = ""; rating = -1; dairy = ""; price = -1;}
    Drink(string nm) {name = nm; type = ""; rating = -1; dairy = ""; price = -1;}
    Drink(string nm, string tp, double rat, string sz, double prc)
          {name = nm; type = tp; rating = rat; dairy = sz; price = prc;}
    
    //setters
    void setName(string nm){ name = nm;}
    void setType(string tp){ type = tp;}
    void setRating(double rat){ rating = rat;}
    void setDairy(string sz){ dairy = sz;}
    void setPrice(double prc){ price = prc;}
    
    //getters
    string getName() const {return name;}
    string getType() const {return type;}
    double getRating() const {return rating;}
    string getDairy() const {return dairy;}
    int getPrice() const {return price;}
    
    // friend functions
    friend int _hash(const Drink& key, int size);
    friend std::ostream& operator<< (std::ostream&, const Drink&);
    
    // overloaded operators
    bool operator > (const Drink &right);
    bool operator < (const Drink &right);
    bool operator == (const Drink &right);
};


#endif
