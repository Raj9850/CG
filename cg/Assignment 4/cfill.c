#include<stdio.h>
#include<GL/glut.h>
#include<math.h>


int i,n,ch;


//Polygon Pixel
int v[2][10];


//Polygon Plotting
float fillColor[3],boundaryColor[3],oldColor[3];


int  Round(int a);
void ddaline(int xa, int ya, int xb, int yb);
void polygonInput();
void polygonOutput();
void boundaryFill(int x, int y , float* boundaryColor , float* fillColor);
void polygonBoundaryFill();
void floodFill(int x, int y, float* fillColor, float* oldColor);
void polygonFloodFill();
void mouse(int btn, int state, int x, int y);
void draw();


int main(int argc , char **argv)
{
	printf("Enter Algorithm You Want to USE ...");
	printf("\n1.Boundary Fill Algorithm \n2.Flood Fill Algorithm \n> > > ");
	scanf("%d",&ch);
	if(ch==1)
	{
		polygonBoundaryFill();
	}
	else if(ch==2)
	{
		polygonFloodFill();
	}
   	polygonInput();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Polygon Filling");
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();


	return 0;
}


void boundaryFill(int x, int y , float* boundaryColor , float* fillColor)
{
	float currentColor[3];
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,currentColor);
	if((currentColor[0]!=boundaryColor[0] || currentColor[1]!=boundaryColor[1] || currentColor[2]!=boundaryColor[2]) && (currentColor[0]!=fillColor[0] || currentColor[1]!=fillColor[1] || currentColor[2]!=fillColor[2]))
	{
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
		glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();
		boundaryFill(x+1, y  , boundaryColor, fillColor);
		boundaryFill(x-1, y  , boundaryColor, fillColor);
		boundaryFill(x  , y+1, boundaryColor, fillColor);
		boundaryFill(x  , y-1, boundaryColor, fillColor);
    }
}


void polygonBoundaryFill()
{
	printf("Enter Boundary Color (RGB) >> ");
    for(i = 0; i < 3; i++)
    {
    	scanf("%f",&boundaryColor[i]);
    }
}


void floodFill(int x, int y, float* oldColor, float* fillColor)
{
	float currentColor[3];
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,currentColor);
	if((currentColor[0]==oldColor[0] || currentColor[1]==oldColor[1] || currentColor[2]==oldColor[2]) && (currentColor[0]!=fillColor[0] || currentColor[1]!=fillColor[1] || currentColor[2]!=fillColor[2]))
	{
		glColor3f(fillColor[0],fillColor[1],fillColor[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		floodFill(x+1, y   , oldColor ,fillColor);
		floodFill(x-1, y   , oldColor ,fillColor);
		floodFill(x  , y+1 , oldColor ,fillColor);
		floodFill(x  , y-1 , oldColor ,fillColor);
		//floodFill(x+1, y+1 , oldColor ,fillColor);
		//floodFill(x-1, y+1 , oldColor ,fillColor);
		//floodFill(x-1, y-1 , oldColor ,fillColor);
		//floodFill(x+1, y-1 , oldColor ,fillColor);
	}
}


void polygonFloodFill()
{
	printf("Enter BackGround Color (RGB) >> ");
    for(i = 0; i < 3; i++)
    {
    	scanf("%f",&oldColor[i]);
    }
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glPointSize(3.0);
	polygonOutput();
	glEnd();
	glFlush();   
}


void mouse(int btn, int state, int x, int y)
{
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)
	{
        if(state==GLUT_DOWN)
		{
			if(ch==1)
			{
				boundaryFill(x,y,boundaryColor,fillColor);
			}
			else if(ch==2)
			{
				floodFill(x,y,oldColor,fillColor);
			}
        }
    }
}


void polygonInput()
{   
    printf("Enter Fill color (RGB)  >> ");
    for(i = 0; i<3; i++)
    {
    	scanf("%f",&fillColor[i]);
    }   	
	printf("Enter The Number of vertices ");
	scanf("%d",&n);
	//Take Input
	for(i=0;i<n;i++)
	{
		printf("Enter The value of x[%d][%d] ",0,i);
		scanf("%d",&v[0][i]);
		printf("Enter The value of y[%d][%d] ",1,i);
		scanf("%d",&v[1][i]);		
	}
	v[0][i]=v[0][0];
	v[1][i]=v[1][0];
}


void polygonOutput()
{
	//Show Output
	for(i=0;i<n;i++)
	{
		ddaline(v[0][i],v[1][i],v[0][i+1],v[1][i+1]);
	}
}


int Round(int a)
{
	return (int)(a+0.5);
}


void ddaline(int xa, int ya, int xb, int yb)
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
	float xinc,yinc,x,y;
	xinc=dx/(float)(steps);
	yinc=dy/(float)(steps);
	x=xa,y=ya;
	glVertex2d(Round(x),Round(y));
	for(int i=0;i<steps;i++)
	{
		x=x+xinc;
		y=y+yinc;
		glVertex2d(Round(x),Round(y));
	}	
}
