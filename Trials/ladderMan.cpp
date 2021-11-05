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

const ld SCREEN_FPS = 1;

const int X_LIMIT = 300;
const int Y_LIMIT = 300;
const int Z_LIMIT = 300;

int ITERATION = 0, STEP = 1, LADDER_STEP = 40;

void update();

void drawLadder();
void drawPerson();

void midpointCircleAlgo(ld x0, ld y0, ld r);

void myInit();
void myDisplay();

void myTimer(int i);
void myKeyboard(unsigned char key, int x, int y);
void mySpecial(int key, int x, int y);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDWOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("Ladder Man");
    myInit();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(0, myTimer, 0);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);

    glutMainLoop();
    return 0;
}

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT,X_LIMIT,-Y_LIMIT,Y_LIMIT,-Z_LIMIT,Z_LIMIT);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void myDisplay() {
    drawLadder();
    drawPerson();

    glFlush();
}

void myTimer(int i) {
    update();
    glutPostRedisplay();
    myDisplay();

    glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
}

void myKeyboard(unsigned char key, int x, int y) {

}

void mySpecial(int key, int x, int y) {

}

void update() {
    ITERATION += STEP;
    if(ITERATION > 10) STEP = -1;
    if(ITERATION <= 2) STEP = 1;
    myInit();
}

void drawPerson() {
    glLineWidth(2);

    glColor3f(1,1,0);

    //face
    ld centre = -250 + LADDER_STEP*(ITERATION+1);
    ld radius = LADDER_STEP/4;
    midpointCircleAlgo(0, centre, radius);

    //stick-spine
    ld spine_start = centre-radius;
    ld spine_end = centre-radius-LADDER_STEP;
    glBegin(GL_LINES);
        glVertex2d(0, spine_start);
        glVertex2d(0, spine_end);
    glEnd();


    //left body part functions
    if(ITERATION % 2) {
        //left-hand
        ld hand_start = centre-radius-3*LADDER_STEP/4;
        ld hand_end = centre-radius-LADDER_STEP/4+LADDER_STEP;
        glBegin(GL_LINES);
            glVertex2d(0, hand_start);
            glVertex2d(-25, hand_end);
        glEnd();

        //left-leg
        ld leg_start = spine_end;
        ld leg_end = centre-radius-LADDER_STEP*9/4;
        glBegin(GL_LINES);
            glVertex2d(0, leg_start);
            glVertex2d(-25, leg_end);
        glEnd();

        //right-hand
        hand_start = centre-radius-3*LADDER_STEP/4;
        hand_end = centre-radius-LADDER_STEP/4;
        glBegin(GL_LINES);
            glVertex2d(0, hand_start);
            glVertex2d(25, hand_end);
        glEnd();
    
        //right-leg
        leg_start = spine_end;
        leg_end = centre-radius-LADDER_STEP*9/4-LADDER_STEP;
        glBegin(GL_LINES);
            glVertex2d(0, leg_start);
            glVertex2d(25, leg_end);
        glEnd();
    } 

    //right body part functions
    else {
        //left-hand
        ld hand_start = centre-radius-3*LADDER_STEP/4;
        ld hand_end = centre-radius-LADDER_STEP/4;
        glBegin(GL_LINES);
            glVertex2d(0, hand_start);
            glVertex2d(-25, hand_end);
        glEnd();

        //left-leg
        ld leg_start = spine_end;
        ld leg_end = centre-radius-LADDER_STEP*9/4-LADDER_STEP;
        glBegin(GL_LINES);
            glVertex2d(0, leg_start);
            glVertex2d(-25, leg_end);
        glEnd();

        //right-hand
        hand_start = centre-radius-3*LADDER_STEP/4;
        hand_end = centre-radius-LADDER_STEP/4+LADDER_STEP;
        glBegin(GL_LINES);
            glVertex2d(0, hand_start);
            glVertex2d(25, hand_end);
        glEnd();
    
        //right-leg
        leg_start = spine_end;
        leg_end = centre-radius-LADDER_STEP*9/4;
        glBegin(GL_LINES);
            glVertex2d(0, leg_start);
            glVertex2d(25, leg_end);
        glEnd();
    }

}

void drawLadder() {
    glLineWidth(4);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);
        glVertex2d(-30, -285);
        glVertex2d(-30, 285);

        glVertex2d(30, -285);
        glVertex2d(30, 285);
    glEnd();

    for(ll i=-270;i<=270;i+=LADDER_STEP) {
        glBegin(GL_LINES);
            glVertex2d(30,i);
            glVertex2d(-30,i);
        glEnd();
    }
}

void printPoints(ld x0, ld y0, ld x, ld y) {
    glBegin(GL_POINTS);
        glVertex2d(x0+x,y0+y);
        glVertex2d(x0+x,y0-y);
        glVertex2d(x0-x,y0+y);
        glVertex2d(x0-x,y0-y);
        glVertex2d(x0+y,y0+x);
        glVertex2d(x0+y,y0-x);
        glVertex2d(x0-y,y0+x);
        glVertex2d(x0-y,y0-x);
    glEnd();
}

void midpointCircleAlgo(ld x0, ld y0, ld r) {
    ld x=0, y=r;
    ld p= 1-r;

    while(x<y) {
        printPoints(x0,y0,x,y);
        x++;

        if(p<0) {
            p += 1+2*x;
        } else {
            p += 1+2*(x-y);
            y--;
        }
        
    }
}

