#include <stdio.h>
#include "assn5structs.h"
void helloworld();
void printinstructions();
void keyboard(unsigned char, int, int);
void rotation(int);
void originate(int);
double dotproduct(struct vertice, struct vertice);
struct vertice vectoraddition(struct vertice, struct vertice);
struct vertice vectorsubtraction(struct vertice, struct vertice);
struct vertice vectormultiplication(struct vertice, double);
struct vertice crossproduct(struct vertice, struct vertice);
double collisiondetection(int, double);
double handlecollision(int, struct triangle , double );
void springforce(int i);
void frictionforce(int i);
void helloworld()
{
	printf("hello world\n");
}
void printinstructions()
{
	printf("This program was written by Caleb Thomas\n");
	printf("This is assignment 1 for Physically Based Animation\n");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("To change gravity, press g or h\n");
	printf("To toggle smaller cube, press c\n");
	printf("To toggle solving method, press s\n");
	printf("To change timestep, press m or n\n");
	printf("To change coefficient of stickiness, press i or o\n");
	printf("To change coefficient of restitution, press j or k\n");
	printf("To create more particles, press p\n");
	printf("To toggle wireframe, press l\n");
	printf("To exit program, press the esc key\n");
	printf("To rotate, press the a or d key.\n");
}

void keyboard ( unsigned char key, int x, int y )
{

	switch ( key ) {
		case 27:       
		      	// When Escape Is Pressed...
			exit ( 0 );   // Exit The Program
			break;        
	        case '1':             // stub for new screen, clears it as well 
		        printf("New screen\n");
			break;
		case 'l':
		case 'L':
			//toggle wireframe
			if(NoFace==0)
				NoFace=1;
			else
				NoFace=0;
			break;
		case 'p':
		case 'P':
			//make particles
			makeparticles();
			break;
		case 'r':
		case 'R':
			//reset everything to the beginning
			resetparticles();			
			break;

		case 'n':
			TIMESTEP*=.99;
			printf("The Timestep is now %lf\n", TIMESTEP);
			break;
		case 'N':
			//makes things slower
			TIMESTEP*=1.01;
			printf("The Timestep is now %lf\n", TIMESTEP);
			break;
		case 'g':
			GRAVITY+=.1;
			printf("Gravity is now %lf times normal\n", GRAVITY/-10);
			break;
		case 'G':
			//increases gravity
			GRAVITY-=.1;
			printf("Gravity is now %lf times normal\n", GRAVITY/-10);
			break;
		case 'f':
			frictionconstant-=.1;
			printf("frictionconstant is now %0.1f\n", frictionconstant);
			break;
		case 'F':
			frictionconstant+=.1;
			printf("frictionconstant is now %0.1f\n", frictionconstant);
			break;
		case 's':
			springconstant-=.1;
			printf("spring constant is now %0.1f\n", springconstant);
			break;
		case 'S':
			springconstant+=.1;
			printf("spring constant is now %0.1f\n", springconstant);
			break;
		case 't':
		case 'T':
				//toggles color of particles
				TOGGLE++;
				if(TOGGLE>=3)
					TOGGLE=0;
				break;
		case 'q':
			rotation(0);
			break;
		case 'Q':
			rotation(1);
			break;
		default:       
			break;
	}
}
void springforce(int i)
{
	//springforce
	struct vertice springforce={0, 0, 0};
	struct vertice temp={0, 0, 0};
	double distance;

	//distance is the difference in positions of a and b subtracted from their home distances
	distance=magnitude(vectorsubtraction(PHead[Edge_List[i].a].position, PHead[Edge_List[i].b].position));
	distance=distance-Edge_List[i].homedistance;

	//temp is the vector between a and b (a-b);
	temp=vectorsubtraction(PHead[Edge_List[i].a].position, PHead[Edge_List[i].b].position);

	//springforce=springconstant*temp/|temp|*distance
	springforce=vectormultiplication(temp, distance*springconstant/magnitude(temp));

	//adding springforce to acceleration of each particle
	PHead[Edge_List[i].a].acceleration=vectorsubtraction(PHead[Edge_List[i].a].acceleration, springforce);
	PHead[Edge_List[i].b].acceleration=vectoraddition(PHead[Edge_List[i].b].acceleration, springforce);
}
void frictionforce(int i)
{
	//frictionforce
	struct vertice frictionforce={0, 0, 0};
	struct vertice temp={0, 0, 0};
	double distance;
	
	//temp is the vector between a and b (a-b);
	temp=vectorsubtraction(PHead[Edge_List[i].a].position, PHead[Edge_List[i].b].position);

	//distance is the difference in positions of a and b subtracted from their home distances
	distance=dotproduct(vectormultiplication(temp, 1/magnitude(temp)), vectorsubtraction(PHead[Edge_List[i].a].velocity, PHead[Edge_List[i].b].velocity));

	//finding friction force
	frictionforce=vectormultiplication(temp, distance*frictionconstant/magnitude(temp));

	//adding friction force to acceleration of each particle
	PHead[Edge_List[i].a].acceleration=vectorsubtraction(PHead[Edge_List[i].a].acceleration, frictionforce);
	PHead[Edge_List[i].b].acceleration=vectoraddition(PHead[Edge_List[i].b].acceleration, frictionforce);
}
struct vertice vectoraddition(struct vertice v1, struct vertice v2)
{
	//subtracts one vector for another
	struct vertice answer;
	answer.x=v1.x+v2.x;
	answer.y=v1.y+v2.y;
	answer.z=v1.z+v2.z;
	return answer;
}

