//
//		          Programming Assignment #1 
//
//			        Caleb Thomas
//				For J Tessendorf
//		
//
/***************************************************************************/

//It's worth noting that I'm defining the origin as the middle of the display (250, 250).  

#include "assn5lib.h"
void init_window();
void display();
void drawparticles(struct particle *);
int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key*/
	makeparticles();
	makeedges();
	intializevertices();
	printinstructions();
	glutInit            ( &argc, argv ); 
       	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowSize  ( 700,700 ); 
	glutCreateWindow    ( "PBA Assignment 1" ); 
	glutDisplayFunc     ( display );  
	glutIdleFunc	    ( display );
	glutKeyboardFunc    ( keyboard );
        					      
        init_window();				             		       		
	glutMainLoop        ( );                 
}

void init_window()
                 /* Clear the image area, and set up the coordinate system */
{
        					       /* Clear the window */
        glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
        glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/
void display ()  
{

  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      //Clear Screen

	//Is this a wireframe or not?
	if(NoFace==1)
	{
		glBegin(GL_TRIANGLES);
			maketriangles(Vertice_List);
		glEnd();
	}
	glBegin(GL_LINE_STRIP);
		//drawing the wireframe
		if(NoFace==1)
		{
			glColor3f(.3,.3,.3);
		}
		else
		{
			glColor3f(1, 1, 1);
		}
		makevertices(Vertice_List);
		

	glEnd();	
	double inputx[3];
	double inputy[3];
	inputx[0]=projection(Vertice_List[8].x, Vertice_List[8].z);
	inputx[1]=projection(Vertice_List[9].x, Vertice_List[9].z);
	inputx[2]=projection(Vertice_List[10].x, Vertice_List[10].z);
	inputy[0]=projection(Vertice_List[8].y, Vertice_List[8].z);
	inputy[1]=projection(Vertice_List[9].y, Vertice_List[9].z);
	inputy[2]=projection(Vertice_List[10].y, Vertice_List[10].z);
	glBegin(GL_LINE_STRIP);
		glVertex2f(inputx[0], inputy[0]);
		glVertex2f(inputx[1], inputy[1]);
		glVertex2f(inputx[2], inputy[2]);
		glVertex2f(inputx[0], inputy[0]);
	glEnd();
	//drawing particles
	drawparticles(PHead);
	displayedges();
  	glutSwapBuffers();                                      // Draw Frame Buffer 
}











void velocitysolver(double time)
{
	//this calculates the soft forces per each edge, then applies said forces directly to each particle's 
	//acceleration value
	for(int i=0; i<1482; i++)
	{
		springforce(i);
		frictionforce(i);
	}
	for(int i=0; i<ListSize; i++)
	{
		//This is Forward Euler Calculation
		PHead[i].velocity.x=PHead[i].velocity.x+PHead[i].acceleration.x*time;
		PHead[i].velocity.y=PHead[i].velocity.y+PHead[i].acceleration.y*time+GRAVITY*time;
		PHead[i].velocity.z=PHead[i].velocity.z+PHead[i].acceleration.z*time;
		//set acceleration back to zero for next cycle
		settozero(i);
	}
}
void positionsolver(double time)
{
	for(int i=0; i<ListSize; i++)
	{
		collisiondetection(i, time);
		PHead[i].position.x=PHead[i].position.x+PHead[i].velocity.x*time;
		PHead[i].position.y=PHead[i].position.y+PHead[i].velocity.y*time;
		PHead[i].position.z=PHead[i].position.z+PHead[i].velocity.z*time;
	}
}
void drawparticles(struct particle *head)
{
	velocitysolver(TIMESTEP);
	positionsolver(TIMESTEP);

	glBegin(GL_POINTS);
	for(int k=0; k<ListSize; k++)
	{
		double red;
		double green;
		double blue;
		if(TOGGLE==0)
		{
			red=1.0;
			green=1.0;
			blue=1.0;
		}
		else if(TOGGLE==1 || k==0)
		{
			red=0;
			green=0;
			blue=0;
		}
		else if(TOGGLE==2)
		{
			red=1.0/(rand()%20);
			green=1.0/(rand()%20);
			blue=1.0/(rand()%20);
		}
		glColor3f(red, green, blue);
		for(double i=-1; i<2; i++)
		{
			for(double j=-1; j<2; j++)
			{
				glVertex2f(projection(PHead[k].position.x, PHead[k].position.z)+i/2, projection(PHead[k].position.y, PHead[k].position.z)+j/2);
				
			}
		}
	}
	glEnd();
}





/***************************************************************************/

/***************************************************************************/




