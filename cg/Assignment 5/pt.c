#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int Round(float x)
{
	return (int)(x+0.5);
}

void matrixmul(int translate[3][3] , int in[3][10] , int out[3][10] , int size)
{
	int j;
	for(int i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < size ; j++)
		{
			out[i][j] = 0;
			for(int k = 0 ; k < 3 ; k++)
			{
				out[i][j] += translate[i][k] * in[k][j];
			}
		}
	}
	out[0][j] = out[0][0];
	out[1][j] = out[1][0];
	out[2][j] = out[2][0];
	

	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < size ; j++)
		{
			printf("%d\t" , out[i][j]);
		}
		printf("\n");
	}
}



//Draw Line
void dda(int xa , int ya, int xb , int yb)
{
	int dx , dy , steps;
	float x_inc , y_inc, x, y;
	
	dx = xb - xa;
	dy = yb- ya;
	
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
		
	x_inc = dx / (float)(steps);
	y_inc = dy / (float)(steps);	
	
	x = xa;
	y = ya;
	
	glVertex2d(Round(x), Round(y));
	
	for(int i = 0 ; i < steps ; i++)
	{
		x += x_inc;
		y += y_inc;
		glVertex2d(Round(x), Round(y));
	}
}

void polygonTranslate()
{
	int numVertex ;
	printf("Enter the number of vertices :");
	scanf("%d" , &numVertex);
	
	int vertex[3][10];
	int out[3][10];
	
	for(int i = 0; i < numVertex ; i++)
	{
		printf("Enter x coordinate of %d vertex : " , i+1);
		scanf("%d" , &vertex[0][i]);
		printf("Enter y coordinate of %d vertex : " , i+1);
		scanf("%d" , &vertex[1][i]);
		vertex[2][i] = 1;
	}
	
	vertex[0][numVertex] = vertex[0][0];
	vertex[1][numVertex] = vertex[1][0];
	vertex[2][numVertex] = vertex[2][0];
	
	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < numVertex ; j++)
		{
			printf("%d\t" , vertex[i][j]);
		}
		printf("\n");
	}
	
	/*for(int i = 0; i <= numVertex ; i++)
	{
		printf("%d , %d\n" , vertex[0][i] , vertex[1][i]);
	}*/
	
	
	for(int i = 0; i < numVertex ; i++)
	{
		dda(vertex[0][i] , vertex[1][i] , vertex[0][i+1] , vertex[1][i+1]);
	}
	
	int tx , ty;
	printf("Enter the x distance to translate the polygon: ");
	scanf("%d" , &tx);
	printf("Enter the y distance to translate the polygon: ");
	scanf("%d" , &ty);
	int translate[3][3] = {{1,0,tx} , {0,1,ty} , {0,0,1}};
	
	/*for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			printf("%d\t" , translate[i][j]);
		}
		printf("\n");
	}*/
	
	matrixmul(translate , vertex , out, numVertex);
	
	glColor3f(1.0, 0.0 ,0.0);
	for(int i = 0; i < numVertex ; i++)
	{
		dda(out[0][i] , out[1][i] , out[0][i+1] , out[1][i+1]);
	}
}

void polygonScale()
{
	int numVertex ;
	printf("Enter the number of vertices :");
	scanf("%d" , &numVertex);
	
	int vertex[3][10];
	int out[3][10];
	
	for(int i = 0; i < numVertex ; i++)
	{
		printf("Enter x coordinate of %d vertex : " , i+1);
		scanf("%d" , &vertex[0][i]);
		printf("Enter y coordinate of %d vertex : " , i+1);
		scanf("%d" , &vertex[1][i]);
		vertex[2][i] = 1;
	}
	
	vertex[0][numVertex] = vertex[0][0];
	vertex[1][numVertex] = vertex[1][0];
	vertex[2][numVertex] = vertex[2][0];
	
	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < numVertex ; j++)
		{
			printf("%d\t" , vertex[i][j]);
		}
		printf("\n");
	}
	
	/*for(int i = 0; i <= numVertex ; i++)
	{
		printf("%d , %d\n" , vertex[0][i] , vertex[1][i]);
	}*/
	
	
	for(int i = 0; i < numVertex ; i++)
	{
		dda(vertex[0][i] , vertex[1][i] , vertex[0][i+1] , vertex[1][i+1]);
	}
	
	int sx , sy;
	printf("Enter the x distance to scale the polygon: ");
	scanf("%d" , &sx);
	printf("Enter the y distance to scale the polygon: ");
	scanf("%d" , &sy);
	int scale[3][3] = {{sx,0,0} , {0,sy,0} , {0,0,1}};
	
	/*for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			printf("%d\t" , translate[i][j]);
		}
		printf("\n");
	}*/
	
	matrixmul(scale , vertex , out, numVertex);
	
	glColor3f(1.0, 0.0 ,0.0);
	for(int i = 0; i < numVertex ; i++)
	{
		dda(out[0][i] , out[1][i] , out[0][i+1] , out[1][i+1]);
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	//function
	polygonScale();
	
	glEnd();
	glFlush();
}

int main(int argc , char **argv)
{	
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0); 
	glutInitWindowSize(640, 480);
	glutCreateWindow("Polygon");
	glClearColor(1.0 ,1.0 ,1.0, 0);
	glColor3f(0.0 , 0.0, 0.0);
	gluOrtho2D(0 , 640, 0 ,480);
	glutDisplayFunc(Draw);
	glutMainLoop();

	return 0;
}

