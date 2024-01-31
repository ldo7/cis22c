/*
 Cafe Simulator
 Written By: Jacky, Lani
 Summary: Integrate hash tables and binary search trees with out Drink object to
          simulate an Employee interface of a consumer transaction.
 */
 #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Stack.h"
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Drink.h"

using namespace std;

//function prototypes
void displayMenu();
void firstToUpper(string& str);
void _printFile(const Drink& drink);
void strDisplay(const string& name);
void displayStats(HashTable<Drink> &hash);
void iDisplay(const string& name, int level);
void undoDelete(HashTable<Drink> &hash, BinarySearchTree<string> &bst, Stack<Drink> &stck);
bool buildDatabase(string fname, HashTable<Drink> &hash, BinarySearchTree<string>& bst);
void menuManager(HashTable<Drink> &, BinarySearchTree<string> &, Stack<Drink>&);
void searchManager(const HashTable<Drink> &, const BinarySearchTree<string> &);
void deleteManager(HashTable<Drink> &, BinarySearchTree<string> &, Stack<Drink>&);
void insertManager(HashTable<Drink> &, BinarySearchTree<string> &, Stack<Drink>&);
void saveToFile(const HashTable<Drink> &hash, const BinaryTree<string>& bst, Stack<Drink> &stck);

/*
 This function executes the entire program.
 */
int main()
{
    string fname = "input.txt";
    HashTable<Drink> hash;
    BinarySearchTree<string> bst;
    Stack<Drink> stck;
    
    if(buildDatabase(fname, hash, bst))
        menuManager(hash, bst, stck);
    return 0;
}

/*
 This function reads data from a file specified by the filename fname and populates a hash table
 and a binary search tree with the contents of the file. It returns a boolean value indicating
 whether the file was successfully opened.
 */
bool buildDatabase(string fname, HashTable<Drink> &hash, BinarySearchTree<string>& bst){
    Drink newDrink;
    string line;
    int count=0, numItems=0;
    ifstream inputFile(fname);

    if (!inputFile) {
        cout << "Error opening file." << endl;
        return false;
    }
    
    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        // Extract the key-value pair from each line
        string key, value;
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            key = line.substr(0, colonPos);
            value = line.substr(colonPos + 1);
        }

        // Remove leading/trailing whitespace from the value
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Fill in the Drink object based on the key
        if (key == "Name") {
            newDrink.setName(value);
            bst.insert(value);
            count++;
        }
        else if (key == "Type") {
            newDrink.setType(value);
            count++;
        }
        else if (key == "Rating") {
            newDrink.setRating(stod(value));
            count++;
        }
        else if (key == "Dairy (Y/N)") {
            newDrink.setDairy(value);
            count++;
        }
        else if (key == "Price") {
            newDrink.setPrice(stod(value));
            count++;
        }
        if (count==5){
            hash.insert(newDrink, _hash);
            count = 0;
            numItems++;
        }
    }
    inputFile.close();
    return true;
}

/*
 This function manages the main menu of the program. It displays the menu options, reads the user's choice,
 and executes the corresponding functionality based on the selected option.
 */
