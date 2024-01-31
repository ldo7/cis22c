template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct Node
    {
      T value;
      Node *next;
    };
    Node *top;     
    int length;

public:
    Stack();
    ~Stack();
    bool push(T);
    T pop();
    T peek() {return top->value;}
    bool isEmpty() {return top==NULL;//length==0}
    int getLength() {return length;}
};

constructor()
    top = NULL;
    length = 0;

destructor()
//    Node* cur = top;
//    while(cur != NULL)
//        cur = cur->next;
//        delete top;
//        top = cur;
    while(!top)             //slightly more efficient 
        Node* cur = top;
        top = top->next;
        delete cur;

push(T data) //prepend
   Node *newNode = new Node;    //new node
   newNode->data = data;
   newNode->next = top;         //prepend
   top = newNode;               //update top
   length++;
   return true;                 //false if newNode = null
}

pop() //remove head
//    if(head == NULL)            //if empty, do nothing
//        return;
//    //if(length == 0) //alternative....
    T data = top->data;         //save value to return
    Node* newTop = top->next;
    delete top;                 //delete
    top = newTop;               //update
    length--;
    return data;

