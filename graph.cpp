#include "graph.hpp"
#include <limits>
#include <iterator>

Graph::Graph (long const & capacity){
	this->capacity=0;
	this->VertexID = new hashTable(capacity*2);
}

int Graph::readFile (std::ifstream & inFile) {
	std::string v1, v2;
	long dist;
    while (inFile>>v1>>v2>>dist){
		this->insert (v1, v2, dist);
	}
	return 0;
}

void Graph::update(std::string const & vertex, Vertex* &vP){
	if (this->findVertex (vertex)) {
		vP = (Vertex *) this->VertexID->getPointer (vertex);
	}
	else {
		//default list constructor
		vP = new Vertex();  
		vP->ID = vertex;
		vP->known = false;
		vP->dist = INF;
		// insert new Vertex at end of VertexList
		this->VertexList.push_back (vP); 		
		this->VertexID->insert(vertex, vP);
		this->capacity++;
	}

	return;
};

int Graph::insert (std::string const & v1, std::string const & v2, long dist){
	Vertex* vP1 = nullptr,* vP2 = nullptr;
	Edge edge;
	this->update(v1,vP1);
	this->update(v2,vP2);
	
	edge.cost = dist;
	edge.dest = vP2;
	vP1->adj.push_back (edge);
	return 0;
}

// determine whether it has the vertex
bool Graph::findVertex (std::string const & Vertex){
	return this->VertexID->contains(Vertex);
}

void Graph::runDijkstra (std::string const & startId){
	Vertex * start = (Vertex *) this->VertexID->getPointer(startId); 
	start->dist = 0;
	start->path.push_back (startId);

 	//initialize a heap
	heap binHeap (this->capacity);
	binHeap.insert(startId,start->dist,start);

	for (std::list<Vertex *>::const_iterator it = this->VertexList.begin (), end = this->VertexList.end (); it != end; ++it) {
		if ((*it)->ID != startId) binHeap.insert((*it)->ID, (*it)->dist, *it);
	}

	Vertex * waitedVertex;
	for (int i = 0; i < this->capacity; ++i) {
		binHeap.deleteMin (NULL, NULL, &waitedVertex); 
		for (std::list<Edge>::const_iterator it = waitedVertex->adj.begin (), end = waitedVertex->adj.end (); it != end && waitedVertex->dist!=INF; ++it) {
			
			if (!it->dest->known && it->dest->dist > (it->cost + waitedVertex->dist)) {
				// update path
				it->dest->path.clear();
				it->dest->path.insert (it->dest->path.begin (), waitedVertex->path.begin (), waitedVertex->path.end ());
				it->dest->path.push_back (it->dest->ID);

				// update distance and key
				it->dest->dist = (it->cost + waitedVertex->dist);
				binHeap.setKey (it->dest->ID, (it->cost + waitedVertex->dist));//setkey to v.dist + cvw
			}
		}
		waitedVertex->known = true;
	}
}

int Graph::writeFile (std::ofstream & outFile){
	for (std::list<Vertex *>::const_iterator it = this->VertexList.begin (), end = this->VertexList.end (); it != end; ++it) {
		outFile << (**it).ID << ": ";
		if ((**it).dist == INF) {
			outFile << "NO PATH" << std::endl;
		}else{
			outFile << (*it)->dist << " [";
			for (std::list<std::string>::const_iterator ti = (*it)->path.begin(), last = (*it)->path.end (); ti != last; ++ti) {
				outFile << *ti;
				if (std::next (ti, 1) != last) outFile << ", ";
			}
			outFile << "]" << std::endl;
		}
	}
	return 0;
}
