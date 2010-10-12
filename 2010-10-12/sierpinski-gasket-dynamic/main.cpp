#include <time.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

int gCount = 1;
time_t gRandSeed;
void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 50.0, 0.0, 50.0, -1.0, 1.0);
}

void increaseDisplay() {
  gCount++;
  usleep(10000);
  glutPostRedisplay();
}


void display() {
  // just a rand seed hack for stably display
  srand(gRandSeed);
  
  glClear(GL_COLOR_BUFFER_BIT);
  GLfloat vertices[3][3] = { {0.0,0.0,0.0}, {25.0, 50.0, 0.0}, {50.0, 0.0, 0.0}};
  GLfloat p[3] = {7.5,5.0,0.0};
  
  glBegin(GL_POINTS);
  for (int i=0; i<gCount; ++i) {
    int x = rand()%3;
    
    p[0] = (p[0] + vertices[x][0])/2;
    p[1] = (p[1] + vertices[x][1])/2;
    
    glVertex3fv(p);
  }
  glEnd();
  glutSwapBuffers();
}

int main (int argc, char *argv[]) {
  gRandSeed = time(NULL);
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
