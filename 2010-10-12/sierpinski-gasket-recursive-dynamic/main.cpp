#include <time.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

/* initial triangle */
GLfloat v[3][2]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};

int gCount = 1;

/* specify one triangle */
void triangle( GLfloat *a, GLfloat *b, GLfloat *c) {
  glVertex2fv(a);
  glVertex2fv(b);
  glVertex2fv(c);
}

/* triangle subdivision using vertex numbers */
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m) {

  GLfloat v0[2], v1[2], v2[2];
  int j;
  
  if( m > 0 )
  {
    for(j=0; j<2; j++) {
      v0[j]=(a[j]+b[j])/2;
    }
    
    for(j=0; j<2; j++) {
      v1[j]=(a[j]+c[j])/2;
    }
    
    for(j=0; j<2; j++) {
      v2[j]=(b[j]+c[j])/2;
    }
    
    divide_triangle(a, v0, v1, m-1);
    divide_triangle(c, v1, v2, m-1);
    divide_triangle(b, v2, v0, m-1);
  }
  else {
    triangle(a,b,c); /* draw triangle at end of recursion */
  }
}


void init() {
  /* attributes */
  glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
  glColor3f(1.0, 0.0, 0.0); /* draw in red */
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);
}

void increaseDisplay() {
  if (gCount <= 15) {
    gCount++;
  }

  sleep(1);
  glutPostRedisplay();
}


void display() {

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  divide_triangle(v[0], v[1], v[2], gCount);
  glEnd();
  
  glutSwapBuffers();
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("sierpinski gasket");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(increaseDisplay);
  glutMainLoop();
  
  return 0;
}
