#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef unsigned char byte;

#define WIDTH 500
#define HEIGHT 500

int t = 0;
byte pixels[HEIGHT][WIDTH][4];

void put_pixel(int x, int y, int r, int g, int b) {
  pixels[y][x][0] = r;
  pixels[y][x][1] = g;
  pixels[y][x][2] = b;
  pixels[y][x][3] = 127;
}

clampf(float n, float lower, float upper) {
  float v = n;
  if (v < lower) v = lower;
  if (v > upper) v = upper;
  return v;
}

clampi(int n, int lower, int upper) {
  int v = n;
  if (v < lower) v = lower;
  if (v > upper) v = upper;
  return v;
}


void clear_buffer() {
  // // Long:
  // int x, y;
  // for (y = 0; y < HEIGHT; y++) {
  //   for (x = 0; x < WIDTH; x++) {
  //     pixels[y][x][0] = 0;
  //     pixels[y][x][1] = 0;
  //     pixels[y][x][2] = 0;
  //   }
  // }

  // Short
  memset(pixels, 0, sizeof(pixels));
}

float f(int x, int y, int t) {
  float v;

  v = sin(
        tan(
          cos(
            (float)x * (float)y * ((float)t/4.0)
          )
        )
      );
  
  // printf("[%dx%d = %f] ", x,y,v);

  return v;
}


void draw() {
  float i = t/1000.0;
  int x,y;
  float val;

  clear_buffer();
  
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      val = clampf( f(x,y,i), 0.0, 1.0 ) * 255.0;
      // printf("%f\n", val);
      put_pixel(x, y, (int)val, (int)val, (int)val);
    }
  }

  t++;
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  draw();
  glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  // glFlush();
  glutSwapBuffers();
  glutPostRedisplay();

  // printf("%d\n", t);

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
  printf("%f clamped: %f\n", 10.0, clampf(10.0, 2.0, 9.0));

  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  // glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (0, 0);
  glutCreateWindow("plasma");

  glutIdleFunc(idle);
  glutDisplayFunc(display);
  
  myinit();
  
  glutMainLoop();
}

