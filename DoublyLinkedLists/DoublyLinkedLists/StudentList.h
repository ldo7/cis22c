// Sorted Circular Doubly-Linked List with Sentinel Node
// Specification file for the Student List class
// Written by: A. Student
// Reviewed by: <Write your name here>
// IDE:


#ifndef STUDENTLIST_H
#define STUDENTLIST_H

struct Student
{
    double gpa;
    std::string name;
};

class StudentList
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        Student stu;     // The value in this node
        ListNode *forw;  // To point to the next node
        ListNode *back;  // To point to the previous node
    };
    
    ListNode *head;      // List head pointer
    int count;           // To keep track of the number of nodes in the list
    

public:
    StudentList();  // Constructor
   ~StudentList();   // Destructor
    
    // Linked list operations
    int getCount() const {return count;}
    void insertNode(Student);
    bool deleteNode(std::string);
    //void searchList() const;
    void displayListForw() const;
    void displayListBack() const;
};
#endif
