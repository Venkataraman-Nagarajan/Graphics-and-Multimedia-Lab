// #include<windows.h>
#include<GL/glut.h>

#include<iostream>
#include<algorithm>
#include<utility>
#include<cmath>
#include<stdlib.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ld X_LIMIT = 10, Y_LIMIT = 10, Z_LIMIT = 10;

const ld  SCREEN_FPS = 60;

const ll WINDOW_WIDTH = 700, WINDOW_HEIGHT = 700;

ll Y_Trans = 0, dir = 1;

void myInit() {
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPointSize(2);
    glLineWidth(5);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT,X_LIMIT,-Y_LIMIT,Y_LIMIT,-Z_LIMIT,Z_LIMIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);

    float light_diffuse[] = {0.7,0.7,0.7,1};
    float light_position[] = {0,0,1,0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void myDisplay() {
    myInit();
    glPushMatrix();

    //glColor3f(1,0,0);
    glTranslated(0,Y_Trans,0);
    float color[] = {1,0,0,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glutSolidSphere(3,30,30);
    
    glPopMatrix();
    glFlush();
}

void update() {
  if(Y_Trans == 5) dir = -1;
  if(Y_Trans == -5) dir = 1;

  Y_Trans += dir;
}

void myTimer(int i) {
    update();
    glutPostRedisplay();

    glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("JUmpin Chapang");
    myInit();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(0, myTimer, 0);

    glutMainLoop();
    return 0;
}