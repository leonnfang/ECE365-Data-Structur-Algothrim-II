//Jungang Fang hashtable
// Created by fang on 9/12/19.
//

#include "hash.h"
#include <string>

unsigned int prime[]={53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

hashTable::hashTable(int size) {
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);

    for (int i = 0; i < data.size(); i++){
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
}
int hashTable::insert(const std::string &key, void *pv) {
    int index = hash(key);
    if(contains(key)){        
        return 1;
    }
    if((2 * filled) >= capacity){       
        if(!rehash()){
            return 2;
        }
    }
    while (data[index].isOccupied) {
        if (data[index].key == key){
            if (data[index].isDeleted){
                data[index].isDeleted = false;
                return 0;
            }
            else
                return 1;
        }
        if (index != capacity-1)
            index++;
        else
            index = 0;
    }
    data[index].key = key;
    data[index].isOccupied = true;
    data[index].isDeleted = false;
    data[index].pv = pv;
    filled++;
    return 0;
}
bool hashTable::contains(const std::string &key) {
    if (findPos(key) == -1)
        return false;
    else
        return true;
}
void *hashTable::getPointer(const std::string &key, bool *b) {
    int index = findPos(key);
    if (index == -1) {
	if(b != nullptr){
      	*b = false;
      }
    	return NULL;
    }
    else {
        if(b != nullptr){
            *b = true;
        }
	return data[index].pv;
    }
}
int hashTable::setPointer(const std::string &key, void *pv){
    int index = findPos(key);
    if (index == -1){
        return 1;
    }
    else {
        data[index].pv = pv;
        return 0;
    }
}
bool hashTable::remove(const std::string &key) {
    int index = findPos(key);
    if (index == -1) {
		    return false;
    }
    else{
		    data[index].isDeleted = true;
		    return true;
    }
}
int hashTable::hash(const std::string &key){
    return (std::hash<std::string>{} (key)) % capacity;
}
int hashTable::findPos(const std::string &key) {
    int index = hash(key);
    while (data[index].isOccupied) {
        if (data[index].key == key && !data[index].isDeleted)
            return index;
        else if (index == capacity-1)
            index = 0;
        else
            index++;
    }
    return -1;
}

bool hashTable::rehash() {
    std::vector<hashItem> temp = data;
    int prev_cap = capacity;
    capacity = getPrime(2 * capacity);
    data.resize(capacity);
    if(data.size() != capacity){
        return false;
    }

    for(int i = 0; i < capacity; ++i){
        data[i].isOccupied = false;
        data[i].isDeleted = true;
    }
    filled = 0;
    for (int i = 0; i < temp.size(); ++i)
        if (temp[i].isOccupied && !temp[i].isDeleted)
            insert(temp[i].key, temp[i].pv);
    return true;
}


unsigned int hashTable::getPrime(int size) {
    int i = 0;
    for(i = 0; i < (sizeof(prime) / sizeof(prime[0])); ++i){
        if(prime[i] >= size*2)
        break;
    }
    return prime[i];
}
