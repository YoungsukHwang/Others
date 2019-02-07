#include <stdio.h>
#include <stdlib.h>

//#define GL_ENABLE

#define     MIN_X           50
#define     MAX_X           950
#define     MAX_BUILDINGS   100
#define     MAX_SKYLINES    1000

#define		MAX(x,y)		((x)>(y)?(x):(y))

struct Building
{
    float height;
    float left, right;
};

struct Skyline
{
    int     num;
    float   height[MAX_SKYLINES];
    float   x[MAX_SKYLINES+1];
};

int				numBuildings = 5;
struct Building buildings[MAX_BUILDINGS];
struct Skyline  skyline;

#ifdef GL_ENABLE            /* OpenGL drawing routines */

#include <GLUT/glut.h>

GLsizei		winWidth  = 1000,
			winHeight = 500;

#define     GROUND          100

void windowReshape(GLint newWidth, GLint newHeight)
{
	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,newWidth,0.0,newHeight);

	winWidth  = newWidth;
	winHeight = newHeight;
}

void drawBuilding( struct Building *b )
{
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
		glVertex2i( b->left,  GROUND );
		glVertex2i( b->left,  GROUND+b->height );
		glVertex2i( b->right, GROUND+b->height );
		glVertex2i( b->right, GROUND );
	glEnd();
}

void drawSkyline( struct Skyline *s )
{
	glColor3f(1.0, 0.0, 0.0);
   	glLineWidth(3.0);

	glBegin(GL_LINE_STRIP);
    for( int i=0; i<s->num; i++ )
    {
		glVertex2i( s->x[i],   GROUND + s->height[i] );
    	glVertex2i( s->x[i+1], GROUND + s->height[i] );
    }
    glEnd();
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLineWidth(3.0);

	glColor3f(0.7, 0.7, 0.7);
	for( int i=0; i<numBuildings; i++ )
        drawBuilding( &(buildings[i]) );

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINE_STRIP);
        glVertex2i(  50, GROUND );
        glVertex2i( 950, GROUND );
    glEnd();

    drawSkyline( &skyline );
  
	glFlush();
}
#endif              /* The end of OpenGL drawing routines */


void printSkyline( struct Skyline *s )
{
	printf( "[%d] ", s->num );
	
    int i;
    for( i=0; i<s->num; i++ )
        printf( "%3.0f (%3.0f) ", s->x[i], s->height[i] );

    printf( "%3.0f\n", s->x[i] );
}


void MergeSkylines( struct Skyline *s, struct Skyline *s1, struct Skyline *s2 )
{
	/* Write your own code */
	float hcomb[MAX_SKYLINES];
	float xcomb[MAX_SKYLINES+1];
	float h1=0, h2=0;
	int i=1,j=1,k=1;
	xcomb[0] = MIN_X;
	hcomb[0] = 0;
	while(i < s1->num && j < s2->num)
	{
		if(s1->x[i] < s2->x[j])
		{
			xcomb[k] = s1->x[i];
			h1 = s1->height[i];
			hcomb[k]= MAX(h1,h2);
			i++,k++;
		}
		else
		{
			xcomb[k] = s2->x[j];
			h2 = s2->height[j];
			hcomb[k]= MAX(h1,h2);
			j++,k++;
		}
	}
	while(i < s1->num)
	{
		xcomb[k] = s1->x[i];
		hcomb[k] = s1->height[i];
		i++,k++;
	}
	while(j < s2->num)
	{
		xcomb[k] = s2->x[j];
		hcomb[k] = s2->height[j];
		j++,k++;
	}
	xcomb[k] = MAX_X;
	hcomb[k] = 0;

	s->num = k;
	for(i=0; i<MAX_SKYLINES+1; i++)
	{
		s->x[i] = xcomb[i];
		s->height[i] = hcomb[i];
	}
}

void ComputeSkyline( struct Skyline *s, struct Building buildings[], int n )
{
    if ( n==1 )
    {
        s->num = 3;
        s->height[0] = 0;
        s->height[1] = buildings->height;
        s->height[2] = 0;

        s->x[0]      = MIN_X;
        s->x[1]      = buildings->left;
        s->x[2]      = buildings->right;
        s->x[3]      = MAX_X;
    }
    else
    {
        struct Skyline s1;
        struct Skyline s2; 

        int middle = n/2;
 
        ComputeSkyline( &s1, buildings, middle );
        ComputeSkyline( &s2, buildings+middle, n-middle );

        MergeSkylines( s, &s1, &s2 );
    }
}

int main(int argc, char* argv[])
{	
    skyline.num = 0;

	int i;

    for(i=0; i<numBuildings; i++ )
    {
        buildings[i].left   = rand()%700+100;
        buildings[i].right  = rand()%100 + 30  + buildings[i].left;
        buildings[i].height = rand()%300;
    }

    ComputeSkyline( &skyline, buildings, numBuildings );
    printSkyline( &skyline );

#ifdef GL_ENABLE
    glutInit( &argc, argv );

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Skylines");

	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,100.0,0.0,100.0);

	glutDisplayFunc(redraw);
	glutReshapeFunc(windowReshape);	

	glutMainLoop();
#endif

	return 0;
}

