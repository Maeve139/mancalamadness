#Makefile for text mancala

all: mancala


mancala: textcala.cpp
	g++ -o state textcala.cpp -std=c++11

clean:
	rm -f state *.o

