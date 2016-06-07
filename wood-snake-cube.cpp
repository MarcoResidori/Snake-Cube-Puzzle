/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Filename: wood-snake-cube.cpp

    Description:
    This programs calculates the sequence of steps to solve a 3x3x3 wood snake cube

    Author: Marco Residori (residori@gmx.net)
*/


#include <stdio.h>
#include <memory.h>
#define NUM_SEGMENTS 17

static int numSolutions = 0;
enum eAxis
{
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2,
    AXIS_INVALID = 3,
};

enum eDirection
{
    DIR_POS = 0,
    DIR_NEG = 1,
    DIR_INVALID = 3,
};

struct tRotation
{
    eAxis axis;
    eDirection direction;
};

struct tPoint
{
    int x;
    int y;
    int z;
};

class cMatrix;
class cSequence;

bool calculate(tPoint point1, int index, cSequence sequence, cMatrix matrix);

class cMatrix
{
    public:
        cMatrix();
        ~cMatrix();
        void init();
        cMatrix & operator = (cMatrix & rhs);
        bool isOccupied(tPoint p);
        bool isOccupied(tPoint p1, tPoint p2);
        bool isInside(tPoint p);
        void setOccupied(tPoint p1, tPoint p2);
        void print();

    private:
        bool mCube[3][3][3];
};

cMatrix::cMatrix()
{
   init();
}

void cMatrix::init()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                mCube[i][j][k] = 0;
            }
        }
    }
}

cMatrix & cMatrix::operator = (cMatrix & rhs)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                rhs.mCube[i][j][k] = mCube[i][j][k];
            }
        }
    }
    return rhs;
}

void cMatrix::print()
{
    printf("Matrix\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                printf("[%d][%d][%d] = %d\n",i,j,k,mCube[i][j][k]);
            }
        }
    }
}

cMatrix::~cMatrix()
{
}

bool cMatrix::isOccupied(tPoint p)
{
    return mCube[p.x][p.y][p.z];
}

bool cMatrix::isOccupied(tPoint p1, tPoint p2)
{
    int start = 0;
    int end = 0;
    int i = 0;

    if(p1.x != p2.x)
    {
        if(p1.x > p2.x)
        {
            start = p2.x;
            end = p1.x - 1;
        }
        else
        {
            start = p1.x + 1;
            end = p2.x;
        }
        for(i = start; i <= end; i++)
        {
            if(mCube[i][p2.y][p2.z] == 1) return true;
        }
    }
    else if(p1.y != p2.y)
    {
        if(p1.y > p2.y)
        {
            start = p2.y;
            end = p1.y - 1;
        }
        else
        {
            start = p1.y + 1;
            end = p2.y;
        }
        for (i = start; i <= end; i++)
        {
            if(mCube[p2.x][i][p2.z] == 1) return true;
        }
    }
    else if(p1.z != p2.z)
    {
        if(p1.z > p2.z)
        {
            start = p2.z;
            end = p1.z - 1;
        }
        else
        {
            start = p1.z + 1;
            end = p2.z;
        }
        for (i = start; i <= end; i++)
        {
            if(mCube[p2.x][p2.y][i] == 1) return true;
        }
    }
    return false;
}

bool cMatrix::isInside(tPoint p)
{
    return (p.x < 3 && p.y < 3 && p.z < 3) && (p.x >= 0 && p.y >= 0 && p.z >= 0);
}

void cMatrix::setOccupied(tPoint p1, tPoint p2)
{
    int start = 0;
    int end = 0;
    int i = 0;

    if(p1.x != p2.x)
    {
        if(p1.x > p2.x)
        {
            start = p2.x;
            end = p1.x;
        }
        else
        {
            start = p1.x;
            end = p2.x;
        }
        for (i = start; i <= end; i++)
        {
            mCube[i][p2.y][p2.z] = 1;
        }
    }
    else if(p1.y != p2.y)
    {
        if(p1.y > p2.y)
        {
            start = p2.y;
            end = p1.y;
        }
        else
        {
            start = p1.y;
            end = p2.y;
        }
        for (i = start; i <= end; i++)
        {
            mCube[p2.x][i][p2.z] = 1;
        }
    }
    else if(p1.z != p2.z)
    {
        if(p1.z > p2.z)
        {
            start = p2.z;
            end = p1.z;
        }
        else
        {
            start = p1.z;
            end = p2.z;
        }
        for(i = start; i <= end; i++)
        {
            mCube[p2.x][p2.y][i] = 1;
        }
    }
}

