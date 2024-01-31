// BST ADT
// Created by A. Student
// Modified by:
 
#include "BinarySearchTree.h"
#include "Park.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

void displayManager(const BinarySearchTree<Park> &);
/* Write your code here: declare buildBST and searchManager */
void buildBST(string str, BinarySearchTree<Park>&);
void searchManager(BinarySearchTree<Park>&);


int main()
{
    string filename = "np.txt";
    BinarySearchTree<Park> bst;

//    cout << "What is the input file's name? ";
//    getline(cin, filename);
    buildBST(filename, bst);
    displayManager(bst);
    searchManager(bst);

    return 0;
}

/* Write your code here: define buildBST and searchManager */
void buildBST(string str, BinarySearchTree<Park>& bst){
    ifstream inputFile(str);
    cout << "Reading data from \"" << str << "\"" << endl;

    if(!inputFile)
    {
        cout << "Error opening the input file: \""<< str << "\"" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
       int year;
       string code, name, state, dsc;
    
       stringstream temp(line);   // create temp with data from line
       temp >> code;              // read from temp
       temp >> state;
       temp >> year;
        temp.ignore();             // to ignore space in front of name
       getline(temp, name, ';');   // stop reading name at ';'
       temp.ignore();             // to ignore space in front of description
       getline(temp, dsc);
       // create a Park object and initialize it with data from file
       Park aPark(code, state, name, dsc, year);
        bst.insert(aPark);
    }

    inputFile.close();
}

/*
Display manager: traversals, count, indented tree, and inner nodes
Input Parameter: bst
*/
void displayManager(const BinarySearchTree<Park> &bst)
{
    string option;
    
    // count
    cout << "Display count [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y")
    {
        cout << "The number of nodes in the BST is ";
        cout << bst.getCount() << endl; /* Write your code here*/
    }
    
    // traversals
    cout << "Display Tree [In/Pre/posT/N]?" << endl;
    getline(cin, option); // I, P, T or N
    option[0] = toupper(option[0]);
    switch (option[0])
    {
       case 'I':
        cout << endl << "Inorder:" << endl;
        /* Write your code here: call inorder - use hDisplay */
        bst.inOrder(hDisplay);
        cout << endl;
        break;
       case 'P':
        cout << endl << "Preorder:" << endl;
        /* Write your code here: call preorder - use hDisplay */
        bst.preOrder(hDisplay);
        cout << endl;
        break;
       case 'T':
        cout << endl << "Postorder:" << endl;
        /* Write your code here: call postorder - use hDisplay */
        bst.postOrder(hDisplay);
        cout << endl;
        break;
       case 'N':
        break;
       default:
        cout << "Invalid option!" << endl;
        break;
    }

    // Indented Tree
    cout << "Display Indented List [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y")
    {
        cout << "Indented List:" << endl;
        /* Write your code here: call printTree - use iDisplay */
        bst.printTree(iDisplay);
        cout << endl;
    }
    
    // Inner Nodes
    cout << "Display Inner Nodes [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y")
    {
        cout  << "Inner Nodes:" << endl;
        /* Write your code here: call printInnerNodes - use kDisplay */
        bst.printInnerNodes(kDisplay);
        cout << endl;
    }
    
}

void searchManager(BinarySearchTree<Park> &bst){
    string targetCode = "";
    Park aPark;

    cout << endl << " Search" << endl;
    cout <<   "=======" << endl;

    while(targetCode != "Q")
    {
        cout << "Enter a park code (or Q to stop searching):" << endl;
        getline(cin, targetCode);
        targetCode[0] = toupper(targetCode[0]);
        targetCode[2] = toupper(targetCode[2);
        if(targetCode != "Q")
        {
            Park target;
            target.setCode(targetCode);
            if(bst.search(target,aPark))
                vDisplay(aPark);
            else
               cout << "Park \"" << targetCode << "\" was not found in this list." << endl;
        }
    }
    cout << "___________________END SEARCH SECTION _____" << endl;
}
