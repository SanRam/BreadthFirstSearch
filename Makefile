# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall

all: BFS BFS.exe

BFS.exe : BFS.o
	$(CC) BFS.o -o BFS.exe
	
BFS: BFS.o
	$(CC) BFS.o -o BFS

BFS.o: BFS.cpp
	$(CC) $(CFLAGS) BFS.cpp

clean:
	rm -rf *o BFS.exe
	rm -rf *o BFS
