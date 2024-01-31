template <class T>
class Queue{
private:
   struct QueueNode {
       T value;
       QueueNode *next;
   };
   QueueNode *front;
   QueueNode *rear;
   int length;

public:
    Queue();
   ~Queue();
   bool push(T); 
   T pop();
    T peek() {return front->value; }
    T peekRear() {return rear->value; }
    int getLength() {return length; }
    bool isEmpty() { return front==NULL; //length==0 }
};

constructor()
    front = rear = NULL;
    length = 0;

destructor()
    Node* cur = front;
    while(cur != NULL)
        cur = cur->next;
        delete front;
        front = cur;

push(T data) // enqueue / append
   Node* newNode = new Node;    //new node
   newNode->data = data;
   newNode->next = NULL;
   
   // update ptrs
   if (!front)               //if empty, update head
       front = newNode;
   else
       rear->next = newNode; //append 
       
   rear = newNode;          //update tail
   length++;

   return true;

pop()  //remove head
//    if(length == 0)            //if empty, do nothing
//        return;
    if(length == 1)             //if last node, update tail
        rear = NULL;
    T data = front->data;       //save value to return
    Node* newNode = front->next;
    delete front;               //delete
    front = newNode;            //update
    length--;
    return data;
