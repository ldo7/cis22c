//
//  BinarySearchTree.h
//  testDelete
//
//  Created by Lani Do on 6/1/23.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // remove a node if found
    //bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    // find the smallest node
//    bool findSmallest(ItemType &returnedItem) const;
    // find the largest node
//    bool findLargest(ItemType &returnedItem) const;
    
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
    
   // find the smallest node
//   BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;
    
   // find the largest node
//   BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;
   
   // internal remove node: locate and delete target node under nodePtr subtree
   // BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success);
    
   // delete target node from tree, called by internal remove node
   //BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);
    
   // remove the leftmost node in the left subtree of nodePtr
   //BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);
    
};


///////////////////////// public function definitions ///////////////////////////
// Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    
    this->count++;
    
    return true;
}

// Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    /* Write your code here */
    temp = _search(this->rootPtr, anEntry);

    if(temp){ // != NULL
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}


//////////////////////////// private functions ////////////////////////////////////////////
///
// Implementation for the search operation: recursive algorithm
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType &target) const
{
    BinaryNode<ItemType>* found = nullptr;
    
   if (nodePtr) // != NULL
   {
       ItemType item = nodePtr->getItem();
       if(item == target){
           found = nodePtr;
       }
       else if (item > target)
           found = _search(nodePtr->getLeftPtr(),target);
       else
           found = _search(nodePtr->getRightPtr(),target);
   }
    return found;
}


// Implementation of the insert operation: iterative algorithm
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if(!nodePtr)
        nodePtr = newNodePtr;
    {
       if (nodePtr->getItem() > newNodePtr->getItem()){
            _insert(nodePtr->getLeftPtr(),newNodePtr);
            nodePtr->setLeftPtr(newNodePtr);
       }
       else{
            _insert(nodePtr->getRightPtr(),newNodePtr);
            nodePtr->setRightPtr(newNodePtr);
       }
   }
   return nodePtr;
}


#endif /* BinarySearchTree_h */
