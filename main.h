#include <windows.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include <stdlib.h>
#include <float.h>

#define POSITIVE 1
#define ZERO 0
#define NEGATIVE -1
#define ASTEROID_SHAPE_NUMBER 10
#define GARBAGE_OBJECT 0
#define SHIP 1
#define BULLET 2
#define ASTEROID 3

//C++
#include <vector>


void keyPressed(unsigned char key, int x, int y);
void keyUp (unsigned char key, int x, int y);
void DrawCircle(float cx, float cy, float r, int num_segments);
void fireTurret(float x,float y);
void DrawAsteroid();
void DrawShip();
void addBullet();
void addAsteroid(float x, float y);
void removeObject();
void setShapes();
int randNumber(int number);
int detectCollision(int i);

typedef struct {
   int vertexNumber;
   float vertex[10][2];
} objectShape;

void drawShape(objectShape shape,GLenum type);