class cSequence
{
    public:
        cSequence();
        ~cSequence();
        cSequence & operator = (cSequence & rhs);
        bool isSequenceComplete();
        void init();
        void print();
        bool add(tRotation rotation,int index);

    private:
        tRotation mSequence[NUM_SEGMENTS];
};

cSequence::cSequence()
{
    init();
};

cSequence & cSequence::operator = (cSequence & rhs)
{
    for(int i = 0; i < NUM_SEGMENTS; i++)
    {
        rhs.mSequence[i] = mSequence[i];
    }
    return rhs;
}

void cSequence::init()
{
    for(int i = 0; i< NUM_SEGMENTS; i++)
    {
        mSequence[i].axis = AXIS_INVALID;
        mSequence[i].direction = DIR_INVALID;
    }
};

cSequence::~cSequence()
{
};

void cSequence::print()
{
    printf("\nSequence: \n");
    for(int i = 0; i < NUM_SEGMENTS; i++)
    {
        printf("Step %2d -> [",i);
        printf("rot ");
        switch(mSequence[i].axis)
        {
            case AXIS_X:
               printf("AXIS_X");
               break;
            case AXIS_Y:
               printf("AXIS_Y");
               break;
            case AXIS_Z:
               printf("AXIS_Z");
               break;
            default:
               printf("AXIS_INVALID");
               break;
        }
        printf(", dir ");

        switch(mSequence[i].direction)
        {
            case DIR_POS:
               printf("DIR_POS");
               break;
            case DIR_NEG:
               printf("DIR_NEG");
               break;
            default:
               printf("DIR_INVALID");
               break;
        }
        printf("]\n");
    }
};

void printRotation(tRotation rotation)
{
    printf("rot ");
    switch(rotation.axis)
    {
        case AXIS_X:
            printf("AXIS_X,");
            break;
        case AXIS_Y:
            printf("AXIS_Y,");
            break;
        case AXIS_Z:
            printf("AXIS_Z,");
            break;
        default:
            printf("AXIS_INVALID,");
            break;
    }
    printf("dir ");
    switch(rotation.direction)
    {
        case DIR_POS:
            printf("DIR_POS");
            break;
        case DIR_NEG:
            printf("DIR_NEG");
            break;
        default:
            printf("DIR_INVALID");
            break;
    }
    printf(")\n");
};

bool cSequence::add(tRotation rotation,int index)
{
    mSequence[index].axis = rotation.axis;
    mSequence[index].direction = rotation.direction;
    return true;
};

static int theSegments[NUM_SEGMENTS] = {3,2,2,3,2,3,2,2,3,3,2,2,2,3,3,3,3};
cSequence theSequence;
cMatrix theMatrix;


bool calculateEndPoint(tPoint point1, int segment, tRotation rotation, tPoint& point2)
{
    switch(rotation.axis)
    {
    case AXIS_X:
       point2.x = rotation.direction == DIR_POS ? point1.x + segment - 1: point1.x - segment + 1;
       point2.y = point1.y;
       point2.z = point1.z;
       break;
    case AXIS_Y:
       point2.y = rotation.direction == DIR_POS ? point1.y + segment - 1: point1.y - segment + 1;
       point2.x = point1.x;
       point2.z = point1.z;
       break;
    case AXIS_Z:
       point2.z = rotation.direction == DIR_POS ? point1.z + segment - 1: point1.z - segment + 1;
       point2.x = point1.x;
       point2.y = point1.y;
       break;
    default:
       break;
    }
    return true;
}

