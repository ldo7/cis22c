/*
  Heaps - ADT

  This program will read data about overbooked customers,
  find their priority and serial numbers, build a heap, then display
  customers in priority sequence
 
  Written By: A. Student
  Changed By:
  IDE:
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "Customer.h"
#include "Heap.h"

using namespace std;
int compare(const Customer &c1,const Customer &c2)
{
    int p1 = c1.getMileage() / 1000 + c1.getYear()- c1.getSeq();
    int p2 = c2.getMileage() / 1000 + c2.getYear()- c2.getSeq();
    
    //compare serial num if same priority
    if(p1==p2)
    {
        int s1 = c1.getSerial();
        int s2 = c2.getSerial();
        if (s1 < s2)
            return -1;
        if (s1 == s2)
            return 0;
        return 1;
    }
    
    //compare priority
    if (p1 < p2)
        return -1;
    if (p1 == p2)
        return 0;
    return 1;
}

int main()
{
    Heap<Customer> heap;
    
    // Get input file name
    string fname;// = "overbooked_2.txt";
    cout << "Input file name: ";
    getline(cin, fname);
    cout << endl;
    
    int year,mileage,seq=0,over=0;
    string name;
    char letter;
    Customer c;
    ifstream inputFile(fname);

    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 0;
    }
    string line;
    while (getline(inputFile, line))
    {
       stringstream temp(line);   // create temp with data from line
        temp >> letter;
        if(letter == 'S'){
            over++;
            heap.deleteHeap(c, compare);
            display(c);
        }
        else if (letter == 'A'){
            temp >> year;
            temp >> mileage;
            temp.ignore();             // to ignore space in front of name
            getline(temp, name);
            seq++;
            Customer c(year,mileage,seq,name);
//            display(c); //debug
            heap.insertHeap(c, compare);
        }
    }

    inputFile.close();
    
    cout << "Served overbooked customers: " << over <<endl<<endl;
    
    int num =heap.getCount();
    while(!heap.isEmpty()){
        heap.deleteHeap(c, compare);
        display(c);
    }
    cout << "Rejected overbooked customers: " << num << endl;

   
    return 0;
}