void menuManager(HashTable<Drink> &hash, BinarySearchTree<string> &bst, Stack<Drink> &stck)
{
    int choice;
    bool playing = true;
    cout << "============================================================" << endl;
    cout << "\t\t  Welcome to De Anza’s 22c Café Simulator!" << endl;
    cout << "============================================================" << endl;
    displayMenu();
    
    while(playing){
        cout << "=================================================" << endl;
        cout << "Please choose option 1-9: ";
        cin >> choice;
        cout << "=================================================" << endl;

        switch(choice)
        {
            case 1: //Add Drink
            {
                insertManager(hash, bst, stck);
                break;
            }
            case 2: //Delete Drink
            {
                deleteManager(hash, bst, stck);
                break;
            }
            case 3: //Undo delete
            {
                undoDelete(hash, bst, stck);
                break;
            }
            case 4: //Search by name
            {
                searchManager(hash, bst);
                break;
            }
            case 5: //Display all drinks
            {
                cout << "DRINKS MENU" << endl;
                bst.inOrder(strDisplay);
                break;
            }
            case 6: //Write to File
            {
                saveToFile(hash, bst, stck);
                cout << "All drinks saved to file!" << endl;
                break;
            }
            case 7: //Statistics
            {
                displayStats(hash);
                break;
            }
            case 8: //Help
            {
                displayMenu();
                break;
            }
            case 9: //Quit
            {
                cout << "\n\t\t\t\t\tGOODBYE!\n" << endl;
                cout << "=================================================" << endl;
                //save to file
                playing = false;
                break;
            }
            case 10: //Team members (hidden)
            {
                cout << "Creators: Lani D, Jharell B, Jacky W, Mariia R" << endl;
                break;
            }
            case 11: //Indented Tree (hidden)
            {
                bst.printTree(iDisplay);
                break;
            }
            default:
            {
                cout << "Invalid choice! Please enter a valid option." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}


/*
 This function is responsible for displaying the menu options to the user.
 */
void displayMenu(){
    cout << "\t\t\t\t\tMENU OPTIONS" << endl;
    cout << "1 - Add Drink" << endl;
    cout << "2 - Delete Drink" << endl;
    cout << "3 - Undo delete" << endl;
    cout << "4 - Search by name" << endl;
    cout << "5 - Display all drinks" << endl;
    cout << "6 - Save to File" << endl;
    cout << "7 - Statistics" << endl;
    cout << "8 - Help" << endl;
    cout << "9 - Quit" << endl;
//    cout << "HIDDEN" << endl;
//    cout << "10 - Team members" << endl;
//    cout << "11 - Indented Tree" << endl;
}

/*
 This function prompts the user to enter the name of a drink and searches for it in the binary
 search tree. If found, it retrieves the corresponding drink from the hash table and displays its details.
 */
void searchManager(const HashTable<Drink> &hash, const BinarySearchTree<string> &bst)
{
    string name;
    Drink foundDrink;

    cout << "Enter the name of the drink to search: ";
    cin.ignore();
    getline(cin, name);
    firstToUpper(name);
    
    if(!bst.search(name,name))
        cout << name << " not found!" << endl;
    else
    {
        hash.search(foundDrink, name, _hash);
        cout << foundDrink;
    }
}

/*
 This function prompts the user to enter the name of a drink and deletes it from the hash table
 and binary search tree if found. The deleted drink is also pushed onto the stack of deleted drinks.
 */
void deleteManager(HashTable<Drink> &hash, BinarySearchTree<string> &bst, Stack<Drink>&stck)
{
    Drink delDrink;
    string name;
    cout << "Enter the name of the drink to delete: ";
    cin.ignore();
    getline(cin, name);
    firstToUpper(name);

    if(!bst.search(name, name))
        cout << name << " not found!" << endl;
    else
    {
        bst.remove(name);
        hash.remove(delDrink, name, _hash);
        stck.push(delDrink);
        cout << name << " has been deleted!" << endl;
    }
}

/*
 This function takes a reference to a HashTable<Drink> object as a parameter and displays
 statistics about the hash table, such as the load factor, total number of collisions,
 and the longest collision path.
 */
void displayStats(HashTable<Drink> &hash){
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
    
    int totalCollisions = 0;
    int longestCollisionPath = 0;
    int longestIndex = 0;
    
    for (int i = 0; i < hash.getSize(); ++i)
    {
        if (hash.getHashArray()[i].getOccupied() > 0)
        {
            int collisions = hash.getHashArray()[i].getNoCollisions();
            totalCollisions += collisions;
            
            if(longestCollisionPath < hash.getHashArray()[i].getNoCollisions())
            {
                longestCollisionPath = hash.getHashArray()[i].getNoCollisions();
                longestIndex = i;
            }
        }
    }
    string colName = hash.getHashArray()[longestIndex].getItem().getName();
    
    cout << "Total number of collisions: " << totalCollisions << endl;
    cout << "The longest collision path: ";
    hash.GetCollisionNames(longestIndex, colName, _hash);
    cout << endl;
}


/*
 This function saves the contents of the hash table to a file named "output.txt".
 It also clears the stack of deleted drinks.
 */
void saveToFile(const HashTable<Drink> &hash, const BinaryTree<string>& bst, Stack<Drink> &stck)
{
    hash.printTable(_hash, _printFile);
    cout << "Drinks successfully saved to file!" << endl;

    //CLEAR STACK
    while(!stck.isEmpty())
    {
        stck.pop();
    }
}

/*
 This function allows the user to create a new drink by providing its details
 (name, type, rating, dairy status, and price). The new drink is then inserted
 into the hash table and binary search tree.
 */
void insertManager(HashTable<Drink> &hash, BinarySearchTree<string> &bst, Stack<Drink> &stck)
{
    Drink newDrink;
    string input;
    cout << "CREATE A NEW DRINK" << endl;
    
    cout << "Name: " ;
    cin.ignore();
    getline(cin, input);
    firstToUpper(input);
    if(bst.search(input, input)){         //check synonym
        cout << input << " already added to menu!" << endl;
        return;
    }
    bst.insert(input);                   //insert BST
    newDrink.setName(input);
   
    cout << "Type of Beverage: " ;
    getline(cin, input);
    newDrink.setType(input);
    
    cout << "Rating (out of 5): " ;
    getline(cin, input);
    newDrink.setRating(stod(input));
   
    cout << "Dairy (Y/N): " ;
    getline(cin, input);
    newDrink.setDairy(input);
   
    cout << "Price: " ;
    getline(cin, input);
    newDrink.setPrice(stod(input));

    hash.insert(newDrink, _hash);       //insert hashTable
    
    cout << "Drink added successfully!" << endl;
}


/*
 helper functions
 */

/*
 This function converts the first character of each word in a given string to uppercase
 and the remaining characters to lowercase. It helps standardize the capitalization of input strings.
 */
void firstToUpper(string& str){
    if(str.empty())
        return;
    
    istringstream is(str);
    istringstream is2(str);
    string word, result;
    int k = 0;
    
    //count words in string
    while (is2 >> word)
        k++;
    
    //correct char in each word
    while (is >> word) {
        word[0] = toupper(word[0]);
        for (int i=1; i<word.length();i++){
            word[i] = tolower(word[i]);
         }
        result += word;
        if (k > 1){
            result += " ";
            k--;
        }
    }
    str = result;
}

/*
 This function takes a string and an integer as parameters and displays the string with
 an indentation level specified by the integer. It is used to display an indented tree of strings.
 */
void iDisplay(const string& name, int level){
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << name << endl;
}

/*
 This function takes a string as a parameter and displays it on the console. It is used to
 display strings from a binary search tree.
 */
void strDisplay(const string& name){
    cout << name << endl;
}

/*
 This function takes a Drink object as a parameter and appends its contents to an output file
 named "output.txt". It is used to save drinks to a file.
 */
void _printFile(const Drink& drink){
    ofstream file;
    
    file.open("outputFile.txt", ios::app);
    
    if(file.is_open()){
        file << drink;
    }
    file.close();
}

/*
 This function restores a recently deleted drink by popping it from the stack of deleted drinks,
 inserting it back into the binary search tree and hash table. It allows the user to undo a drink deletion.
 */
void undoDelete(HashTable<Drink> &hash, BinarySearchTree<string> &bst, Stack<Drink> &stck){
    if(stck.isEmpty()){
        cout << "no recently deleted drinks!" << endl;
    }
    else
    {
        Drink newDrink = stck.pop();
        bst.insert(newDrink.getName());
        hash.insert(newDrink, _hash);
        cout << newDrink.getName() << " added back to menu!" << endl;
    }
}
