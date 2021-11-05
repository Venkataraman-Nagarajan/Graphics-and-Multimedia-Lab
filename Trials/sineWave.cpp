#include<GL/freeglut.h>
#include<GL/gl.h>
#include<GL/glut.h>

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<stdlib.h>

using namespace std;

typedef long double ld;
typedef long long ll;

const int WINDWOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

const int SCREEN_FPS = 10;

const int X_LIMIT = 10;
const int Y_LIMIT = 10;
const int Z_LIMIT = 10;

int translation_f = 0;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 1, 0, 0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT, X_LIMIT, -Y_LIMIT, Y_LIMIT, -Z_LIMIT, Z_LIMIT);
}

void update() {
    myInit();
    translation_f += 1;
    return;
}

void myDisplay() {
    glColor3d(1,0,0);
    glBegin(GL_POINTS);
        
    for(double i=-X_LIMIT; i<=X_LIMIT; i+=0.01) {
            glVertex2d(i, sin(i+translation_f));
    }

    glEnd();
    glFlush();
}

void runMainLoop(int i) {
    update();
    glutPostRedisplay();
    myDisplay();

    glutTimerFunc(1000/SCREEN_FPS, runMainLoop, 0);
}

void myKeyboard(unsigned char c, int x, int y);
void mySpecial(int c, int x, int y);
 
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
    glutInitWindowSize(WINDWOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Sine wave");

    myInit();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(1000/ SCREEN_FPS, runMainLoop, 0);
    //glutKeyboardFunc(myKeyboard);
    //glutSpecialFunc(mySpecial);

    glutMainLoop();
    return 0;
}

