#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

int xmin, xmax, ymin, ymax;
int code[4];

void test();

struct LineClipping
{
    float x, y;
    int binary[4];
} p1, p2;

void LineDDA(int xa, int ya, int xb, int yb)
{
    int dx = (xb - xa);
    int dy = (yb - ya);
    int steps;
    float xInc, yInc, x = xa, y = ya;

    steps = (abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));
    xInc = dx / (float)steps;
    yInc = dy / (float)steps;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    int k;
    for (k = 0; k < steps; k++)
    {
        x += xInc;
        y += yInc;
        glVertex2i(floor(x + 0.5), floor(y + 0.5));
    }

    glEnd();
    glFlush();
}

void check(struct LineClipping *p)
{
    if (p->x < xmin)
        p->binary[3] = 1;
    else
        p->binary[3] = 0;

    if (p->x > xmax)
        p->binary[2] = 1;
    else
        p->binary[2] = 0;

    if (p->y < ymin)
        p->binary[1] = 1;
    else
        p->binary[1] = 0;

    if (p->y > ymax)
        p->binary[0] = 1;
    else
        p->binary[0] = 0;
}

void calculate(struct LineClipping *p)
{
    int i, flag;
    float x, y;

    for (i = 0; i < 4; i++)
    {
        if (p->binary[i] == 0)
            flag = 0;
        else
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("\nNo intersection");
    else
    {
        if (p->binary[3] == 1)
            x = xmin;
        if (p->binary[2] == 1)
            x = xmax;
        if (p->binary[1] == 1)
            y = ymin;
        if (p->binary[0] == 1)
            y = ymax;

        if (p->binary[3] == 1 || p->binary[2] == 1)
        {
            float m = (p2.y - p1.y) / (float)(p2.x - p1.x);
            y = p->y + m * (x - p->x);
        }
        else
        {
            float m = (p2.y - p1.y) / (float)(p2.x - p1.x);
            x = p->x + (y - p->y) / m;
        }

        p->x = x;
        p->y = y;
    }
}

void find()
{
    calculate(&p1);
    printf("\n%f\t%f", p1.x, p1.y);
    calculate(&p2);
    printf("\n%f\t%f", p2.x, p2.y);
    check(&p1);
    check(&p2);


    for(int i = 0; i < 4; i++)
    {
    printf("\np1:%d", p1.binary[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        printf("\np2:%d", p2.binary[i]);
    }

    test();

}

void test()
{
  int i = 0, flag, flag1;

  for (i = 0; i < 4; i++)
  {
      if (p1.binary[i] == 0 && p2.binary[i] == 0)
      {
          flag = 0;
      }
      else
      {
          flag = 1;
          break;
      }
  }

  if (flag == 0)
  {
      printf("\nAccepted:");
  }
  else
  {
      for (i = 0; i < 4; i++)
      {
          code[i] = p1.binary[i] && p2.binary[i];
      }

      for (i = 0; i < 4; i++)
      {
          if (code[i] == 1)
          {
              flag1 = 0;
              break;
          }
          else
          {
              flag1 = 1;
          }
      }

      if (flag1 == 0)
      {
          printf("\nRejected:");
      }
      else
      {
          printf("\nPartially accepted:");
          find();
      }
  }

}

void Init()
{
  glClearColor(1.0, 1.0, 1.0, 0);
  glColor3f(0.0, 0.0, 0.0);
  gluOrtho2D(0, 640, 0, 480);
}

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  LineDDA(p1.x, p1.y, p2.x, p2.y);

  LineDDA(xmin, ymin, xmax, ymin);
  LineDDA(xmax, ymin, xmax, ymax);
  LineDDA(xmax, ymax, xmin, ymax);
  LineDDA(xmin, ymax, xmin, ymin);

  check(&p1);
  check(&p2);
  test();

  glColor3f(1.0, 0.0, 0.0);
  LineDDA(p1.x, p1.y, p2.x, p2.y);

}

int main(int argc, char **argv)
{
  printf("\nEnter the xmin and ymin value of a rectangle:");
  scanf("%d%d", &xmin, &ymin);
  printf("\nEnter the xmax and ymax value of a rectangle:");
  scanf("%d%d", &xmax, &ymax);
  printf("\nEnter the x and y value of point p1:");
  scanf("%f%f", &p1.x, &p1.y);
  printf("\nEnter the x and y value of point p2:");
  scanf("%f%f", &p2.x, &p2.y);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Line Clipping");
  Init();
  glutDisplayFunc(Display);
  glutMainLoop();

}
