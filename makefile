MAIN = main
OBJECTS = $(MAIN).o puzzle.o
FLAGS = -Wall -Wextra -std=c++17 -pedantic-errors
DEBUG = -g
CC = g++

all: $(MAIN).exe

$(MAIN).exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(MAIN).exe $(FLAGS)

$(MAIN).o: $(MAIN).cpp puzzle.h 
	$(CC) -c $(MAIN).cpp -o $(MAIN).o $(FLAGS)

puzzle.o: puzzle.cpp puzzle.h
	$(CC) -c puzzle.cpp -o puzzle.o $(FLAGS)

clean:
	del /q $(MAIN).exe $(OBJECTS)