double dotproduct(struct vertice v1, struct vertice v2)
{
	//Calculates the dot product.  
	double answer;
	answer=v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
	return answer;
}

struct vertice crossproduct(struct vertice v1, struct vertice v2)
{
	//does the cross product of two vectors
	struct vertice answer;
	answer.x=v1.y*v2.z-v1.z*v2.y;
	answer.y=v1.z*v2.x-v1.x*v2.z;
	answer.z=v1.x*v2.y-v1.y*v2.x;
	return answer;
}
struct vertice vectormultiplication(struct vertice v1, double constant)
{
	//multiplies a vector by a constant
	struct vertice answer;
	answer.x=v1.x*constant;
	answer.y=v1.y*constant;
	answer.z=v1.z*constant;
	return answer;
}

void originate(int direction)
{
	for(int i=0; i<11; i++)
	{
		Vertice_List[i].x=Vertice_List[i].x-250*direction;
		Vertice_List[i].y=Vertice_List[i].y-250*direction;
		Vertice_List[i].z=Vertice_List[i].z-250*direction;
	}
	for(int i=0; i<ListSize; i++)
	{
		PHead[i].position.x-=250*direction;
		PHead[i].position.y-=250*direction;
		PHead[i].position.z-=250*direction;
	}
}
void rotation(int direction)
{
	originate(1);
	if(direction==0)
	{
		for(int i=0; i<11; i++)
		{
			Vertice_List[i].x=Vertice_List[i].x*cos(3/180*PI)+Vertice_List[i].z*sin(3/180*PI);
			Vertice_List[i].z=Vertice_List[i].x*-sin(3/180*PI)+Vertice_List[i].z*cos(3/180*PI);
			
		}
		for(int i=0; i<ListSize; i++)
		{
			PHead[i].position.x=PHead[i].position.x*cos(3/180*PI)+PHead[i].position.z*sin(3/180*PI);
			PHead[i].position.z=PHead[i].position.x*-sin(3/180*PI)+PHead[i].position.z*cos(3/180*PI);
		}
		printf("turning right\n");
	}
	else
	{
		for(int i=0; i<11; i++)
		{
			Vertice_List[i].x=Vertice_List[i].x*cos(-3/180*PI)+Vertice_List[i].z*sin(-3/180*PI);
			Vertice_List[i].z=Vertice_List[i].x*-sin(-3/180*PI)+Vertice_List[i].z*cos(-3/180*PI);
			
		}	
		for(int i=0; i<ListSize; i++)
		{
			PHead[i].position.x=PHead[i].position.x*cos(-3/180*PI)+PHead[i].position.z*sin(-3/180*PI);
			PHead[i].position.z=PHead[i].position.x*-sin(-3/180*PI)+PHead[i].position.z*cos(-3/180*PI);
		}
		printf("turning left\n");
	}
	originate(-1);
}
double findtime(int indice, struct triangle collided, double timestep)
{
	double dt;
	struct vertice position;
	struct vertice velocity;
	position.x=PHead[indice].position.x;
	position.y=PHead[indice].position.y;
	position.z=PHead[indice].position.z;
	velocity.x=PHead[indice].velocity.x;
	velocity.y=PHead[indice].velocity.y;
	velocity.z=PHead[indice].velocity.z;
	dt=dotproduct(*collided.normal, vectorsubtraction(position, collided.p0))/dotproduct(*collided.normal, velocity);
//printf("found a time!!! %lf\n", dt);
	return (timestep+dt);
}
void displayedges()
{
	double inputx[2];
	double inputy[2];
	glBegin(GL_LINES);
		for(int i=0; i<1482; i++)
		{	
			inputx[0]=projection(PHead[Edge_List[i].a].position.x, PHead[Edge_List[i].a].position.z);
			inputx[1]=projection(PHead[Edge_List[i].b].position.x, PHead[Edge_List[i].b].position.z);
			inputy[0]=projection(PHead[Edge_List[i].a].position.y, PHead[Edge_List[i].a].position.z);
			inputy[1]=projection(PHead[Edge_List[i].b].position.y, PHead[Edge_List[i].b].position.z);
			glVertex2f(inputx[0], inputy[0]);//left faces
			glVertex2f(inputx[1], inputy[1]);
		}
	glEnd();
}
double collisiondetection(int indice, double timestep)
{	
	//setting up the correct structs for this function
	double timetemp=-100;
	double ttemp=0;
	int timestop=-1;
	struct vertice temp;
	struct vertice x1;
	struct vertice x2;
	double d1;
	double d2;
	x1.x=PHead[indice].position.x;
	x1.y=PHead[indice].position.y;
	x1.z=PHead[indice].position.z;
	x2.x=PHead[indice].position.x+PHead[indice].velocity.x*timestep;
	x2.y=PHead[indice].position.y+PHead[indice].velocity.y*timestep;
	x2.z=PHead[indice].position.z+PHead[indice].velocity.z*timestep;

	//this is detecting, for each triangle, if it is colliding with the particle.  
	for(int i=0; i<13; i++)
	{
		//printf("Triangle_List x is %lf %lf %lf\n", Triangle_List[i].p0.x, Triangle_List[i].p0.y, Triangle_List[i].p0.z);

		temp.x=x1.x-Triangle_List[i].p0.x;
		temp.y=x1.y-Triangle_List[i].p0.y;
		temp.z=x1.z-Triangle_List[i].p0.z;

		d1=dotproduct(temp, *Triangle_List[i].normal);
		temp.x=x2.x-Triangle_List[i].p0.x;
		temp.y=x2.y-Triangle_List[i].p0.y;
		temp.z=x2.z-Triangle_List[i].p0.z;
		d2=dotproduct(temp, *Triangle_List[i].normal);
		//printf("normals are %lf %lf and %lf\n", Triangle_List[i].normal->x, Triangle_List[i].normal->y, Triangle_List[i].normal->z);
		//this determines if a collision is detected
		if(d2*d1<0)
		{
			struct vertice answer;
			temp.x=(d1*x2.x-d2*x1.x)/(d1-d2);
			temp.y=(d1*x2.y-d2*x1.y)/(d1-d2);
			temp.z=(d1*x2.z-d2*x1.z)/(d1-d2);
			//printf("temps are %lf %lf and %lf \n", temp.x, temp.y, temp.z);
			//confirm collision
			answer.x=dotproduct(vectorsubtraction(temp, Triangle_List[i].p0), crossproduct((vectorsubtraction(Triangle_List[i].p2, Triangle_List[i].p0)), *Triangle_List[i].normal));
			answer.y=dotproduct(vectorsubtraction(temp, Triangle_List[i].p1), crossproduct((vectorsubtraction(Triangle_List[i].p0, Triangle_List[i].p1)), *Triangle_List[i].normal));
			answer.z=dotproduct(vectorsubtraction(temp, Triangle_List[i].p2), crossproduct((vectorsubtraction(Triangle_List[i].p1, Triangle_List[i].p2)), *Triangle_List[i].normal));
			if(answer.x>0 && answer.y>0 && answer.z>0)
			{
				//printf("collision detected!!!!\n");
				//now that the collision is confirmed, it will be handled from here
				ttemp=findtime(indice, Triangle_List[i], timestep);
				if(ttemp>timetemp)
				{
					timetemp=ttemp;
					timestop=i;
				}
			}	
		}
	}
	if(timetemp>-100 && (timetemp/timestep)<.999999)
	{
		timestep=handlecollision(indice, Triangle_List[timestop], timestep);
		//printf("found a time!!! %lf for %i at %i\n", timestep, indice, timestop);
		collisiondetection(indice, timestep);
	}
	return timestep;
}
double handlecollision(int i, struct triangle collided, double timestep)
{
	double dt;
	struct vertice position;
	struct vertice velocity;
	
	position.x=PHead[i].position.x;
	position.y=PHead[i].position.y;
	position.z=PHead[i].position.z;
	velocity.x=PHead[i].velocity.x;
	velocity.y=PHead[i].velocity.y;
	velocity.z=PHead[i].velocity.z;
	dt=dotproduct(*collided.normal, vectorsubtraction(position, collided.p0))/dotproduct(*collided.normal, velocity);
	//found the time when the collision occurred.  
	PHead[i].position.x=PHead[i].position.x-PHead[i].velocity.x*dt*.94;
	PHead[i].position.y=PHead[i].position.y-PHead[i].velocity.y*dt*.94;
	PHead[i].position.z=PHead[i].position.z-PHead[i].velocity.z*dt*.94;
	
	double foundt;
	foundt=timestep+dt;
	//now, find the reflected velocity
	double vnormal;
	struct vertice v11;
	struct vertice vanswer;
	vnormal=dotproduct(velocity, *collided.normal);
	v11=vectorsubtraction(velocity, vectormultiplication(*collided.normal, vnormal));
	vanswer=vectorsubtraction(vectormultiplication(v11, STICKINESS), vectormultiplication(*collided.normal, RESTITUTION*vnormal));
	//we've found the velocity, now assign it to the particle
	PHead[i].velocity.x=vanswer.x;
	PHead[i].velocity.y=vanswer.y;
	PHead[i].velocity.z=vanswer.z;
	return foundt;
}	
