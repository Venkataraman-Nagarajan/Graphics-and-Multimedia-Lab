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

const ll X_LIMIT = 50, Y_LIMIT = 50, Z_LIMIT = 50;

const ll WINDOW_WIDTH = 750, WINDOW_HEIGHT = 750;

const ld SCREEN_FPS = 60;

enum Dir{LEFT, RIGHT, ALL};
//
ll Zangle = 0;
ld blueX = -17.5, blueY = -17.5;
ld greenX = 17.5, greenY = 17.5;
ll RotAngle = 0;
//

void bresenhamLine(ll X1, ll Y1, ll X2, ll Y2, ll Z);
void DDALine(ll X1, ll Y1, ll X2, ll Y2, ll Z);
void midPointCircle(ld x0, ld y0, ld r, ld z, Dir d=ALL);

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1,0,1,1);

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

void drawBorders() {
    glColor3f(0,1,1);
    //borders
    glPointSize(2);
    bresenhamLine(-40,-40,-40,40,-2);
    bresenhamLine(-40,40,40,40,-2);
    bresenhamLine(40,40,40,-40,-2);
    bresenhamLine(40,-40,-40,-40,-2);
    
    glPointSize(2);
    glColor3f(1,1,0);
    midPointCircle(0,0,50,-3);
}

void drawBoard() {  
    //checker board
    glColor3f(0,0,0);
    glPointSize(4);
    
    bresenhamLine(-20,-20,-20,20,-1);
    bresenhamLine(-20,20,20,20,-1);
    bresenhamLine(20,20,20,-20,-1);
    bresenhamLine(20,-20,-20,-20,-1);
    //ll k =-1;
    for(ld k=-1;k<=-0.5;k+=0.1) {
        for(ll i=-20;i<20;i+=5) {
            for(ll j=-20;j<20;j+=5) {
                if(abs(i%2) == abs(j%2)) {
                    glColor3f(0,0,0);
                } else {
                    glColor3f(1,1,1);
                }

                glBegin(GL_POLYGON);
                    glVertex3d(i,j,k);
                    glVertex3d(i+5,j,k);
                    glVertex3d(i+5,j+5,k);
                    glVertex3d(i,j+5,k);
                glEnd();
        
            } 
        }
    }
}

void drawCoins() {
    //coins
    for(ld k=-0.5;k<=0;k+=0.1) {
        for(ld r=0;r<=1.5;r+=0.1) {
            glColor3f(0.3,0,1);
            midPointCircle(blueX, blueY, r, k);
            glColor3f(0.3,1,0);
            midPointCircle(greenX, greenY, r, k);
        }
    }

    for(ld k=-0.5;k<=0.5;k+=0.1) {
        for(ld r=1.5;r<=2;r+=0.1) {
            glColor3f(0,0,1);
            midPointCircle(blueX, blueY, r, k);
            glColor3f(0,1,0);
            midPointCircle(greenX, greenY, r, k);
        }
    }
}

void drawYinYang() {
    glPushMatrix();
        glRotated(RotAngle, 0, 0, 1);
        for(ld k=0;k<=0.5;k+=0.1) {
            for(ld r=0;r<=5;r+=0.1) {
                glColor3f(0,0,0);
                midPointCircle(30,30,r,k,LEFT);
                glColor3f(1,1,1);
                midPointCircle(30,30,r,k,RIGHT);
            }

            for(ld r=0;r<=2.5;r+=0.1) {
                glColor3f(0,0,0);
                midPointCircle(30,32.5,r,k+0.5,RIGHT);
                glColor3f(1,1,1);
                midPointCircle(30,27.5,r,k+0.5,LEFT);
            }

            for(ld r=0;r<=1.25;r+=0.1) {
                glColor3f(1,1,1);
                midPointCircle(30,32.5,r,k+1);
                glColor3f(0,0,0);
                midPointCircle(30,27.5,r,k+1);
            }
        }
    glPopMatrix();
}
 
void myDisplay() {
    myInit();

    glRotated(Zangle, 1, 0, 0);

    drawBorders();
    drawBoard();
    drawCoins();
    drawYinYang();

    glFlush();
}


void update() {
    // updation
    RotAngle = (RotAngle + 1)%360;
}

