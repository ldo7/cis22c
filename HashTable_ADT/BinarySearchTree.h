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
    bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
   
   // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success);
    
   // delete target node from tree, called by internal remove node
   BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);
    
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
    temp = _search(this->rootPtr, anEntry);

    if(temp){ // != NULL
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}

// Wrapper for _remove
//
template<class Temp>
bool BinarySearchTree<Temp>::remove(const Temp& item)
{
    bool success = false;
    this->rootPtr = _remove(this->rootPtr, item, success);
    return success;
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
    else
    {
       if (nodePtr->getItem() > newNodePtr->getItem()){
         nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(),newNodePtr));

       }
       else{
         nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(),newNodePtr));
       }
   }
   return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool& success)
{
    if (nodePtr == nullptr) {
        success = false;
        return nullptr;
    }
    
    if (nodePtr->getItem() > target) {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    }
    else if (nodePtr->getItem() < target) {
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    }
    else {
        nodePtr = _removeNode(nodePtr);
        success = true;
    }
    
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType>* targetNodePtr)
{
    if (targetNodePtr->isLeaf()) {
        delete targetNodePtr;
        targetNodePtr = nullptr;
        return targetNodePtr;
    }
    else if (targetNodePtr->getLeftPtr() == nullptr) {
        BinaryNode<ItemType>* nodeToDelete = targetNodePtr;
        targetNodePtr = targetNodePtr->getRightPtr();
        delete nodeToDelete;
        return targetNodePtr;
    }
    else if (targetNodePtr->getRightPtr() == nullptr) {
        BinaryNode<ItemType>* nodeToDelete = targetNodePtr;
        targetNodePtr = targetNodePtr->getLeftPtr();
        delete nodeToDelete;
        return targetNodePtr;
    }
    else {
        ItemType newNodeValue;
        targetNodePtr->setRightPtr(_removeLeftmostNode(targetNodePtr->getRightPtr(), newNodeValue));
        targetNodePtr->setItem(newNodeValue);
        return targetNodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor){
    if (nodePtr->getLeftPtr() == nullptr) {
         successor = nodePtr->getItem();
         return _removeNode(nodePtr);
     }
     else {
         nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), successor));
         return nodePtr;
     }
}

#endif /* BinarySearchTree_h */
























