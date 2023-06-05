#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>




int  r;




int  Round(int a);
void DDALINE(int xa, int ya, int xb, int yb);
void BRESENHAMCIRCLE(int xc, int yc, int r);
void mouse(int button, int state, int x, int y);
void Draw();




int main(int argc,char ** argv)
{
    printf("Enter Radius of Circle ");
    scanf("%d",&r);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("BRESENHAM CIRCLE");
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();


    return 0;
}


void BRESENHAMCIRCLE(int xc, int yc, int r)
{
    int x,y,d;
    x=0;
    y=r;
    d=3-2*r;
    do
    {
        glVertex2d( y+xc, x+yc);
		glVertex2d( x+xc, y+yc);
		glVertex2d( x+xc,-y+yc);
glVertex2d( y+xc,-x+yc);
		glVertex2d(-y+xc,-x+yc);
		glVertex2d(-x+xc,-y+yc);
		glVertex2d(-x+xc, y+yc);
		glVertex2d(-y+xc, x+yc);
        if(d<0)
		{
			x=x+1;
			d=d+4*x+6;
		}
		else
		{
			x=x+1;
			y=y-1;
			d=d+4*x-4*y+10;
		}
    } while (y>=x);
    
}


void mouse(int button, int state, int x, int y)
{
	y = 480-y;
    glBegin(GL_POINTS);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
   	    int xc=x;
    	int yc=y;
    	glColor3f(1.0,0.0,0.0);
        BRESENHAMCIRCLE(    xc,     yc,r); 
        BRESENHAMCIRCLE(    xc, 480-yc,r);
        BRESENHAMCIRCLE(640-xc,     yc,r);
        BRESENHAMCIRCLE(640-xc, 480-yc,r); 
        glEnd();
        glFlush();
	}
}


void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);


    DDALINE(0,240,640,240);
    DDALINE(320,0,320,640);
    int i=0;
    while(i<640)
    {
        DDALINE(i,237,i,243);
        DDALINE(317,i,323,i);
i+=20;
    }


    glEnd();
    glFlush();
}


int Round(int a)
{
    return (int)(a+0.5);
}


void DDALINE(int xa, int ya, int xb, int yb)
{
    int dx,dy,steps;
    dx=xb-xa;
    dy=yb-ya;
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    float xinc,yinc;
    xinc = dx/(float)(steps);
    yinc = dy/(float)(steps);
    float xd = xa;
    float yd = ya;
    glVertex2d(Round(xd),Round(yd)); 
    for(int i=0;i<steps;i++)
    {
        xd = xd + xinc;
        yd = yd + yinc;
        glVertex2d(Round(xd),Round(yd));            
    }
}

