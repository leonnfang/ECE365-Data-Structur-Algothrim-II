#include <iostream>
#include "heap.h"

//constructor
heap::heap(int capacity) {
    heap::capacity = capacity;
    heapSize = 0;
    data.resize(capacity + 1);
    allocate = new hashTable(capacity * 2);
}

//insert node into the heap
int heap::insert(const std::string &id, int key, void *pv) {
    if (heapSize == data.size() - 1) return 1;
    if (allocate->contains(id)) return 2;
    node temp;
    temp.id = id;
    temp.key = key;
    temp.pointData = pv;
    data[++heapSize] = temp;

    allocate->insert(id, &data[heapSize]);
    percolateUp(heapSize);
    return 0;
}

//set key value to a node given a string id
int heap::setKey(const std::string &id, int key) {
    if (!allocate->contains(id)) return 1;
    else{
        node *n = static_cast<node *>(allocate->getPointer(id));
        int tempKey = n->key;
        n->key = key;
        int pos = getPos(n);
        if(key > tempKey){
            percolateDown(pos);
        }
        else if(key < tempKey){
            percolateUp(pos);
        }
        return 0;
    }
}

//remove the node of minimum key value
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (heapSize == 0) return 1;
    else{
        if(pId != NULL) *pId = data[1].id;
        if(pKey != NULL) *pKey = data[1].key;
        if(ppData != NULL) *(static_cast<void **> (ppData)) = data[1].pointData;
        allocate->remove(data[1].id);
        data[1] = data[heapSize--];
        percolateDown(1);
        return 0;
    }
}

//remove node given a string id
int heap::remove(const std::string &id, int *pKey, void *ppData) {
    if (!allocate->contains(id)) return 1;
    else{
        node *n = static_cast<node *> (allocate->getPointer(id));
        if (pKey != nullptr) *pKey = n->key;
        if(ppData != nullptr) *(static_cast<void **> (ppData)) = n->pointData;

        int tempKey= n->key;
        allocate->remove(id);
        *n = data[heapSize--];
        int newKey = n->key;
        int pos = getPos(n);

        if(tempKey < newKey)
            percolateDown(pos);
        if(tempKey > newKey)
            percolateUp(pos);
        return 0;
    }
}

//percolating up
void heap::percolateUp(int pos){
    node temp = data[pos];
    int parent = pos / 2;

    while(pos > 1 && (temp.key) < (data[parent].key)){
        data[pos] = data[parent];
		    allocate->setPointer(data[pos].id, &data[pos]);
        pos = parent;
        parent = pos / 2;
    }
    data[pos] = temp;
    allocate->setPointer(data[pos].id, &data[pos]);
}

//percolating down
void heap::percolateDown(int pos){
    int child;
    node temp = data[pos];

    while((pos * 2) <= heapSize){
        child = pos * 2;
        if((child != heapSize) && (data[child].key > data[child + 1].key)){
            child++;
        }
        if(temp.key > data[child].key){
            data[pos] = data[child];
            allocate->setPointer(data[pos].id, &data[pos]);
        }
        else
            break;
        pos = child;
    }
    data[pos] = temp;
    allocate->setPointer(data[pos].id, &data[pos]);
}

//getting the position of a node
int heap::getPos(node *n) {
    int pos = n - &data[0];
    return pos;
}
