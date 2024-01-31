/* *~*~*
  Specification file for the Customer class
  Written By: A. Student
  Changed by:
  IDE:
  *~**/
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

using std::string;

class  Customer; // Forward Declaration

// Function Prototypes for friend functions
void Display(const Customer &);

class Customer
{
private:
    int mileage;//a
    int year; //b
    int seq; //c
    int serial;
	 string name;
	
public:
    Customer();
    Customer(int y, int m, int s, const std::string& n);

    int getYear() const { return year; }
    void setYear(int newYear) { year = newYear; }
    int getMileage() const { return mileage; }
    void setMileage(int newMileage) { mileage = newMileage; }
    int getSeq() const { return seq; }
    void setSeq(int newSeq) { seq = newSeq; }
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }
    int getSerial() const { return serial; }
    void setSerial(int newSerial) { serial = newSerial; }
    
    //friend
    friend void display(const Customer &);

    // Overloaded operators
    bool operator<(const Customer& other) const { return seq < other.seq; }
    bool operator>(const Customer& other) const { return seq > other.seq; }
    bool operator==(const Customer& other) const { return seq == other.seq; }
};
#endif
