/*
 CIS22B
 02/16/23
 Assignment #5
 
 This program creates a simple vending machine with 3 different snacks,
 and asks the user to input money & select a snack.
================================================================================
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#pragma warning (disable: 4996)
//^^display time in code
using namespace std;

class Snack {
private:
    string name;
    double price;
    int stock;
    int sold;
    string* ptime;
    string getCurrentTime() //display time when each item is sold
    {
        time_t t = time(0);
        struct tm ts;
        char buff[10];
        ts = *localtime(&t);
        strftime(buff, sizeof(buff), "%X", &ts);
        return buff;
    }
public:
//==============
// Constructors
//==============
    Snack()
    {
        name = " ";
        price = 0;
        stock = 0;
        sold = 0;
        ptime = nullptr;
    }
    Snack(string n, double p, int s)
    {
        name = n;
        price = p;
        stock = s;
        sold = 0;
        ptime = new string[s];
    }
//=========================
// Getter & Setter methods
//=========================
    string getName() const{
        return name;
    }
    double getPrice() const{
        return price;
    }
    int getStock() const{
        return stock;
    }
    int getSold() const{
        return sold;
    }
    void setName(string n){
        name = n;
    }
    void setPrice(double p){
        price = p;
    }
    void setStock(int s){
        stock = s;
        ptime = new string[s];
    }
    void setSold(int s){
        sold = s;
    }
// =========================================================================
//                                  buyItem
// 1)Parameters: amount of money entered by user
// 2)Returns: true if 'Y' yes, false if 'N' no
// 3)Summary: checks if user has sufficient funds to purchase items. If so,
//          then adjust stock and total money remaining, else display error
//          if insufficient funds or stock is sold out.
// =========================================================================
    bool buyItem(double& moneyEntered)
    {
        if(moneyEntered >= price && stock > 0)          //sufficient funds
        {                                               // & item in-stock
            moneyEntered -= price;
            ptime[sold] = getCurrentTime();
            stock--;
            sold++;
            cout << "Item has been dispensed below" << endl;
            if (moneyEntered>0)
            {
                cout << "$" << setprecision(2) << moneyEntered
                     << " dispensed below" << endl;
            }
            return true;
        }
        else if (moneyEntered < price)                   //lacks funds
        {
            cout << "ERROR: not enough money!" << endl;
        }
        else                                             //out of stock
        {
            cout << "ERROR: item is sold-out!" << endl
                 << "$" << setprecision(2) << moneyEntered
                 << " dispensed below" << endl;
        }
        
        return false;
    }
//============
// Destructor
//============
    ~Snack()
    {
        //display stock left, total sold, & profits
        //if none bought, don't display
        cout << "\n\nClosing info for " << name << ":" << endl
             << setw(9) << stock << " in stock" << endl
             << setw(9) << sold << " sold";
        if(sold != 0)
        {
            cout << " for profit of $" << price*sold << endl
                 << "\nTransactions occured at: " << endl;
            
            //display time
            for (int i=0; i<sold; i++)
            {
                cout << setw(16) << ptime[i] << endl;
            }
        }
        
        //clean heap
        delete[] ptime;
        ptime = nullptr; //good habit, so not dangling?
    }
};

//===================
//function prototypes
//===================
void displayVendingMachine(const Snack [], int);
int getQuarters();
void userBuyItem(Snack [], int);
bool promptToContinue();

int main()
{
    const int SIZE = 3; //initially put int const OOPS
    bool loop = true;

    //OKAY
    //Snack snacks[SIZE] = {Snack(),Snack("Candy",1.25,5),Snack("Soda",1,2)};
    
    //BETTER
    Snack snacks[SIZE] = {
        Snack(),
        Snack("Candy",1.25,5),
        Snack("Soda",1,2)
    };
    snacks[0].setName("Chips");
    snacks[0].setPrice(1.75);
    snacks[0].setStock(3);
    
    cout << "Welcome to the vending machine!" << endl;
    
    /*                             //OKAY
    while (loop)
    {
        userBuyItem(snacks, 3);
        loop = promptToContinue();
    }*/
                                   //BETTER
    do {
        userBuyItem(snacks, SIZE);
    } while (promptToContinue());
    
    return 0;
}
// ===============================================================
//                       displayVendingMachine
// 1)Parameters: array of Snack objects and num of elements inside
// 2)Returns: none
// 3)Summary: displaying the vending machine’s contents
// ===============================================================
void displayVendingMachine(const Snack s[], int size)
{
    cout << "\nItem #" << setw(15)                   //OKAY
         << "Item Name" << setw(12)
         << "Price" << setw(15)
         << "# in-stock" << endl
         << setfill('-') << setw(49)
         << "-" << setfill(' ') << endl;
    /*                                              //BETTER
     cout << setw(10) << left << "Item #"
         << setw(14) << left << "Item Name"
         << setw(10) << left << "Price"
         << setw(10) << left << "# in-stock" << endl
         << "--------------------------------------------" << endl;
     */
    
    for (int i = 0; i < size; i++)                   //OKAY
    {
        cout << setw(12) << left << i+1
             << setw(16) << s[i].getName()
             << setw(10) << fixed << setprecision(2) << s[i].getPrice()
             << s[i].getStock() << right << endl;
        
        /*                                           //BETTER
         for (i = 0; i < length; i++) {
             cout << setw(10) << left << i + 1
                 << setw(14) << left << list[i].getName()
                 << setw(10) << left << list[i].getPrice()
                 << setw(10) << left << list[i].getQuantity() << endl;
         */
    }
}
// ============================================
//                  getQuarters
// 1)Parameters: none
// 2)Returns: number of quarters
// 3)Summary: request and validate money input
// ============================================
int getQuarters() {
    int quarters;
    do {
        cout << "\nEnter a number of quarters: ";
        cin >> quarters;
        if (quarters < 1) {
            cout << "Please enter a number greater than 0" << endl;
        }
    } while(quarters < 1);
    return quarters;
}
// =================================================================
//                           userBuyItem
// 1)Parameters: array of Snack objects and num of elements inside
// 2)Returns: none
// 3)Summary: prompt the user to choose a snack
// =================================================================
void userBuyItem(Snack snacks[], int numSnacks)
{
    displayVendingMachine(snacks, numSnacks);
    
    double dollars = 0.25 * getQuarters();
    int item;
    cout << "Amount Entered: $" << fixed << setprecision(2)
         << dollars << endl;
    do {
        cout << "\nEnter a number between 1 and 3 and make your selection: ";
        cin >> item;
        if(item < 1 || item > numSnacks)
            cout << "Please enter a number between 1 and 3" << endl;
    } while(item < 1 || item > numSnacks);
    
   snacks[item-1].buyItem(dollars);
}

