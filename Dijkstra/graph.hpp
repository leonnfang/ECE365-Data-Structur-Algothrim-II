#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "hash.h"
#include "heap.h"
#include <fstream>
#include <sstream>
#include <list>
#include <string>

class Graph {
	public:
		Graph (long const & capacity);
		int readFile (std::ifstream & inFile);
		int writeFile (std::ofstream & outFile);

		int insert (std::string const & v1, std::string const & v2, long dist);
		bool findVertex (std::string const & Vertex);
		void runDijkstra (std::string const & startId) ;

	private:
		//set infinity to 100000000
		const int INF = 100000000;

		long capacity;
		struct Vertex;

		typedef struct Edge {
			unsigned long cost;
			Vertex * dest;
		} Edge;

		typedef struct Vertex {
				std::string ID;
				std::list<Edge> adj;
				bool known;
				long long dist;
				std::list<std::string> path;
		} Vertex;
		std::list<Vertex *> VertexList; 
		hashTable * VertexID;
		void update(std::string const & vertex, Vertex* &vP);

};

#endif
