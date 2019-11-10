#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

int main () {
	string graph, startId, pathFile;
	ifstream inFile;
	ofstream outFile;

	Graph dijks(10);
	chrono::duration<double> elapsed_seconds;

	// Input file
	while (!inFile.is_open ()) {
		cout << "Enter name of graph file: ";
		cin >> graph;
		inFile.open (graph); 
	}
	dijks.readFile(inFile);

	// Enter starting vertex id
	do{
		cout << "Enter a valid vertex id for the staring vertex: ";
		cin >> startId;
	} while(!dijks.findVertex (startId)); 
	
	// Output the time
	auto start =chrono::system_clock::now();
	dijks.runDijkstra(startId);
	auto end = chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << elapsed_seconds.count () << endl;

	// Output file
	while (!outFile.is_open ()) {
		cout <<"Enter name of output file: ";
		cin >> pathFile;
		outFile.open (pathFile, ios::out | ios::trunc);
	}

	if(dijks.writeFile (outFile))
		cerr << "Writing Error in printing path" << endl;
	
	// Close Files
	inFile.close ();
	outFile.close ();
	return 0;
}

