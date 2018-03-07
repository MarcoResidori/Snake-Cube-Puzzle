# Snake-Cube-Puzzle

Simple program that calculates the steps to turn this snake:

![snake](images/snake.png) 

into this cube:

![cube](images/cube.png) 

## How to build and run the program

```
make
./snake-cube-puzzle
```

The solution is calculated using the following coordinate system:

![coordinate-system](images/coordinate-system.png)

## Solution 1 of 6 

```
Step  0 -> [AXIS_X,DIR_POS,LENGTH_3]
Step  1 -> [AXIS_Y,DIR_POS,LENGTH_2]
Step  2 -> [AXIS_X,DIR_NEG,LENGTH_2]
Step  3 -> [AXIS_Z,DIR_POS,LENGTH_3]
Step  4 -> [AXIS_Y,DIR_POS,LENGTH_2]
Step  5 -> [AXIS_Z,DIR_NEG,LENGTH_3]
Step  6 -> [AXIS_X,DIR_POS,LENGTH_2]
Step  7 -> [AXIS_Z,DIR_POS,LENGTH_2]
Step  8 -> [AXIS_Y,DIR_NEG,LENGTH_3]
Step  9 -> [AXIS_X,DIR_NEG,LENGTH_3]
Step 10 -> [AXIS_Y,DIR_POS,LENGTH_2]
Step 11 -> [AXIS_Z,DIR_NEG,LENGTH_2]
Step 12 -> [AXIS_Y,DIR_POS,LENGTH_2]
Step 13 -> [AXIS_Z,DIR_POS,LENGTH_3]
Step 14 -> [AXIS_Y,DIR_NEG,LENGTH_3]
Step 15 -> [AXIS_X,DIR_POS,LENGTH_3]
Step 16 -> [AXIS_Y,DIR_POS,LENGTH_3]
```