// =======================================================
//                     promptToContinue
// 1)Parameters: none
// 2)Returns: true if 'Y' yes, false if 'N' no
// 3)Summary: determine if user wants to continue or exit
// =======================================================
bool promptToContinue(){
    string c; //simplier to use char & cin since string isn't validated by isalpha....
    while (true) {
        cout << "\nContinue? (Y / N): ";
        getline(cin >> ws, c);
        if (c == "Y" || c == "y" )
        {
            return true;
        }
        else if (c == "N" || c == "n" )
        {
            return false;
        }
        else
        {
            cout<<"ERROR: please enter Y or N" << endl;
        }
    }
}

/* SAMPLE RUN OF CODE
 
 Welcome to the vending machine!

 Item #      Item Name       Price     # in-stock
 -------------------------------------------------
 1           Chips           1.75      3
 2           Candy           1.25      5
 3           Soda            1.00      2

 Enter a number of quarters: -1
 Please enter a number greater than 0

 Enter a number of quarters: 8
 Amount Entered: $2.00

 Enter a number between 1 and 3 and make your selection: 0
 Please enter a number between 1 and 3

 Enter a number between 1 and 3 and make your selection: 4
 Please enter a number between 1 and 3

 Enter a number between 1 and 3 and make your selection: 3
 Item has been dispensed below
 $1.00 dispensed below

 Continue? (Y / N): a
 ERROR: please enter Y or N

 Continue? (Y / N): Y

 Item #      Item Name       Price     # in-stock
 -------------------------------------------------
 1           Chips           1.75      3
 2           Candy           1.25      5
 3           Soda            1.00      1

 Enter a number of quarters: 4
 Amount Entered: $1.00

 Enter a number between 1 and 3 and make your selection: 3
 Item has been dispensed below

 Continue? (Y / N): y

 Item #      Item Name       Price     # in-stock
 -------------------------------------------------
 1           Chips           1.75      3
 2           Candy           1.25      5
 3           Soda            1.00      0

 Enter a number of quarters: 4
 Amount Entered: $1.00

 Enter a number between 1 and 3 and make your selection: 3
 ERROR: item is sold-out!
 $1.00 dispensed below

 Continue? (Y / N): y

 Item #      Item Name       Price     # in-stock
 -------------------------------------------------
 1           Chips           1.75      3
 2           Candy           1.25      5
 3           Soda            1.00      0

 Enter a number of quarters: 10
 Amount Entered: $2.50

 Enter a number between 1 and 3 and make your selection: 1
 Item has been dispensed below
 $0.75 dispensed below

 Continue? (Y / N): Y

 Item #      Item Name       Price     # in-stock
 -------------------------------------------------
 1           Chips           1.75      2
 2           Candy           1.25      5
 3           Soda            1.00      0

 Enter a number of quarters: 9
 Amount Entered: $2.25

 Enter a number between 1 and 3 and make your selection: 1
 Item has been dispensed below
 $0.50 dispensed below

 Continue? (Y / N): n


 Closing info for Soda:
         0 in stock
         2 sold for profit of $2.00

 Transactions occured at:
         23:37:50
         23:38:00


 Closing info for Candy:
         5 in stock
         0 sold

 Closing info for Chips:
         1 in stock
         2 sold for profit of $3.50

 Transactions occured at:
         23:38:23
         23:38:32
 Program ended with exit code: 0
 */
