#Makefile for text mancala

all: mancala


mancala: stateround2.cpp
	g++ -o state textcala.cpp -std=c++11

clean:
	rm -f state *.o

