all: wood-snake-cube.cpp 
	g++ -g -Wall -o wood-snake-cube wood-snake-cube.cpp

clean: 
	rm -f wood-snake-cube
