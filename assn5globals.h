typedef struct color
{
	double r;
	double g;
	double b;
}color;


        /* Include needed files */
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGHT 500
#define PI 3.14159265
#define ACCELERATIONTIMESTEP 10
int TIMER=0;
//list of global variables that hold all the necessary info.  

//this is really just a point
typedef struct vertice{
	double x;
	double y;
	double z;
}vertice;


//contains all the info for each triangle
typedef struct triangle{
	struct vertice p0;
	struct vertice p1;
	struct vertice p2;
	struct vertice *normal;
}triangle;


//contains necessary movement data for each particle, is a linked list to accommodate a lot of particles
typedef struct particle{
	struct vertice position;
	struct vertice velocity;
	struct vertice acceleration;
}particle;
typedef struct edge{
	int a;
	int b;
	double homedistance;
}edge;
struct edge Edge_List[1482];
//array that holds all the info for each triangle
struct triangle Triangle_List[13];
//list of all the vertices for the big cube
struct vertice Vertice_List[11];
//list of all the vertices for the little cube
#define ListSize 400
struct particle PHead[ListSize];
int SOLVERTYPE=0;
int CONSTRAINTS=1;
double springconstant=8;
double frictionconstant=8;
//timestep
double TIMESTEP=.005;
//gravity
double GRAVITY=-10;
//coefficient of stickiness
double STICKINESS=1;
//coefficient of restitution
double RESTITUTION=1;
//toggle change in colors
double TOGGLE=0;
//Is this going around a sphere?
double SPHERE=0;
//is this wireframe?
int NoFace=1;
int particlecount=1;
