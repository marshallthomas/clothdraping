#include "assn5globals.h"
void calculatenormal(struct triangle);
void makeparticles();
void resetparticles();
void initializevertices();
void maketriangles(struct vertice);
void makevertices(struct vertice);
void settozero(int);
double projection(double, double);
void leaderaccelerationchange();
void debuglist();
double magnitude(struct vertice);
struct vertice vectorsubtraction(struct vertice, struct vertice);
double projection(double x, double z)
{
	//This projects either the x or y value onto the viewing plane based on the z value of each point.  
	x=(x-250)*400/(z+400)+250;
	return x;
}
void calculatenormal(struct triangle example)
{
	//This calculates the normal of the triangles for this program.  
	struct vertice edge1;
	struct vertice edge2;
	//find U
	edge1.x=example.p1.x-example.p0.x;
	edge1.y=example.p1.y-example.p0.y;
	edge1.z=example.p1.z-example.p0.z;
	//find V
	edge2.x=example.p2.x-example.p0.x;
	edge2.y=example.p2.y-example.p0.y;
	edge2.z=example.p2.z-example.p0.z;
	//find normal of two edges
	example.normal->x=edge1.y*edge2.z-edge1.z*edge2.y;
	example.normal->y=edge1.z*edge2.x-edge1.x*edge2.z;
	example.normal->z=edge1.x*edge2.y-edge1.y*edge2.x;
	double magnitude=sqrt(example.normal->x*example.normal->x+example.normal->y*example.normal->y+example.normal->z*example.normal->z);
	example.normal->x=example.normal->x/magnitude;
	example.normal->y=example.normal->y/magnitude;
	example.normal->z=example.normal->z/magnitude;
	//makes normal unit vector
}
void resetparticles()
{
	//when the r button is pressed, the particles all reset and go back to the middle.  
	//also, some of the global variables are reset.  
	RESTITUTION=1;
	STICKINESS=1;
	GRAVITY=-10;
	TIMESTEP=.005;
	for(int i=0; i<ListSize/20; i++)
	{
		for(int j=0; j<ListSize/20; j++)
		{
			PHead[i*20+j].position.x=170+i*8+.05;
			PHead[i*20+j].position.y=400;
			PHead[i*20+j].position.z=70+j*8+.075;
			PHead[i*20+j].velocity.y=0;
			PHead[i*20+j].velocity.x=0;
			PHead[i*20+j].velocity.z=0;
			settozero(i*20+j);
		}
	}
}
void makeedges()
{
	//horizontal edges
	for(int i=0; i<19; i++)
	{
		for(int j=0; j<20; j++)
		{
			Edge_List[i*20+j].a=i*20+j;
			Edge_List[i*20+j].b=(i+1)*20+j;
		}
	}
	int sum=19*20;
	//verticle edges;		
	for(int i=0; i<20; i++)
	{
		for(int j=0; j<19; j++)
		{
			Edge_List[sum+i*19+j].a=i*20+j;
			Edge_List[sum+i*19+j].b=i*20+j+1;
		}
	}
	sum=sum+19*20;
	//diagonal edges;
	for(int i=0; i<19; i++)
	{
		for(int j=0; j<19; j++)
		{
			Edge_List[sum+i*19+j].a=i*20+j;
			Edge_List[sum+i*19+j].b=i*20+20+j+1;
		}
	}
	//the other diagonal edges
	sum=sum+19*19;
	for(int i=0; i<19; i++)
	{
		for(int j=0;j<19; j++)
		{
			Edge_List[sum+i*19+j].a=i*20+j+1;
			Edge_List[sum+i*19+j].b=i*20+20+j;
		}
	}
	//finding home distances for each edge
	sum=sum+19*19;
	for(int i=0; i<sum; i++)
	{
		Edge_List[i].homedistance=magnitude(vectorsubtraction(PHead[Edge_List[i].a].position, PHead[Edge_List[i].b].position));
	}
}
double magnitude(struct vertice example)
{
	double answer=example.x*example.x+example.y*example.y+example.z*example.z;
	answer=sqrt(answer);
	return answer;
}
void makeparticles()
{
	for(int i=0; i<ListSize/20; i++)
	{
		for(int j=0; j<ListSize/20; j++)
		{
			PHead[i*20+j].position.x=170+i*8+.05;
			PHead[i*20+j].position.y=400;
			PHead[i*20+j].position.z=70+j*8+.075;
			PHead[i*20+j].velocity.y=0;
			PHead[i*20+j].velocity.x=0;
			PHead[i*20+j].velocity.z=0;
			settozero(i*20+j);
		}
	}

}
struct vertice vectorsubtraction(struct vertice v1, struct vertice v2)
{
	//subtracts one vector for another
	struct vertice answer;
	answer.x=v1.x-v2.x;
	answer.y=v1.y-v2.y;
	answer.z=v1.z-v2.z;
	return answer;
}
void intializevertices()
{
	//This function is hardcoding the locations of the vertices for the big and small cube, as well as setting
	//up the code to hold the triangles.......  
	//Had I been able to find a .obj file for the cubes, I wouldn't have done this.  
	Vertice_List[0].x=200;
	Vertice_List[0].y=100;
	Vertice_List[0].z=100;

	Vertice_List[1].x=200;
	Vertice_List[1].y=100;
	Vertice_List[1].z=200;

	Vertice_List[2].x=300;
	Vertice_List[2].y=100;
	Vertice_List[2].z=200;
	
	Vertice_List[3].x=300;
	Vertice_List[3].y=100;
	Vertice_List[3].z=100;
	
	Vertice_List[4].x=200;
	Vertice_List[4].y=200;
	Vertice_List[4].z=100;

	Vertice_List[5].x=200;
	Vertice_List[5].y=200;
	Vertice_List[5].z=200;

	Vertice_List[6].x=300;
	Vertice_List[6].y=200;
	Vertice_List[6].z=200;

	Vertice_List[7].x=300;
	Vertice_List[7].y=200;
	Vertice_List[7].z=100;

	Vertice_List[8].x=250;
	Vertice_List[8].z=500;
	Vertice_List[8].y=100;
	
	Vertice_List[9].x=0;
	Vertice_List[9].z=0;
	Vertice_List[9].y=100;
	
	Vertice_List[10].x=500;
	Vertice_List[10].z=0;
	Vertice_List[10].y=100;

	Triangle_List[0].p0=Vertice_List[0];
	Triangle_List[0].p1=Vertice_List[1];
	Triangle_List[0].p2=Vertice_List[5];
	Triangle_List[0].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[0]);

	Triangle_List[1].p0=Vertice_List[5];
	Triangle_List[1].p1=Vertice_List[4];
	Triangle_List[1].p2=Vertice_List[0];
	Triangle_List[1].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[1]);

	Triangle_List[2].p0=Vertice_List[1];
	Triangle_List[2].p1=Vertice_List[2];
	Triangle_List[2].p2=Vertice_List[6];
	Triangle_List[2].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[2]);

	Triangle_List[3].p0=Vertice_List[6];
	Triangle_List[3].p1=Vertice_List[5];
	Triangle_List[3].p2=Vertice_List[1];
	Triangle_List[3].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[3]);

	Triangle_List[4].p0=Vertice_List[2];
	Triangle_List[4].p1=Vertice_List[3];
	Triangle_List[4].p2=Vertice_List[7];
	Triangle_List[4].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[4]);

	Triangle_List[5].p0=Vertice_List[7];
	Triangle_List[5].p1=Vertice_List[6];
	Triangle_List[5].p2=Vertice_List[2];
	Triangle_List[5].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[5]);

	Triangle_List[6].p0=Vertice_List[6];
	Triangle_List[6].p1=Vertice_List[4];
	Triangle_List[6].p2=Vertice_List[5];
	Triangle_List[6].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[6]);

	Triangle_List[7].p0=Vertice_List[6];
	Triangle_List[7].p1=Vertice_List[7];
	Triangle_List[7].p2=Vertice_List[4];
	Triangle_List[7].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[7]);

	Triangle_List[8].p0=Vertice_List[0];
	Triangle_List[8].p1=Vertice_List[2];
	Triangle_List[8].p2=Vertice_List[1];
	Triangle_List[8].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[8]);

	Triangle_List[9].p0=Vertice_List[0];
	Triangle_List[9].p1=Vertice_List[3];
	Triangle_List[9].p2=Vertice_List[2];
	Triangle_List[9].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[9]);

	Triangle_List[10].p0=Vertice_List[0];
	Triangle_List[10].p1=Vertice_List[4];
	Triangle_List[10].p2=Vertice_List[7];
	Triangle_List[10].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[10]);

	Triangle_List[11].p0=Vertice_List[7];
	Triangle_List[11].p1=Vertice_List[3];
	Triangle_List[11].p2=Vertice_List[0];
	Triangle_List[11].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[11]);

	Triangle_List[12].p0=Vertice_List[8];
	Triangle_List[12].p1=Vertice_List[9];
	Triangle_List[12].p2=Vertice_List[10];
	Triangle_List[12].normal=(vertice *)malloc(sizeof(vertice));
	calculatenormal(Triangle_List[12]);


}
void maketriangles(struct vertice Vertices[8])
{
	double inputx[8]; //creating a matrix to do the calculations up front and not do them four times per frame for every line
	double inputy[8];
	for(int i=0; i<8; i++)
	{
		inputx[i]=projection(Vertices[i].x, Vertices[i].z);
		inputy[i]=projection(Vertices[i].y, Vertices[i].z);
	}
	glColor3f(0, 0, 1);
	glVertex2f(inputx[0], inputy[0]);//left faces
	glVertex2f(inputx[1], inputy[1]);
	glVertex2f(inputx[5], inputy[5]);
	
	glColor3f(0, 1, 0);
	glVertex2f(inputx[5], inputy[5]);
	glVertex2f(inputx[4], inputy[4]);
	glVertex2f(inputx[0], inputy[0]);

	glColor3f(0, .3, .3);
	glVertex2f(inputx[1], inputy[1]);//back faces
	glVertex2f(inputx[2], inputy[2]);
	glVertex2f(inputx[6], inputy[6]);

	glColor3f(1, 0, 0);
	glVertex2f(inputx[6], inputy[6]);
	glVertex2f(inputx[5], inputy[5]);
	glVertex2f(inputx[1], inputy[1]);

	glColor3f(1, 0, 1);
	glVertex2f(inputx[2], inputy[2]);//right faces
	glVertex2f(inputx[3], inputy[3]);
	glVertex2f(inputx[7], inputy[7]);

	glColor3f(1, 1, 0);
	glVertex2f(inputx[7], inputy[7]);
	glVertex2f(inputx[6], inputy[6]);
	glVertex2f(inputx[2], inputy[2]);

	glColor3f(1, 1, 1);
	glVertex2f(inputx[6], inputy[6]);//top faces
	glVertex2f(inputx[4], inputy[4]);
	glVertex2f(inputx[5], inputy[5]);

	glColor3f(.5, .5, .5);
	glVertex2f(inputx[6], inputy[6]);
	glVertex2f(inputx[7], inputy[7]);
	glVertex2f(inputx[4], inputy[4]);

	glColor3f(.5, .5,.5);
	glVertex2f(inputx[0], inputy[0]);//bottom faces
	glVertex2f(inputx[1], inputy[1]);
	glVertex2f(inputx[2], inputy[2]);

	glColor3f(.5, 0, .5);
	glVertex2f(inputx[0], inputy[0]);
	glVertex2f(inputx[3], inputy[3]);
	glVertex2f(inputx[2], inputy[2]);


}
//***************************************************************************/
void makevertices(struct vertice Vertices[8])
{
		double inputx[8]; //creating a matrix to do the calculations up front and not do them four times per frame for every line
		double inputy[8];
		for(int i=0; i<8; i++)
		{
			inputx[i]=projection(Vertices[i].x, Vertices[i].z);
			inputy[i]=projection(Vertices[i].y, Vertices[i].z);
		}
		
		glVertex2f(inputx[0], inputy[0]); //First face, left face
		glVertex2f(inputx[1], inputy[1]);
		glVertex2f(inputx[5], inputy[5]);
		glVertex2f(inputx[4], inputy[4]);
		glVertex2f(inputx[0], inputy[0]);
		glVertex2f(inputx[5], inputy[5]);
	
		glVertex2f(inputx[1], inputy[1]);//Second face, back face
		glVertex2f(inputx[2], inputy[2]);
		glVertex2f(inputx[6], inputy[6]);
		glVertex2f(inputx[5], inputy[5]);
		glVertex2f(inputx[1], inputy[1]);
		glVertex2f(inputx[6], inputy[6]);
	
		glVertex2f(inputx[4], inputy[4]);//third face, top face
		glVertex2f(inputx[7], inputy[7]);
		glVertex2f(inputx[6], inputy[6]);

		glVertex2f(inputx[2], inputy[2]);//fourth face, right face
		glVertex2f(inputx[3], inputy[3]);
		glVertex2f(inputx[7], inputy[7]);
		glVertex2f(inputx[6], inputy[6]);
		glVertex2f(inputx[2], inputy[2]);
		glVertex2f(inputx[7], inputy[7]);
		
		glVertex2f(inputx[3], inputy[3]);//fifth face, bottom face
		glVertex2f(inputx[0], inputy[0]);
		glVertex2f(inputx[2], inputy[2]);
	
}
void settozero(int i)
{

	PHead[i].acceleration.x=0;
	PHead[i].acceleration.y=0;
	PHead[i].acceleration.z=0;
}
