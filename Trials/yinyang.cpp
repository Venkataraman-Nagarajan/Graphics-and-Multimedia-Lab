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

const int X_LIMIT = 50;
const int Y_LIMIT = 50;
const int Z_LIMIT = 50;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glClearColor(1,0,1,1);
    glPointSize(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glOrtho(-X_LIMIT, X_LIMIT, -Y_LIMIT, Y_LIMIT, -Z_LIMIT, Z_LIMIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// void myTimer(int i) {
//     update();
//     glutPostRedisplay();
//     myDisplay();

//     glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
// }   

void MidPointAlgoLeftSemi(int px, int py, double r) {
    double x=0,y=r;
    double p = 1-r;

    glBegin(GL_POINTS);

    while(x<y) {
        glVertex2d(px-x, py-y);
        glVertex2d(px-x, py+y);
        glVertex2d(px-y, py-x);
        glVertex2d(px-y, py+x);
        
        x+=0.01;

        if(p<0) {
            p+= 1+2*x;
        } else {
            p += 1+2*(x-y);
            y-=0.01;
        }
    }

    glEnd();
}

void MidPointAlgoRightSemi(int px, int py, double r) {
    double x=0,y=r;
    double p = 1-r;

    glBegin(GL_POINTS);

    while(x<y) {
        glVertex2d(px+x, py-y);
        glVertex2d(px+x, py+y);
        glVertex2d(px+y, py-x);
        glVertex2d(px+y, py+x);
        
        x+=0.01;

        if(p<0) {
            p+= 1+2*x;
        } else {
            p += 1+2*(x-y);
            y-=0.01;
        }
    }

    glEnd();
}

void myDisplay() {
    //Draw outer semis
    myInit();

    ll radius = 20;


    //Outer Semi
    glColor3f(1,1,1);
    for(double i=0;i<=radius;i+=0.01) 
        MidPointAlgoLeftSemi(0,0,i);
    glColor3f(0,0,0);
    for(double i=0;i<=radius;i+=0.01) 
        MidPointAlgoRightSemi(0,0,i);
        

    //inner semi
    glColor3f(0,0,0);
    for(double i=0;i<=radius/2;i+=0.01) 
        MidPointAlgoLeftSemi(0,radius/2,i);
    glColor3f(1,1,1);
    for(double i=0;i<=radius/2;i+=0.01) 
        MidPointAlgoRightSemi(0,-radius/2,i);
    
    //inner ccircle
    glColor3f(1,1,1);
    for(double i=0;i<=radius/5;i+=0.01) { 
        MidPointAlgoLeftSemi(0,radius/2,i);
        MidPointAlgoRightSemi(0,radius/2,i);
    }
    glColor3f(0,0,0);
    for(double i=0;i<=radius/5;i+=0.01) { 
        MidPointAlgoLeftSemi(0,-radius/2,i);
        MidPointAlgoRightSemi(0,-radius/2,i);
    }
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB| GLUT_SINGLE|GLUT_DEPTH);
    glutInitWindowSize(WINDWOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("KungFu Panda");

    myInit();

    glutDisplayFunc(myDisplay);
    //glutTimerFunc(0, myTimer, 0);
    //glutKeyboardFunc(myKeyBoard);
    //glutSpecialFunc(mySpecial);

    glutMainLoop();
    return 0;
}