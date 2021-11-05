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

int iter_count = 0;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glPointSize(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-X_LIMIT, X_LIMIT, -Y_LIMIT, Y_LIMIT, -Z_LIMIT, Z_LIMIT);

    glEnable(GL_DEPTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MidPointAlgo(int px, int py, double r) {
    double x=0,y=r;
    double p = 1-r;

    glBegin(GL_POINTS);

    while(x<y) {
        glVertex2d(px-x, py-y);
        glVertex2d(px-x, py+y);
        glVertex2d(px-y, py-x);
        glVertex2d(px-y, py+x);
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

double degreeToRad(double angle) {
    return angle * 3.141592654/180;
}

vector<double> getHomoCoord(pair<double, double> point) {
    vector<double> val;
    val.push_back(point.first);
    val.push_back(point.second);
    val.push_back(1);
    return val;
}

pair<double, double> getPoint(vector<double> val) {
    return make_pair(val[0], val[1]);
}

vector<double> multiply(vector<vector<double>> a, vector<double> b) {
    vector<double> res;
    for(int i=0;i<a.size();i++) {
        int sum = 0;
        for(int j=0;j<a[0].size();j++) {
            sum += a[i][j]*b[j];
        }
        res.push_back(sum);
    }
    return res;
}

pair<double, double> rotate(double angle, pair<double, double> point) {
    vector<vector<double>> rot_mat, res_mat;
    vector<double> val;

    val.push_back(cos(angle)); val.push_back(-sin(angle)); val.push_back(0); 
    rot_mat.push_back(val); val.clear();
    val.push_back(sin(angle)); val.push_back(cos(angle)); val.push_back(0); 
    rot_mat.push_back(val); val.clear();
    val.push_back(0); val.push_back(0); val.push_back(1); 
    rot_mat.push_back(val); val.clear();  

    return getPoint(multiply(rot_mat, getHomoCoord(point)));
}

void myDisplay() {

    //Display Clock Frame
    glColor3f(1,1,0);
    for(float i=30;i<=35;i+=0.01) {
        MidPointAlgo(0,0,i);   
    }

    pair<double, double> min_hand, hour_hand;

    min_hand = rotate(-0.12*iter_count, make_pair(0,28));
    hour_hand = rotate(-0.12*0.12*iter_count, make_pair(0,20));

    glBegin(GL_LINES);
        glVertex2d(0,0);
        glVertex2d(min_hand.first, min_hand.second);
        
        glVertex2d(0,0);
        glVertex2d(hour_hand.first, hour_hand.second);
    glEnd();

    glFlush();

}

void update() {
    myInit();
    iter_count++;
    return;
}

void myTimer(int i) {
    update();
    glutPostRedisplay();
    myDisplay();

    glutTimerFunc(1, myTimer, 0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
    glutInitWindowSize(WINDWOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Clock");

    myInit();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(0, myTimer, 0);

    glutMainLoop();
    return 0;
}