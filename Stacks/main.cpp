/**~*~*~*
CIS 22C
Project: Stack ADT

Written by: Lani Do
IDE: xcode
*~*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "StackADT.h"

using namespace std;

void printInfo();
void processNumbers(string, Stack<int> &, Stack<int> &, int);
void printStack(Stack<int> &);
static bool open = false;   //true if file is successfully opened

int main()
{
    printInfo();

    cout << "Enter input file name: " << endl;
    string filename;
    getline(cin, filename); // assume valid

    Stack<int> s;           // main stack
    Stack<int> maxstack;    // stack with largest elements
    int max = -999;

    processNumbers(filename, s, maxstack, max);

    printStack(s);

    return 0;
}

/**~*~*~*~*~
This function displays the project's title
*~*/
void printInfo(){
    cout << " ~*~ Project: Stack ADT ~*~ " << endl;
}

/**~*~*~*~*~
This function processes the input file
 Depending on the input, stack elements will be added, removed, or displayed.
*~*/
void processNumbers(string filename, Stack<int>& s, Stack<int>& maxstack, int max){
    ifstream file;
    file.open(filename);
    int data;

    if(!file){
        cout <<"There was an error opening \""<< filename <<"\". Exiting." << endl;
        return;
    }
    cout << endl << "Input File: " << filename << endl;
    
    while(file >> data){
        open = true;
//        cout << data << " ";//DEBUG

        //display the number of elements in the stack
        if (data == 0)
        {
            cout << "Count: " << s.getLength() << endl;
        }
        // display element at top and largest value
        else if (data == 1)
        {
            if (s.getLength() == 0)
                cout << "Top: Empty" << endl;
            else{
                cout << "Top: " << s.peek() << endl
                     << "Max: " << max << endl;
            }

        }
        // (-)num, remove top element and display largest value
        else if (data < 0)
        {
            if (s.getLength() == 0)
                cout << "Pop: Empty" << endl;
            else{
                maxstack.pop();
                if(maxstack.getLength() > 0)    //update max value
                    max = maxstack.peek();
                cout << "Pop: " << s.pop() << endl;
                if(s.getLength() > 0)
                     cout << "Max: " << max << endl;
            }
        }
        // (+)num, add element to stack
        else
        {
            s.push(data);
            if(data > max){
                max = data;
            }
            maxstack.push(max);
        }
    }

    file.close();
}

/**~*~*~*~*~
This function prints remaining elements on the stack
*~*/
void printStack(Stack<int>& s){
    //if empty stack & file never opened
    if(s.getLength() <= 0 && open)
        cout << "Stack: Empty" << endl;
    //if elements remaining in stack & file was opened
    else if (open){
        cout << "Stack: ";
        while (s.getLength() > 0){
            cout << s.pop() << " ";
        }
        cout << endl;
    }
}
