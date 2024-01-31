class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *head;
    int length;

public:
    LinkedList();
    ~LinkedList();
    int getLength() const {return length;}
    void insert(T data);
    bool remove(T data);
    void print() const;
    bool search(string, T &data) const;
};

constructor()
    head = new Node; // head points to the sentinel node
    head->next = NULL;
    length = 0;

destructor()
    Node* cur = head->next; //head = head->next b/c sentinel node
    Node* pNext;
    while(cur != NULL)
        pNext = cur->next;
        delete cur;
        cur = pNext;
    }
    delete head; // delete sentinel node
}

insert(T data)
    Node *newNode;  // A new node
    Node *pCur;     // To traverse the list
    Node *pPre;     // The previous node
    
    // Allocate a new node and store dataIn there.
    newNode = new Node;
    newNode->park = dataIn;

    // Initialize pointers
    pPre = head;
    pCur = head->next;

    // Find location: skip all nodes whose code is less than dataIn's code
    while (pCur && newNode->park.getCode() > pCur->park.getCode())
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;
    
    // Update the counter
    length++;
}

remove(T data)
    Node *pCur;       // To traverse the list
    Node *pPre;       // To point to the previous node
    bool deleted = false;
    
    // Initialize pointers
    pPre = head;
    pCur = head->next;

    // Find node containing the target: Skip all nodes whose code is less than the target
    while (pCur != NULL && pCur->park.getCode() < target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // If found, delete the node
    if (pCur && pCur->park.getCode() == target)
    {
        pPre->next = pCur->next;
        delete pCur;
        deleted = true;
        length--;
    }
    return deleted;
}

print() const
{
     Node *pCur;  // To move through the list

     // Position pCur: skip the head of the list.
     pCur = head->next;

     // While pCur points to a node, traverse the list.
     while (pCur)
     {
         // Display the value in this node.
//         pCur->park.hDdisplay();
         cout << pCur->park;
         
         // Move to the next node.
         pCur = pCur->next;
    }
    cout << endl;
}

search(T data) const
{
    bool found = false; // assume target not found
    Node *pCur = head;  // To move through the list
    
    // Find node containing the target: Skip all nodes whose code is less than the target
    while (pCur != NULL && pCur->park.getCode() < target)
    {
        pCur = pCur->next;
    }
    
    // If found
    if (pCur && pCur->park.getCode() == target){
        found = true;
        dataOut = pCur->park;
    }
    
    return found;
}

