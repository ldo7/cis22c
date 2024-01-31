/*
 CIS22B
 03/10/23
 Assignment #6
 
 This program implements linked lists to create a simple list of Composers,
 and allows the user to edit or view the list.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Composer.hpp"
#include "LinkedList.h"
using namespace std;

int main() {
    LinkedList<Composer> list;          //create list of Composers
    Composer c;
    ifstream file;
    string name, temp;
    int date;

    file.open("composers.txt");         //read file & populate list
    while(file){
//    for(int i=0;i<34;i++){
        getline(file, name, ',');
        getline(file, temp);
        date = stoi(temp);
        c.setName(name);
        c.setDate(date);
        list.insert(c);
    }
    file.close();
                                        //request user input
    while(true){
        cout << "Enter 's' to search, 'r' to remove, 'd' to display,"
             <<" or 'e' to exit: ";
        getline(cin, temp);

        
//        char input;
//        cin >> temp;              //cannot use getline with char
//        switch(input){
//            case 's': case 'S':   //upper & lower cases
//                //
//                break;            //MUST add "break;" after every case
//            case 'r': case 'R':       //or else next case may run
//                //
//                break;
//        }
        
        if(temp == "s")                     //SEARCH
        {
            cout << "Enter a composer's name to search for: ";
            getline(cin, name);
            c.setName(name);
            cout << endl << setw(5+static_cast<int>(name.size())) << name;
            if (list.find(c)) {
                cout << " was found in the list\n" << endl;
            }
            else {
                cout << " was found not in the list\n" << endl;
            }

        }
        else if(temp == "r")                //REMOVE
        {
            cout << "Enter a composer's name to remove: ";
            getline(cin, name);
            c.setName(name);
            cout << endl << setw(5+static_cast<int>(name.size())) << name;
            if (list.remove(c)) {
                cout << " was successfully removed from the list\n" << endl;
            } else {
                cout << " was not found in the list when attempting "
                     <<"to remove\n" << endl;
            }
        }
        else if(temp == "d")                //DISPLAY
        {
            cout << endl;
            list.printList();
        }
        else if(temp == "e")                //EXIT
        {
            cout << "Press any key to continue . . . \n" << endl;
            getline(cin, temp);
            //break;
        }
    }
    
    return 0;
}
/* SAMPLE RUN
 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d

 Claudio Monteverdi - 1643
 Henry Purcell - 1695
 Antonio Vivaldi - 1741
 Johann Sebastian Bach - 1750
 George Frideric Handel - 1759
 Wolfgang Amadeus Mozart - 1791
 Joseph Haydn - 1809
 Ludwig van Beethoven - 1827
 Franz Schubert - 1828
 Felix Mendelssohn - 1847
 Frederic Chopin - 1849
 Robert Schumann - 1856
 Hector Berlioz - 1869
 Richard Wagner - 1883
 Franz Liszt - 1886
 Pyotr Ilyich Tchaikovsky - 1893
 Johannes Brahms - 1897
 Giuseppe Verdi - 1901
 Antonin Dvorak - 1904
 Edvard Grieg - 1907
 Gustav Mahler - 1911
 Claude Debussy - 1918
 Camille Saint-Saens - 1921
 Giacomo Puccini - 1924
 George Gershwin - 1937
 Maurice Ravel - 1937
 Sergei Rachmaninoff - 1943
 Bela Bartok - 1945
 Arnold Schoenberg - 1951
 Sergei Prokofiev - 1953
 Igor Stravinsky - 1971
 Dmitri Shostakovich - 1975
 Leonard Bernstein - 1990
 Aaron Copland - 1990

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
 Enter a composer's name to search for: Franz Liszt

      Franz Liszt was found in the list

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
 Enter a composer's name to search for: Hanz Zimmer

      Hanz Zimmer was found not in the list

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
 Enter a composer's name to remove: Camille Saint-Saens

      Camille Saint-Saens was successfully removed from the list

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
 Enter a composer's name to remove: CPE Bach

      CPE Bach was not found in the list when attempting to remove

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d

 Claudio Monteverdi - 1643
 Henry Purcell - 1695
 Antonio Vivaldi - 1741
 Johann Sebastian Bach - 1750
 George Frideric Handel - 1759
 Wolfgang Amadeus Mozart - 1791
 Joseph Haydn - 1809
 Ludwig van Beethoven - 1827
 Franz Schubert - 1828
 Felix Mendelssohn - 1847
 Frederic Chopin - 1849
 Robert Schumann - 1856
 Hector Berlioz - 1869
 Richard Wagner - 1883
 Franz Liszt - 1886
 Pyotr Ilyich Tchaikovsky - 1893
 Johannes Brahms - 1897
 Giuseppe Verdi - 1901
 Antonin Dvorak - 1904
 Edvard Grieg - 1907
 Gustav Mahler - 1911
 Claude Debussy - 1918
 Giacomo Puccini - 1924
 George Gershwin - 1937
 Maurice Ravel - 1937
 Sergei Rachmaninoff - 1943
 Bela Bartok - 1945
 Arnold Schoenberg - 1951
 Sergei Prokofiev - 1953
 Igor Stravinsky - 1971
 Dmitri Shostakovich - 1975
 Leonard Bernstein - 1990
 Aaron Copland - 1990

 Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: e
 Press any key to continue . . .
 
 Program ended with exit code: 9
 */
