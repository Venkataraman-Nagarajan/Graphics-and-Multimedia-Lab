// To apply the following 2D transformations on objects and to render the final output along with the original object. 

// 2) Rotation     
//     a) about origin     
//     b) with respect to a fixed point (xr,yr)

#include<bits/stdc++.h>
#include<GL/glut.h> 

using namespace std;
using ld = long double;
using ll = long long;

#define X       first
#define Y       second

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

const int X_MIN = -300;
const int X_MAX = 300;
const int Y_MIN = -300;
const int Y_MAX = 300;

const ld PADDING = 0;
const ld STEP = 10;
const ld SCALE = 1;
const ld PI = 3.14159265358979323846264338327950288419716939937510582;

void myInit();
void myDisplay();

void printAxes();
ld getRadian(ld degree);
ld multiply(vector<ld> a, vector<ll> b);
vector<ld> multiply(vector<vector<ld>> a, vector<ll> b);

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<ld> rotate(vector<ll> &point_matrix, ld angle=0, pair<ll,ll> pivot=make_pair(0,0));
pair<ld,ld> getPoint(vector<ld> point_matrix);
void rotateShape();


int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Rotation");             
    glutDisplayFunc(myDisplay);              
    myInit();             
    glutMainLoop();             
    return 1;         
} 

void myInit() {     
    glClearColor(1.0,1.0,1.0,0.0);     
    glColor3f(0.0f,0.0f,0.0f);     
    glPointSize(5.0);     
    glMatrixMode(GL_PROJECTION);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );     
    glLoadIdentity();     
    gluOrtho2D(X_MIN,X_MAX,Y_MIN,Y_MAX); 
}     

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    printAxes();
    rotateShape();

    glFlush();         
}

void printAxes() {
    glBegin(GL_LINES);
    
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2d(X_MIN,0);
    glVertex2d(X_MAX,0);
    
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2d(0,Y_MIN);
    glVertex2d(0,Y_MAX);

    for(ll i=X_MIN;i<X_MAX;i+=STEP) {
        glVertex2d(i,-0.3*STEP);
        glVertex2d(i,0.3*STEP);
    }

    for(ll i=Y_MIN;i<Y_MAX;i+=STEP) {
        glVertex2d(-0.3*STEP,i);
        glVertex2d(0.3*STEP,i);
    }

    glEnd();
}

void rotateShape() {
    //Plot original shape;
    
    vector<pair<ll,ll>> shape = {{20,20}, {60,20}, {40,60}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,1.0f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Rotate shape with respect to origin;

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> rotated_point = getPoint(rotate(point_matrix,90));

        glVertex2d(rotated_point.X,rotated_point.Y);        
    }

    glEnd();

    //Rotate shape with respect to a fixed point;

    pair<ll,ll> pivot = {40,70};

    glBegin(GL_POINTS);
    glColor4f(0.8f,0.0f,0.5f,0.9f);
    glVertex2d(pivot.X, pivot.Y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> rotated_point = getPoint(rotate(point_matrix,180,pivot));

        glVertex2d(rotated_point.X,rotated_point.Y);        
    }

    glEnd();
}

pair<ld,ld> getPoint(vector<ld> point_matrix) {
    ll h = point_matrix[2];
    ld x = point_matrix[0];
    ld y = point_matrix[1];

    return {x/h,y/h};
}

ld getRadian(ld degree) {
    return degree*PI/180;
}

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h) {
    vector<ll> point_matrix;
    point_matrix.push_back(h*point.first);
    point_matrix.push_back(h*point.second);
    point_matrix.push_back(h);
    return point_matrix;
}

vector<ld> rotate(vector<ll> &point_matrix, ld angle, pair<ll,ll> pivot) {
    angle = getRadian(angle);
    ll xr = pivot.X;
    ll yr = pivot.Y;

    vector<vector<ld>> rotate_matrix = {   
                                {cos(angle), -sin(angle), xr*(1-cos(angle) + yr*sin(angle))}, 
                                {sin(angle),  cos(angle), yr*(1-cos(angle) - xr*sin(angle))},
                                {0         ,  0         ,1}
                            };
    return multiply(rotate_matrix, point_matrix);
}

vector<ld> multiply(vector<vector<ld>> a, vector<ll> b) {
    vector<ld> result;
    for(int i=0;i<a.size();i++) {
        ll temp = multiply(a[i],b);
        result.push_back(temp);
    }
    return result;
}

ld multiply(vector<ld> a, vector<ll> b) {
    ld result=0;
    for(int i=0;i<a.size();i++) {
        result+=(a[i]*b[i]);
    }
    return result;
}