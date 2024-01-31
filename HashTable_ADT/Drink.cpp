#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Drink.h"
using namespace std;
/*
Hash function: takes the key and returns the index in the hash table
*/

int _hash(const Drink &key, int size)
{
    string k = key.getName();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        sum += k[i] * k[i] * k[i];
    return sum % size;
}

/*
 
 */
ostream& operator<< (ostream& out, const Drink& item){
        out << "Name: " << item.name << endl;
        out << "Type: " << item.type << endl;
        out << "Rating: " << item.rating << endl;
        out << "Dairy (Y/N): " << item.dairy << endl;
        out << "Price: " << item.price << endl << endl << endl;
        return out;
}

//
bool Drink::operator > (const Drink &right)
{
    string name1 = name;
    string name2 = right.name;
    transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
    transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
    return (name1 > name2);
}

//
bool Drink::operator < (const Drink &right)
{
    return !(name > right.name);
}

//
bool Drink::operator == (const Drink &right)
{
    string name1 = name;
    string name2 = right.name;
    transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
    transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
    return (name1 == name2);
}
