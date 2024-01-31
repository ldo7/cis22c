#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

template<class ItemType>
class HashTable
{
private:
    HashNode<ItemType>* hashAry;
    int hashSize;
   int count;
    
public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
    HashTable(int n)    { count = 0; hashSize = n;    hashAry = new HashNode<ItemType>[hashSize]; }
    ~HashTable(){ delete [] hashAry; }

    int getCount() const    { return count; }
   int getSize() const { return hashSize; }
   double getLoadFactor() const {return 100.0 * count / hashSize; }
    HashNode<ItemType>* getHashArray() const { return hashAry; }
   bool isEmpty() const    { return count == 0; }
   bool isFull()  const    { return count == hashSize; }
    
   bool insert(const ItemType &itemIn, int h(const ItemType &key, int size) );
   bool remove(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
   int  search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const;
    void printTable(int h(const ItemType &key, int size), void visit(const ItemType &)) const;
    void GetCollisionNames(int index, const ItemType &key, int h(const ItemType &key, int size));

    //hash resize functions
    bool isPrime(int num);
    int nextPrime(int num);
    void HashResize(int h(const ItemType &key, int size));
};


/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert( const ItemType &itemIn, int h(const ItemType &key, int size) )
{
    double loadFactor = 100.0 * count / hashSize;
    if(loadFactor >= 75.0)
    {
        HashResize(h);
        return false;
    }
        
    int bucket = h(itemIn,hashSize);
    int probing = 0;
    while(probing < hashSize){
        //insert in next empty bucket
        if(hashAry[bucket].getOccupied() <= 0 ){ //0 or -1
            hashAry[bucket].setItem(itemIn);
            hashAry[bucket].setOccupied(1);
            hashAry[bucket].setNoCollisions(probing);
            count++;
            return true;
        }
        //next bucket index
        bucket = (bucket + 1) % hashSize;
        probing++;
    }
    return false;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
   if found:
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record (occupied = -1: deleted!)
     - returns true
   if not found: - returns false
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
    int bucket = h(key,hashSize);;
    int probing = 0;
    while(probing < hashSize){
        //find filled bucket & compare key
        if(hashAry[bucket].getOccupied() == 1 && hashAry[bucket].getItem()==key){
            itemOut = hashAry[bucket].getItem();
            hashAry[bucket].setOccupied(-1); //empty after occupied
            hashAry[bucket].setNoCollisions(0);
            ItemType empty;
            hashAry[bucket].setItem(empty);
            count--;
            return true;
        }
        //next bucket index
        bucket = (bucket + 1) % hashSize;
        probing++;
    }
    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const
{
    int bucket = h(key,hashSize);;
    int probing = 0;
    while(probing < hashSize){
        //find filled bucket & compare key
        if(hashAry[bucket].getOccupied() == 1 && hashAry[bucket].getItem() == key){
            itemOut = hashAry[bucket].getItem();
            return hashAry[bucket].getNoCollisions();
        }
        //next bucket index
        bucket = (bucket + 1) % hashSize;
        probing++;
    }
   return -1;
}

/*~*~*~*
   Print all items in the hash table
*~**/
template<class ItemType>
void HashTable<ItemType>::printTable(int h(const ItemType &key, int size), void visit(const ItemType &)) const
{
    if ( count == hashSize)
        return;
    ItemType item = hashAry[0].getItem();
    int bucket = h(hashAry[0].getItem(),hashSize);
    int probing = 0;
    while(probing < hashSize){
        //get item in next filled bucket
        if(hashAry[bucket].getOccupied() == 1){
//            std::cout << hashAry[bucket].getItem();
            ItemType item = hashAry[bucket].getItem();
            visit(item);
        }
        //next bucket index
        bucket = (bucket + 1) % hashSize;
        probing++;
    }
}

//
template<class ItemType>
bool HashTable<ItemType>::isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

//
template<class ItemType>
int HashTable<ItemType>::nextPrime(int num)
{
    while (!isPrime(num))
    {
        num++;
    }
    return num;
}

/*
 
 */
template<class ItemType>
void HashTable<ItemType>::HashResize(int h(const ItemType &key, int size))
{
    int newSize = nextPrime(hashSize * 2);
    HashNode<ItemType>* newHashAry = new HashNode<ItemType>[newSize];

    // Rehash existing entries to the new hashtable
    for (int i = 0; i < hashSize; ++i)
    {
        if (hashAry[i].getOccupied() > 0)
        {
            int bucket = h(hashAry[i].getItem(), newSize);
            int probing = 0;
            while (probing < newSize)
            {
                if (newHashAry[bucket].getOccupied() <= 0)
                {
                    newHashAry[bucket] = hashAry[i];
                    break;
                }
                bucket = (bucket + 1) % newSize;
                probing++;
            }
        }
    }

    delete[] hashAry;
    hashAry = newHashAry;
    hashSize = newSize;
}

/*
 
 */
template<class ItemType>
void HashTable<ItemType>::GetCollisionNames(int index, const ItemType &key, int h(const ItemType &key, int size))
{
    int bucket = h(key,hashSize);;
    
    //loops until finding name with longest collisions
    while(bucket != index && key != hashAry[bucket].getItem())
    {
        if(hashAry[bucket].getOccupied() == 1)
        {
            //outputs longest path of collisions
            std::cout << hashAry[bucket].getItem().getName() << " ";
        }
        //next bucket index
        bucket = (bucket + 1) % hashSize;
        
    }
}
#endif // HASHTABLE_H_
