/*
 Header file & function definitions for Linked List class
 */
#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include "Node.hpp"
#include<string>
using namespace std;

template<class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList();                   //default
//    LinkedList(const T data);       //overloaded
    ~LinkedList();                  //destructor
//    void printList() const;
//    void append(const T data);
//    void prepend(const T data);
//    bool removeFront();
    void insert(const T data);
    bool remove(const T data);
    bool find(const T data) const;
//    bool isEmpty() const;
//    T getFirst() const;
//    T getLast() const;
};
/*
 default constructor
 */
template <class T>
LinkedList<T>::LinkedList() {
    head = NULL;        //empty list
    tail = NULL;
}
/*
 overloaded constructor
 */
template <class T>
LinkedList<T>::LinkedList(const T data) {
    Node<T>* temp = new Node<T>; //new node
    temp->data = data;
    temp->next = NULL;
    head = temp;        //update head & tail
    tail = temp;
}
/*
 destructor
 */
template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* temp = head;
    while (temp != NULL) {
        temp = head->next;
        delete head;
        head = temp;
    }
    delete temp;
}

/* PRINT
 Paramters: none, Returns: none
 Summary: displays all elements in linked list
 */
template <class T>
void LinkedList<T>::printList() const{
    Node<T>* iter = head;
    while(iter != NULL) {
        cout << iter->data;
        iter = iter->next;
    }
    cout << endl;
}
/* APPEND
 Paramters: any value, Returns: none
 Summary: adds a node to the end of the list
 */
template <class T>
void LinkedList<T>::append(const T data){
    Node<T>* iter = head;               //ptr to iterate
    Node<T>* temp = new Node<T>;        //create new node
    temp->data = data;
    temp->next = NULL;
    
    if(head == NULL) {                  //if empty, head->temp->null
        head = temp;
        tail = temp;
        return;
    }
    while(iter->next != NULL) {         //iterate until last node
        iter = iter->next;
    }
    iter->next = temp;                  //append, iter->temp->null
    tail = temp;                        //update tail ptr

}
/* PRE-APPEND
 Paramters: any value, Returns: none
 Summary: adds a node to the front of the list
 */
template <class T>
void LinkedList<T>::prepend(const T data){
    Node<T>* temp = new Node<T>; //create new node
    temp->data = data;
    temp->next = NULL;
    
    if(head == NULL)             //if empty, head->temp->null
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;      //append temp->head->null
        head = temp;            //update head ptr
    }
}
/* REMOVE 1ST
 Paramters: none, Returns: true if removed, else false
 Summary: removes the front node.
 */
template <class T>
bool LinkedList<T>::removeFront(){
    if(head == NULL)            //empty list, nothing to remove
        return false;
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    return true;
}
/* INSERT
 Paramters: any value, Returns: none
 Summary: insert value into the linked list in correct order
 */
template <class T>
void LinkedList<T>::insert(const T data){
    Node<T>* iter = head;           //ptr to iterate
    Node<T>* prev = NULL;           //hold prev node
    Node<T>* temp = new Node<T>;    //create new node
    temp->data = data;
    temp->next = NULL;

    if(head == NULL)                //empty list
    {
        head = temp;
        tail = temp;
        return;
    }
    while(iter != NULL && iter->data < data) { //find max node
        prev = iter;
        iter = iter->next;
    }
    if (prev == NULL) {         //less than head, prepend
        head = temp;
        temp->next = iter;
    }
    else {                      //insert after prev node
        prev->next = temp;
        temp->next = iter;
        if (iter == NULL)       //if last node, update tail
            tail = temp;
    }
}
/* REMOVE
 Paramters: any value, Returns: true if node found & removed, else false
 Summary: remove the node with that value from list
 */
template <class T>
bool LinkedList<T>::remove(const T data){
    Node<T>* iter = head;
    Node<T>* prev = new Node<T>;
    
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
/* FIND
 Paramters: any value, Returns: true if value if found, else false
 Summary: search for given value in linked list
 */
template <class T>
bool LinkedList<T>::find(const T data) const{
    Node<T>* iter = head;
    while(iter != NULL) {
        if (iter->data == data)
            return true;
        iter = iter->next;
    }
    return false;
}
/* EMPTY?
 Paramters: none, Returns: true if list is empty, else false
 Summary: determine if list has any nodes
 */
template <class T>
bool LinkedList<T>::isEmpty() const{
    if(head == NULL)
        return true;
    return false;
}
/* GET FIRST
 Paramters: none, Returns: value stored in first node of list
 Summary: get first node in list
 */
template <class T>
T LinkedList<T>::getFirst() const{
    if(head == NULL)
        return NULL;
    return head->data;
}
/* GET LAST
 Paramters: none, Returns: value stored in last node of list
 Summary: get last node in list
 */
template <class T>
T LinkedList<T>::getLast() const{
    if(head == NULL)
        return NULL;
    
    Node<T>* iter = new Node<T>;        //ptr to iterate
    iter = head;
    while(iter->next != NULL) {         //iterate until last node
        iter = iter->next;
    }
    return iter->data;
}

#endif /* LinkedList_h */
