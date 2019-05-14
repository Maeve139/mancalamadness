#Makefile for text mancala

all: mancala


mancala: textcala.cpp
	g++ -o textcala textcala.cpp -std=c++11

clean:
	rm -f textcala *.o

