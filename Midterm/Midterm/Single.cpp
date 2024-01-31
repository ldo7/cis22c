template <class T>
class LinkedList {
private:
    Node* head;
    Node* tail;
public:
    LinkedList();
    ~LinkedList();
    void printList() const;
    void append(const T data);
    void prepend(const T data);
    bool removeFront();
    void insert(const T data);
    bool remove(const T data);
    bool find(const T data) const;
};

constructor()
    head = NULL;        //empty list
    tail = NULL;

destructor()
    Node* iter = head;
    while (iter != NULL) {
        iter = head->next;
        delete head;
        head = iter;
append(const T data){
    Node* iter = head;                  //iterate
    Node* newNode = new Node<T>;        //new node
    newNode->data = data;
    newNode->next = NULL;
    
    if(head == NULL) {                  //if empty
        head = newNode;
        tail = newNode;
        return;
    }
    while(iter->next != NULL) {         //iterate until last node
        iter = iter->next;
    }
    iter->next = newNode;               //append,
    tail = newNode;                     //update tail

}
prepend(const T data){
    Node* newNode = new Node;       //new node
    newNode->data = data;
    newNode->next = head;           //prepend
    head = newNode;                 //update head
    
    if(head == NULL)                //if empty
        tail = newNode;
    
}
insert(const T data){
    Node* curr = head;           //iterate
    Node* prev = NULL;           //prev node
  
    Node* newNode = new Node;    //new node
    newNode->data = data;
    newNode->next = NULL;

    if(head == NULL)            // if empty list
    {
        head = newNode;
        tail = newNode;
        return;
    }
    while(curr != NULL && curr->data < data) {  //find max node
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {         //less than head, PREPREND
        head = newNode;
        newNode->next = curr;
    }
    else {                      //insert after prev node
        prev->next = newNode;
        newNode->next = curr;
        if (curr == NULL)       //if last node, update tail
            tail = newNode;
    }
}
removeFront(){
    if(head == NULL)            //empty list, nothing to remove
        return false;
    Node<T>* newNode = head->next;
    delete head;
    head = newNode;
    return true;
}
remove(const T data){
    Node* iter = head;
    Node* prev = new Node;
    
    if(head == NULL)                //empty list, nothing removed
        return false;
    if (head->data == data)         //delete head
    {
        iter = head->next;
        delete head;
        head = iter;
        return true;
    }
    while(iter != NULL){            //iterate until node found
        if(iter->data == data){
            prev->next = iter->next;    //remove
            if(prev->next == NULL)      //if last node, update tail
                tail = prev;
            delete iter;
            return true;
        }
        prev = iter;
        iter = iter->next;
    }
    return false;                   //not found, nothing removed
}
/*
 extra operators (not in stack/queue)
 */
find(const T data) const{ // traverse + if condition
    Node<T>* iter = head;
    while(iter != NULL) {
        if (iter->data == data)
            return true;
        iter = iter->next;
    }
    return false;
}
print() const{
    Node<T>* iter = head;
    while(iter != NULL) {
        cout << iter->data;
        iter = iter->next;
    }
    cout << endl;
}
isEmpty() const{
    return head == NULL
}
