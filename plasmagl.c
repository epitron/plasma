#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500

unsigned char pixels[HEIGHT][WIDTH][3];

void put_pixel(int x, int y, int r, int g, int b) {
  pixels[y][x][0] = r;
  pixels[y][x][1] = g;
  pixels[y][x][2] = b;
}

clampf(float n, float lower, float upper) {
  if (n < lower) n = lower;
  if (n > upper) n = upper;
  return n;
}

clampi(int n, int lower, int upper) {
  if (n < lower) n = lower;
  if (n > upper) n = upper;
  return n;
}

float f(x,y,i) {
  return sin(tan(cos(x*y*(i/4.0))));
}


int c = 0;

void clear_buffer() {
  int x, y;

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      pixels[y][x][0] = 0;
      pixels[y][x][1] = 0;
      pixels[y][x][2] = 0;
    }
  }
}

void render() {
  float i = c/1000.0;
  int x,y;
  unsigned char val = clampf(f(x,y,i), 0.0, 1.0) * 255;

  clear_buffer();
  
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      put_pixel(x, y, val, val, val);
    }
  }
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  render();
  glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);

  // glFlush();
  glutSwapBuffers();
  glutPostRedisplay();

  c++;

  // for (k = 0; k < 50000; k++) {
  //   x = rand() % WIDTH;
  //   y = rand() % HEIGHT;

  //   put_pixel(x, y, 255, 255, 255);
  // }
  
  // int j, k;
  // typedef GLfloat point2[2];
  // point2 p = {0.0, 0.0};
  // point2 vertices[3] = {{0.0, 0.0}, {249.0, 499.0}, {499.0, 0.0}};

  // glClear(GL_COLOR_BUFFER_BIT);
  
  // for (k = 0; k < 50000; k++) {
  //   j = rand() % 3;
  //   p[0] = (p[0] + vertices[j][0]) / 2.0;
  //   p[1] = (p[1] + vertices[j][1]) / 2.0;
  //   glBegin(GL_POINTS);
  //   glVertex2fv(p);
  //   glEnd();
  // }
  
  // glFlush();
}

void idle() {
  display();
}

void myinit(void) {
  // glClearColor(1.0, 1.0, 1.0, 1.0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}


void main(int argc, char **argv) {
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  // glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (0, 0);
  glutCreateWindow("Snow");

  glutIdleFunc(idle);
  glutDisplayFunc(display);
  
  myinit();
  
  glutMainLoop();
}

