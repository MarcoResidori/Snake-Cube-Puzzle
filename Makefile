all: snake-cube-puzzle.cpp 
	g++ -g -Wall -o snake-cube-puzzle snake-cube-puzzle.cpp

clean: 
	rm -f snake-cube-puzzle