bool step(tPoint point1, tRotation rotation, int index, cSequence sequence, cMatrix matrix)
{
    tPoint point2 = {0,0,0};

    if(index >= NUM_SEGMENTS)
    {
       printf("Error\n");
       return false;
    }

    if(calculateEndPoint(point1,theSegments[index],rotation,point2))
    {
       if(matrix.isInside(point2))
       {
          if(matrix.isOccupied(point1,point2) == false)
          {             
             matrix.setOccupied(point1,point2);
             //printf("Adding index %d,", index); printRotation(rotation);
             sequence.add(rotation,index);
             calculate(point2,++index,sequence,matrix);
          }
          else
          {
              //printf("Path {%d,%d,%d}->{%d,%d,%d} is occupied\n",point1.x,point1.y,point1.z,point2.x,point2.y,point2.z);
          }
       }
       else
       {
           //printf("Point {%d,%d,%d} is outside\n",point2.x,point2.y,point2.z);
       }
    }

    return true;
}

bool calculate(tPoint point1, int index, cSequence sequence, cMatrix matrix)
{
    tRotation rotation;

    if(index >= NUM_SEGMENTS)
    {
        sequence.print();
        //matrix.print();
        numSolutions++;
        return true;
    }

    rotation.axis = AXIS_X;
    rotation.direction = DIR_POS;
    //printf("[Index %d] Trying ",index); printRotation(rotation);
    step(point1,rotation,index,sequence,matrix);

    rotation.axis = AXIS_X;
    rotation.direction = DIR_NEG;
    //printf("[Index %d] Trying ",index); printRotation(rotation);
    step(point1,rotation,index,sequence,matrix);

    rotation.axis = AXIS_Y;
    rotation.direction = DIR_POS;
    //printf("[Index %d] Trying ",index); printRotation(rotation); 
    step(point1,rotation,index,sequence,matrix);

    rotation.axis = AXIS_Y;
    rotation.direction = DIR_NEG;
    //printf("[Index %d] Trying ",index); printRotation(rotation);
    step(point1,rotation,index,sequence,matrix);

    rotation.axis = AXIS_Z;
    rotation.direction = DIR_POS;
    //printf("[Index %d] Trying ",index); printRotation(rotation);
    step(point1,rotation,index,sequence,matrix);

    rotation.axis = AXIS_Z;
    rotation.direction = DIR_NEG;
    //printf("[Index %d] Trying ",index); printRotation(rotation);
    step(point1,rotation,index,sequence,matrix);

    //printf("No solution found\n");

    return true;
}

int main(int argc, char* argv[])
{
    tPoint point;

    printf("Start!\n");

    //possible cases
    printf("--------------------------------------------------\n");
    printf("Case 1\n"); //corner
    printf("--------------------------------------------------\n");
    theMatrix.init();
    theSequence.init();
    point.x = 0;
    point.y = 0;
    point.z = 0;
    printf("Starting point {%d,%d,%d}\n",point.x,point.y,point.z);
    calculate(point,0,theSequence,theMatrix);
    
    printf("--------------------------------------------------\n");
    printf("Case 2\n"); //middle side
    printf("--------------------------------------------------\n");
    theMatrix.init();
    theSequence.init();
    point.x = 1;
    point.y = 0;
    point.z = 0;
    printf("Starting point {%d,%d,%d}\n",point.x,point.y,point.z);
    calculate(point,0,theSequence,theMatrix);

    printf("--------------------------------------------------\n");
    printf("Case 3\n"); //middle base
    printf("--------------------------------------------------\n");
    theMatrix.init();
    theSequence.init();
    point.x = 1;
    point.y = 1;
    point.z = 0;
    printf("Starting point {%d,%d,%d}\n",point.x,point.y,point.z);
    calculate(point,0,theSequence,theMatrix);

    printf("--------------------------------------------------\n");
    printf("Case 4\n"); //middle cube
    printf("--------------------------------------------------\n");
    theMatrix.init();
    theSequence.init();
    point.x = 1;
    point.y = 1;
    point.z = 1;
    printf("Starting point {%d,%d,%d}\n",point.x,point.y,point.z);
    calculate(point,0,theSequence,theMatrix);

    printf("\nNumber of solutions: %d\n", numSolutions);

    printf("\nEnd!\n");

    return 0;
}

