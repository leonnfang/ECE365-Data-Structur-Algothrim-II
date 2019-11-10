.PHONY: clean debug run backup

runDijkstra.exe: runDijkstra.o graph.o heap.o hash.o
	g++ -std=c++11 graph.o heap.o hash.o runDijkstra.o -o runDijkstra.exe

runDijkstra.o: runDijkstra.cpp
	g++ -c -std=c++11 runDijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c -std=c++11 heap.cpp heap.h

hash.o: hash.cpp hash.h
	g++ -c -std=c++11 hash.cpp hash.h

graph.o:graph.cpp graph.hpp
	g++ -c -std=c++11 graph.cpp graph.hpp

debug:
	g++ -g -std=c++11 -o debugDijkstra.out runDijkstra.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
