/*
 CIS22B
 02/6/23
 Assignment #3
 
 This program creates a simple movie database.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

//outline Movie object properties
struct Movie {
    string title;
    double revenue; //in billions
    string director;
    string date;
    int runtime; //in minutes
};

//function prototypes
int numberOfLines(ifstream&);
void populateMovieFromFile(ifstream&, Movie&);
void displayMovie(const Movie&);
Movie* createDatabase(int&);
bool caseInsensitiveCmp(string, string);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

// ===========================================================
//                        main function
// 1)Parameters: none
// 2)Returns: integer 0
// 3)Summary: Calls functions to obtain list of movies
// ===========================================================
int main() {
    int x=0;
    bool keepAsking = true;
    Movie* m = createDatabase(x);
    
    while (keepAsking) {
        findMovie(m,x);
        keepAsking = promptToContinue();
    }
    displayFavorites();
    
    //clean heap - ALSO in displayFavorites function....
    //delete m;
    delete[] m;
    return 0;
}
// ===========================================================
//                        numberOfLines
// 1)Parameters: input file
// 2)Returns: integer number of lines in file
// 3)Summary: read input file and count lines
// ===========================================================
int numberOfLines(ifstream& file){
    int count = 0;
    string line;
    
    file.clear();
    file.seekg(0);
    
    //getline returns true if line is read, else false
    while(getline(file, line)){
        count++;
    }
    return count;
}
// ===========================================================
//                        populateMovieFromFile
// 1)Parameters: input file & movie object
// 2)Returns: none
// 3)Summary: Read one line and store info to one Movie object
// ===========================================================
void populateMovieFromFile(ifstream& file, Movie& m){
    string temp;
    
    getline(file, m.title, ',');
    getline(file, temp, ',');
    m.revenue = stod(temp);
    getline(file, m.director, ',');
    getline(file, m.date, ',');
    getline(file, temp);
    m.runtime = stoi(temp);
}
// ===========================================================
//                        displayMovie
// 1)Parameters: movie object passed by constant reference
// 2)Returns: none
// 3)Summary: displays formatted contents of Movie object
// ===========================================================
void displayMovie(const Movie& m){
    
    cout << "\n";
    cout << setw(15) << "Title: " << m.title << endl;
    cout << setw(15) << "Gross Total: " << m.revenue << " billion dollars"
         << endl;
    cout << setw(15) << "Director: " << m.director << endl;
    cout << setw(15) << "Release date: " << m.date << endl;
    cout << setw(15) << "Runtime: " << m.runtime << " minutes" << endl;
}
// ===========================================================
//                        createDatabase
// 1)Parameters: numbers of movies in database
// 2)Returns: Movie pointer pointing to an array of Movie objects
// 3)Summary: Request input file, determine number of lines, and
//      create dynamically-allocated array to store Movie objects
// ===========================================================
Movie* createDatabase(int& x){
    string filename;
    ifstream file;
    
    //Request file name
    do {
        cout << "Please enter filename: ";
        getline(cin, filename);
        file.open(filename);
        
        //check if valid filename
        if (!file)
            cout <<"\n          ERROR: Please enter a valid file name\n"
                 << endl;
        else
            break;
    } while (!file);
    
    //find number of movies
    x = numberOfLines(file);
    //store each movie from file in database(array)
    Movie* arr = new Movie[x];
    file.close();
    file.open(filename); //just in case..
    
    for (int i = 0; i < x; i++){
        populateMovieFromFile(file, arr[i]);
    }
    file.close();
    return arr;
}
// ===========================================================
//                        caseInsensitiveCmp
// 1)Parameters: two strings
// 2)Returns: true if equivalent strings, else false
// 3)Summary: noncase-sensitive comparison of two strings
// ===========================================================
bool caseInsensitiveCmp(string title1, string title2){
    //compare length
    if (title1.size() != title2.size())
        return false;
    else
    {
    //compare each letter
        for (int i = 0; i < title1.size(); i++){
            if (tolower(title1.at(i)) != tolower(title2.at(i)))
                return false;
        }
        return true;
    }
}
// ==============================================================
//                          saveToFile
// 1)Parameters: movie object passed by constant reference
// 2)Returns: integer 0
// 3)Summary: If the file does not exist, create it. If the file
//      does exist, add the Movie object to the end of the file.
// ==============================================================
void saveToFile(const Movie& m){
    //constant AND pass by reference = don't make copy of ALL the movies
    static bool firstCall = true;
    ofstream of;
    
    // if file DNE, then CREATE
    if (firstCall){
        of.open("favorites.txt");
        firstCall = false;
        of << m.title << ", " << m.revenue << ", " << m.director
        << ", " << m.date << ", " << m.runtime << endl;

    }
    //already opened, APPEND
    else {
        of.open("favorites.txt", ios::app);
        of << m.title << ", " << m.revenue << ", " << m.director
        << ", " << m.date << ", " << m.runtime << endl;
        
    }
    of.close();
}
// ===========================================================
//                        findMovie
// 1)Parameters: array of movie objects & number of movies
// 2)Returns: none
// 3)Summary: asks user to search for a movie & save it to
//            a list of favorite movies
// ===========================================================
void findMovie(Movie* m, int x){
    string title;
    bool found = false;
    string c;
    
    cout << "\nEnter a movie title to search for: ";
    getline(cin, title);
    
    //search database for movie
    for (int i = 0; i < x; i++){
        //match found
        if(caseInsensitiveCmp(m[i].title, title)){
            displayMovie(m[i]);
            found = true; //SHOULD SET TRUE AFTER USER DECIDES TO SAVE MOVIE
                        //ELSE IF THEY NEVER SAVE A MOVIE,.... WAIT nvm....?
            //Saving movie if needed
            //check if valid input before saving movie
            while(c != "Y" && c != "y" && c != "N" && c != "n"){
                cout<<"\nWould you like to save the above movie? (Y / N): ";
                getline(cin, c);
                
                if (c == "Y" || c == "y" ){
                    saveToFile(m[i]);
                    cout << "Successfully saved to favorites.txt!"
                         << endl;
                }
                else if (c != "N" && c != "n" ){
                    cout << "\n          ERROR: please enter Y or N"
                         << endl;
                }
            }
        }
    }
    if (!found){
        cout<<"          ERROR: '"<< title << "' not found in database."
            << " Please try again." << endl;
    }
}
// ===========================================================
//                        promptToContinue
// 1)Parameters: none
// 2)Returns: true if 'Y' yes, false if 'N' no
// 3)Summary: determine if student wants to continue or exit
// ===========================================================
bool promptToContinue(){
    string c;
    
    while (true){
        cout << "\nWould you like to exit? (Y / N): ";
        getline(cin, c);
        if (c == "Y" || c == "y" ){
            return false;
        }
        else if (c == "N" || c == "n" ){
            return true;
        }
        else
            cout<<"\n          ERROR: please enter Y or N" << endl;
    }
}
// ===========================================================
//                        displayFavorites
// 1)Parameters: none
// 2)Returns: none
// 3)Summary: display all saved fmovies. If there are no
//            saved movies, display an error
// ===========================================================
void displayFavorites(){
    cout << "Your saved movies are: \n" << endl;
    int lines;
    Movie* arr;
    
    ifstream file;
    file.open("favorites.txt");
    
    lines = numberOfLines(file);
    
    file.close();
    file.open("favorites.txt");
    
    if (lines == 0)
        cout <<setw(15) << "          ERROR: no saved movies";
    else{
        arr = new Movie[lines];
        for (int i = 0; i < lines; i++){
            populateMovieFromFile(file, arr[i]);
            displayMovie(arr[i]);
        }
    }
    file.close();
    
    //clean heap
    delete []arr;
}

/* SAMPLE RUN OF CODE
Please enter filename: random
          ERROR: Please enter a valid file name
Please enter filename: movies.txt

Enter a movie title to search for: random
          ERROR: 'random' not found in database. Please try again.

Would you like to exit? (Y / N): 0
          ERROR: please enter Y or N

Would you like to exit? (Y / N): n

Enter a movie title to search for: FINDING DORY

        Title: Finding Dory
  Gross Total: 1.029 billion dollars
     Director:  Andrew Stanton
 Release date:  6/17/16
      Runtime: 97 minutes

Would you like to save the above movie? (Y / N): p
          ERROR: please enter Y or N

Would you like to save the above movie? (Y / N): Y
Successfully saved to favorites.txt!

Would you like to exit? (Y / N): N

Enter a movie title to search for: AVAtAR

        Title: Avatar
  Gross Total: 2.788 billion dollars
     Director:  James Cameron
 Release date:  12/18/09
      Runtime: 161 minutes

Would you like to save the above movie? (Y / N): N

Would you like to exit? (Y / N): n

Enter a movie title to search for: Minions

        Title: Minions
  Gross Total: 1.159 billion dollars
     Director:  Pierre Coffin & Kyle Blada
 Release date:  7/10/15
      Runtime: 91 minutes

Would you like to save the above movie? (Y / N): y
Successfully saved to favorites.txt!

Would you like to exit? (Y / N): y
Your saved movies are:
        Title: Finding Dory
  Gross Total: 1.029 billion dollars
     Director:   Andrew Stanton
 Release date:   6/17/16
      Runtime: 97 minutes

        Title: Minions
  Gross Total: 1.159 billion dollars
     Director:   Pierre Coffin & Kyle Blada
 Release date:   7/10/15
      Runtime: 91 minutes
free(): invalid pointer


...Program finished with exit code 0
*/
