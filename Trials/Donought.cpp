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

const int X_LIMIT = 2;
const int Y_LIMIT = 2;
const int Z_LIMIT = 2;

int xangle = 0;
int yangle = 0;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,1);

    //glPointSize(2);
    //glLineWidth(5);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT, X_LIMIT, -Y_LIMIT, Y_LIMIT, -Z_LIMIT, Z_LIMIT);
    //gluPerspective(200, 1, 0.1, 500);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,1,0,0,0,0,1,0);
}

void myDisplay() {
    glPushMatrix();
    glRotated(xangle, 1, 0, 0);
    glRotated(yangle, 0, 1, 0);
    //glutWireCube(1);

    glutSolidTorus(0.4, 0.8, 10, 100);

    glPopMatrix();
    glFlush();
}

void update() {
    myInit();
    float x = rand() % (100 - 0 + 1);
    std::cout << x << " \n";
    if(x < 50) {
        xangle = (xangle+1)%361;
    }
    // else if(x < 50) {
    //     xangle--;
    // }
    // else if(x < 75) {
    //     yangle++;
    // }
    else {
       yangle = (yangle+1)%361;
    }
}

void myTimer(int i) {
    update();
    glutPostRedisplay();
    myDisplay();

    glutTimerFunc(100, myTimer, 0);
}

int main(int argc, char* argv[]) {
    srand(0);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDWOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Torus");

    myInit();

    glutDisplayFunc(myDisplay);    
    glutTimerFunc(0, myTimer, 0);
    
    glutMainLoop();
    return 0;
}