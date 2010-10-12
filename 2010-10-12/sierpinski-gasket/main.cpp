#include <stdlib.h>
#include <GLUT/GLUT.h>

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 50.0, 0.0, 50.0, -1.0, 1.0);
}

void display() {  
  GLfloat vertices[3][3] = { {0.0,0.0,0.0}, {25.0, 50.0, 0.0}, {50.0, 0.0, 0.0}};
  GLfloat p[3] = {7.5,5.0,0.0};
  
  glBegin(GL_POINTS);
  for (int i=0; i<5000; ++i) {
    int x = rand()%3;
    
    p[0] = (p[0] + vertices[x][0])/2;
    p[1] = (p[1] + vertices[x][1])/2;
    
    glVertex3fv(p);
  }
  glEnd();
  glFlush();
}

int main (int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("sierpinski gasket");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  
  return 0;
}
