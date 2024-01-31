/*
 Cafe Simulator
 Written By: Lani, Jharell
 */
#include <iostream>
#include <fstream>
#include <sstream>
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
    overload ostream opeator for save to output file function
 */
ostream& operator<< (ostream& out, const Drink& item){
        out << "Name: " << item.name << endl;
        out << "Type: " << item.type << endl;
        out << "Rating: " << item.rating << endl;
        out << "Dairy (Y/N): " << item.dairy << endl;
        out << "Price: " << item.price << endl << endl << endl;
        return out;
}

/*
 overload greater than operator for binary search tree functions
 */
bool Drink::operator > (const Drink &right)
{
    string name1 = name;
    string name2 = right.name;
    transform(name1.begin(), name1.end(), name1.begin(), ::tolower); //insenstive-case comparison
    transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
    return (name1 > name2);
}

/*
 overload less than operator for binary search tree functions
 */
bool Drink::operator < (const Drink &right)
{
    return !(name > right.name);
}

/*
 overload equality operator for binary search tree functions
 */
bool Drink::operator == (const Drink &right)
{
    string name1 = name;
    string name2 = right.name;
    transform(name1.begin(), name1.end(), name1.begin(), ::tolower); //insenstive-case comparison
    transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
    return (name1 == name2);
}
