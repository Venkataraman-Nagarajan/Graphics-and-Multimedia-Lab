// #include<windows.h>
#include<GL/glut.h>

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<utility>
#include<stdlib.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ll X_LIMIT = 300, Y_LIMIT = 300, Z_LIMIT = 300;

const ll WINDOW_WIDTH = 300, WINDOW_HEIGHT = 300;

const ld SCREEN_FPS = 60;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,1);

    glPointSize(2);
    glLineWidth(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT,X_LIMIT,-Y_LIMIT,Y_LIMIT,-Z_LIMIT,Z_LIMIT);
    //gluOrtho2D(-X_LIMIT,X_LIMIT,-Y_LIMIT,Y_LIMIT);


    // gluPerspective(100,1,0.1,100);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // gluLookAt(0,0,1,0,0,0,0,1,0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    /*
    glShadeModel(GL_SMOOTH);

    float light_diffuse[] = {0.7,0.7,0.7,1};
    float light_position[] = {0,0,1,0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    */
}

void myDisplay() {
    
    glFlush();
}


void update() {
    myInit();
    // updation
}

void myTimer(int i) {
    update();
    glutPostRedisplay();

    glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
}


void myKeyboard(unsigned char c, int x, int y) {
    switch(c) {
        case ' ': {
            break;
        }
    }
    return;
}

void mySpecial(int c, int x, int y) {
    // GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("Trials");
    myInit();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);

    glutMainLoop();
    return 0;
}