#include "heap.h"

heap::heap(int capacity) {
    heap::capacity = capacity;
    sizeCurr = 0;
    data.resize(capacity + 1);
    mapping = new hashTable(capacity * 2);
}

void heap::percolateUp(int posCur){
    node tmp = data[posCur];
    int parent = posCur / 2;

    while(posCur > 1 && (tmp.key) < (data[parent].key)){
        data[posCur] = data[parent];
		    mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur = parent;
        parent = posCur / 2;
    }
    data[posCur] = tmp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}
void heap::percolateDown(int posCur){
    int child;
    node tmp = data[posCur];

    while((posCur * 2) <= sizeCurr){
        child = posCur * 2;
        if((child != sizeCurr) && (data[child].key > data[child + 1].key)){
            child++;
        }
        if(tmp.key > data[child].key){
            data[posCur] = data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else
            break;
        posCur = child;
    }
    data[posCur] = tmp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (sizeCurr == data.size() - 1) return 1;
    if (mapping->contains(id)) return 2;
    node tmp;
    tmp.id = id;
    tmp.key = key;
    tmp.pData = pv;
    data[++sizeCurr] = tmp;

    mapping->insert(id, &data[sizeCurr]);
    percolateUp(sizeCurr);
    return 0;
}

int heap::setKey(const std::string &id, int key) {
    if (!mapping->contains(id)) return 1;
    else{
        node *pn = static_cast<node *>(mapping->getPointer(id));
        int tmpKey = pn->key;
        pn->key = key;
        int pos = getPos(pn);
        if(key > tmpKey){
            percolateDown(pos);
        }
        else if(key < tmpKey){
            percolateUp(pos);
        }
        return 0;
    }
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (sizeCurr == 0) return 1;
    else{
        if(pId != NULL) *pId = data[1].id;
        if(pKey != NULL) *pKey = data[1].key;
        if(ppData != NULL) *(static_cast<void **> (ppData)) = data[1].pData;
        mapping->remove(data[1].id);
        data[1] = data[sizeCurr--];
        percolateDown(1);
        return 0;
    }
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    if (!mapping->contains(id)) return 1;
    else{
        node *pn = static_cast<node *> (mapping->getPointer(id));
        if (pKey != nullptr) *pKey = pn->key;
        if(ppData != nullptr) *(static_cast<void **> (ppData)) = pn->pData;

        int tmpKey= pn->key;
        mapping->remove(id);
        *pn = data[sizeCurr--];
        int newKey = pn->key;
        int pos = getPos(pn);

        if(tmpKey < newKey)
            percolateDown(pos);
        if(tmpKey > newKey)
            percolateUp(pos);
        return 0;
    }
}
