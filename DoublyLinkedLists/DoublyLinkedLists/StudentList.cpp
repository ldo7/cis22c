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
Constructor()
{
    head = new ListNode; // head points to the sentinel node
    
    head->stu.gpa = -1;
    head->stu.name = "";
    head->forw = head;
    head->back = head;
    
    count = 0;
}
displayforw() const
{
    ListNode *pCur;  // To move through the list

    // Position pCur: skip the head of the list.
    pCur = head->forw;

    // While pCur points to a node, traverse the list.
    while (pCur != head)
    {
        // Display the value in this node.
        cout << pCur->stu.gpa << " " << pCur->stu.name << endl;

        // Move to the next node.
        pCur = pCur->forw;
    }
    cout << endl;
}
displayback() const
{
    ListNode *pCur;  // To move through the list

    // Position pCur: skip the head of the list.
    pCur = head->back;

    // While pCur points to a node, traverse the list.
    while (pCur != head)
    {
        // Display the value in this node.
        cout << pCur->stu.gpa << " " << pCur->stu.name << endl;

        // Move to the next node.
        pCur = pCur->back;
    }
    
    cout << endl;
}
insert(Student dataIn)
{
    ListNode *newNode;  // A new node
    ListNode *pCur;     // To traverse the list
    
    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->stu = dataIn;

    // Initialize pointers
    pCur = head->forw;
   
    // Find location: skip all nodes whose name is less than dataIn's name
    while (pCur != head && pCur->stu.name < dataIn.name)
    {
        pCur = pCur->forw;
    }

    if(pCur->stu.name != dataIn.name){
        // Insert the new node between pPre and pCur
        ListNode *pPre = pCur->back;     // The previous node
        pPre->forw = newNode;
        newNode->forw = pCur;
        newNode->back = pPre;
        pCur->back = newNode;
//        success = true
        
        // Update the counter
        count++;
    }
    else{
        cout << dataIn.name << " - rejected: duplicate key!" << endl;
    }
}
remove(string target)
{
    ListNode *pCur;     // To traverse the list
    bool success = false;
    
    // Initialize pointers
    pCur = head->forw;
    
    while (pCur != head && pCur->stu.name < target)
    {
        pCur = pCur->forw;
    }
    
    if(pCur != head && pCur->stu.name == target){   //item was found
        pCur->back->forw = pCur->forw;
        pCur->forw->back = pCur->back;
        success = true;
        count--;
    }
 
    return success;
}

// **************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
// **************************************************
StudentList::~StudentList()
{
  
}
