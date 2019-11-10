#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h"

class heap{
	private:
		class node { // An inner class within heap
        		public:
				std::string id = ""; // The id of this node
				int key; // The key of this node
				void *pData; // A pointer to the actual data
	};
	void percolateUp(int posCur);
	
	void percolateDown(int posCur);
	
	int getPos(node *pn);
	
	int capacity;
	int sizeCurr;
	
	std::vector<node> data; // The actual binary heap
	hashTable *mapping; // maps ids to node pointers

	public:
		heap(int capacity);

		int insert(const std::string &id, int key, void *pv = NULL);

		int setKey(const std::string &id, int key);

		int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

		int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

};
#endif
