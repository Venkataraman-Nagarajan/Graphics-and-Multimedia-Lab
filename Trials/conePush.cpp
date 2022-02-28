// #include<windows.h>
#include<GL/glut.h>

#include<iostream>
#include<algorithm>
#include<utility>
#include<stdlib.h>
#include<cmath>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld;

const ll X_LIMIT = 100, Y_LIMIT = 100, Z_LIMIT = 20;
const ll WINDOW_WIDTH = 700, WINDOW_HEIGHT = 700;
const ld SCREEN_FPS = 60;

ld multiply(vector<ld> a, vector<ld> b) {
    ld ans = 0;
    for(ll i=0;i<a.size();i++) {
        ans += a[i]*b[i]; 
    }

    return ans;
}

vector<ld> multiply(vector<vector<ld>> a, vector<ld> b) {
    vector<ld> ans;
    ld sum;
    for(ll i=0;i<a.size();i++) {
        sum = multiply(a[i], b);
        ans.push_back(sum);
    }

    return ans;
}

vector<ld> shear(vector<ld> point) {
    vector<vector<ld>> shear_mat;
    vector<ld> row;

    row.clear(); row.push_back(1); row.push_back(2); row.push_back(0); shear_mat.push_back(row);
    row.clear(); row.push_back(0); row.push_back(1); row.push_back(0); shear_mat.push_back(row);
    row.clear(); row.push_back(0); row.push_back(0); row.push_back(1); shear_mat.push_back(row);

    return multiply(shear_mat, point);
}

vector<ld> getHomo(vector<ld> point) {
    vector<ld> ans;
    ld h = 1;
    ans.push_back(point[0]*h);
    ans.push_back(point[1]*h);
    ans.push_back(h);
    return ans;
}

vector<ld> getPoint(vector<ld> point) {
    vector<ld> ans;
    ld h = point[2];
    ans.push_back(point[0]/h);
    ans.push_back(point[1]/h);
    return ans;
}

void bresenham(ld X1, ld Y1, ld X2, ld Y2) {
    ld dx = abs(X2-X1);
    ld dy = abs(Y2-Y1);

    ld stepX, stepY;

    if(X2>X1) stepX = 1; 
    else stepX = -1;

    if(Y2>Y1) stepY = 1;
    else stepY = -1;

    ld x = X1, xEnd = X2, y = Y1, yEnd = Y2;
    ld p;

    if(dx > dy) {
        p = 2*dy - dx;

        while(x != xEnd) {
            glBegin(GL_POINTS);
                glPushMatrix();
                    //glTranslated(-8,0,0);
                    glVertex2d(x-8, y);
                glPopMatrix();
                glPushMatrix();
                    //glTranslated(8,0,0);
                    vector<ld> point;
                    point.clear();
                    point.push_back(x+8); point.push_back(y);
                    vector<ld> new_point = getPoint(shear(getHomo(point)));
                    glVertex2d(new_point[0], new_point[1]);
                glPopMatrix();
            glEnd();
            
            x+=stepX;
            if(p < 0) {
                p += 2*dy;
            } else {
                p += 2*(dy - dx);
                y += stepY;
            }
        }

    } else {
        p = 2*dx - dy;

        while(y != yEnd) {
            glBegin(GL_POINTS);
                glPushMatrix();
                    //glTranslated(-8,0,0);
                    glVertex2d(x-8, y);
                glPopMatrix();
                glPushMatrix();
                    //glTranslated(8,0,0);
                    vector<ld> point;
                    point.clear();
                    point.push_back(x+8); point.push_back(y);
                    vector<ld> new_point = getPoint(shear(getHomo(point)));
                    glVertex2d(new_point[0], new_point[1]);
                glPopMatrix();
            glEnd();
            
            y+=stepY;
            if(p < 0) {
                p += 2*dx;
            } else {
                p += 2*(dx - dy);
                x += stepX;
            }
        }
    }
}

void plotPoints(ld x0,ld y0, ld x, ld y) {
    vector<vector<ld>> points;
    vector<ld> point;

    point.clear(); point.push_back(x0+x); point.push_back(y0+y); points.push_back(point);
    point.clear(); point.push_back(x0+x); point.push_back(y0-y); points.push_back(point);
    point.clear(); point.push_back(x0-x); point.push_back(y0-y); points.push_back(point);
    point.clear(); point.push_back(x0-x); point.push_back(y0+y); points.push_back(point);
    point.clear(); point.push_back(x0+y); point.push_back(y0+x); points.push_back(point);
    point.clear(); point.push_back(x0-y); point.push_back(y0+x); points.push_back(point);
    point.clear(); point.push_back(x0+y); point.push_back(y0-x); points.push_back(point);
    point.clear(); point.push_back(x0-y); point.push_back(y0-x); points.push_back(point);

    for(ll i=0;i<points.size();i++) {
        point = points[i];
        glBegin(GL_POINTS);
                glPushMatrix();
                    //glTranslated(-8,0,0);
                    glVertex2d(point[0]-8, point[1]);
                glPopMatrix();
                glPushMatrix();
                    //glTranslated(8,0,0);
                    point[0] +=8;
                    vector<ld> new_point = getPoint(shear(getHomo(point)));
                    glVertex2d(new_point[0], new_point[1]);
                glPopMatrix();
            glEnd();
    }
}

void midPont(ld x0, ld y0, ld r) {
    ld p = 1-r;
    ld x=0,y=r;

    while(x <= y) {
        plotPoints(x0,y0,x,y);

        x += 0.1;
        if(p<0) {
            p+=1+2*x;
        } else {
            p+=1+2*x-2*y;
            y-=0.1;
        }
    }
}

void myInit() {
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPointSize(3);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-X_LIMIT,X_LIMIT,-Y_LIMIT,Y_LIMIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
}

void myDisplay() {
    midPont(0,0,5);
    bresenham(-5,0,0,10);
    bresenham(5,0,0,10);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("cone ah thalrom");
    myInit();

    glutDisplayFunc(myDisplay);

    glutMainLoop();
    return 0;
}