void myTimer(int i) {
    update();
    glutPostRedisplay();

    glutTimerFunc(1000/SCREEN_FPS, myTimer, 0);
}


void myKeyboard(unsigned char c, int x, int y) {
    switch(c) {
        case 'w': {
            blueY = min(blueY+5, (ld)17.5);
            break;
        }
        case 's': {
            blueY = max(blueY-5, (ld)-17.5);
            break;
        }
        case 'a': {
            blueX = max(blueX-5, (ld)-17.5);
            break;
        }
        case 'd': {
            blueX = min(blueX+5, (ld)17.5);
            break;
        }
    }
    return;

   // glutPostRedisplay();
}

void mySpecial(int c, int x, int y) {
    // GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
    switch(c) {
        case GLUT_KEY_UP: {
            greenY = min(greenY+5, (ld)17.5);
            break;
        }
        case GLUT_KEY_DOWN: {
            greenY = max(greenY-5, (ld)-17.5);
            break;
        }
        case GLUT_KEY_LEFT: {
            greenX = max(greenX-5, (ld)-17.5);
            break;
        }
        case GLUT_KEY_RIGHT: {
            greenX = min(greenX+5, (ld)17.5);
            break;
        }
        case GLUT_KEY_PAGE_UP: {
            Zangle += 2;
            break;
        }
        case GLUT_KEY_PAGE_DOWN: {
            Zangle -= 2;
            break;
        }
    }

    return;
     
    //glutPostRedisplay();
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

void bresenhamLine(ll X1, ll Y1, ll X2, ll Y2, ll Z) {
    ll dx = abs(X2-X1);
    ll dy = abs(Y2-Y1);

    ll stepX, stepY;
    ll p;

    if(X1 < X2) stepX = 1;
    else stepX = -1;

    if(Y1 < Y2) stepY = 1;
    else stepY = -1;

    ll x = X1, y = Y1, xEnd = X2, yEnd = Y2;

    if(dx > dy) {
        p = 2*dy - dx;

        while(x != xEnd) {
            glBegin(GL_POINTS);
                glVertex3d(x,y,Z);
            glEnd();

            x += stepX;
            if(p < 0) {
                p += 2*dy;
            } else {
                p += 2*(dy - dx);
                y+=stepY;
            }
        }
    } else {
        p = 2*dx - dy;

        while(y != yEnd) {
            glBegin(GL_POINTS);
                glVertex3d(x,y,Z);
            glEnd();

            y += stepY;
            if(p < 0) {
                p += 2*dx;
            } else {
                p += 2*(dx - dy);
                x += stepX;
            }
        }
    }
}

void DDALine(ll X1, ll Y1, ll X2, ll Y2, ll Z) {
    ll dx = (X2 - X1);
    ll dy = (Y2 - Y1);

    ld steps, xInc, yInc;

    if(abs(dx) > abs(dy))   steps = abs(dx);
    else                    steps = abs(dy);

    xInc = dx/steps; yInc = dy/steps;

    for(ll i=0;i<=steps;i++) {
        glBegin(GL_POINTS); 
            glVertex3d(X1,Y1,Z);
        glEnd();

        X1 += xInc;
        Y1 += yInc;
    }

}

void plotPoints(ld x0, ld y0, ld x, ld y, ld z, Dir d) {
    glBegin(GL_POINTS);
        if(d != LEFT) {
            glVertex3d(x0-x,y0-y,z);
            glVertex3d(x0-y,y0-x,z);
            glVertex3d(x0-x,y0+y,z);
            glVertex3d(x0-y,y0+x,z);
        } 
        if(d != RIGHT) {
            glVertex3d(x0+x,y0+y,z);
            glVertex3d(x0+y,y0+x,z);
            glVertex3d(x0+x,y0-y,z);
            glVertex3d(x0+y,y0-x,z);
        }
    glEnd();
}

void midPointCircle(ld x0, ld y0, ld r, ld z, Dir d) {
    ld p = 1-r;
    ld x = 0, y = r;

    while(x <= y) {
        //plot x,y;
        plotPoints(x0,y0,x,y,z,d);

        x += 0.1;
        if(p < 0) {
            p+= 1+2*x;
        } else {
            p+= 1+2*x-2*y;
            y-=0.1;
        }
    } 

}
