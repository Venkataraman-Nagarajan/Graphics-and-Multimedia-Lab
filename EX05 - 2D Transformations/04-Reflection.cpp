// To apply the following 2D transformations on objects and to render the final output along with the original object. 

// 4) Reflection with respect to     
//     a) x-axis     
//     b) y-axis     
//     c) origin     
//     d) the line x=y 

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

void myInit();
void myDisplay();

void printAxes();
ld multiply(vector<ld> a, vector<ll> b);
vector<ld> multiply(vector<vector<ld>> a, vector<ll> b);

enum ReflectionType {X_AXIS, Y_AXIS, ORIGIN, X_EQUALS_Y_LINE};

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<ld> reflect(vector<ll> &point_matrix, ReflectionType type=ORIGIN);
pair<ld,ld> getPoint(vector<ld> point_matrix);
void reflectShape();


int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Reflection");             
    glutDisplayFunc(myDisplay);              
    myInit();             
    glutMainLoop();             
    return 1;         
} 

void myInit() {     
    glClearColor(1.0,1.0,1.0,0.0);     
    glColor3f(0.0f,0.0f,0.0f);     
    glPointSize(2.0);     
    glMatrixMode(GL_PROJECTION);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );     
    glLoadIdentity();     
    gluOrtho2D(X_MIN,X_MAX,Y_MIN,Y_MAX); 
}     

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    printAxes();
    reflectShape();

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

void reflectShape() {
    
    vector<pair<ll,ll>> shape; 
    
    //Plot original shape;
    
    shape = {{20,100}, {40,80}, {60,100}, {40,120}};

    glBegin(GL_POLYGON);
    glColor4f(0.0f,1.0f,0.7f,1.0f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Reflect shape along x-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> reflected_point = getPoint(reflect(point_matrix, X_AXIS));

        glVertex2d(reflected_point.X,reflected_point.Y);        
    }

    glEnd();

    //Reflect shape along y-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> reflected_point = getPoint(reflect(point_matrix, Y_AXIS));

        glVertex2d(reflected_point.X,reflected_point.Y);        
    }

    glEnd();

    //Reflect shape along origin;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> reflected_point = getPoint(reflect(point_matrix, ORIGIN));

        glVertex2d(reflected_point.X,reflected_point.Y);
    }

    glEnd();

    //Reflect shape along x=y line;

    glBegin(GL_LINES);
    glColor4f(0.0f,1.0f,0.0f,0.4f);

    glVertex2d(min(X_MIN,Y_MIN),min(X_MIN,Y_MIN));
    glVertex2d(max(X_MAX,Y_MAX),max(X_MAX,Y_MAX));

    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> reflected_point = getPoint(reflect(point_matrix, X_EQUALS_Y_LINE));

        glVertex2d(reflected_point.X,reflected_point.Y);
    }

    glEnd();
}

pair<ld,ld> getPoint(vector<ld> point_matrix) {
    ll h = point_matrix[2];
    ld x = point_matrix[0];
    ld y = point_matrix[1];

    return {x/h,y/h};
}

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h) {
    vector<ll> point_matrix;
    point_matrix.push_back(h*point.first);
    point_matrix.push_back(h*point.second);
    point_matrix.push_back(h);
    return point_matrix;
}

vector<ld> reflect(vector<ll> &point_matrix, ReflectionType type) {
    
    vector<vector<ld>> reflection_matrix;

    switch (type)
    {
        case X_AXIS:
            reflection_matrix = {
                                    {1,0,0}, 
                                    {0,-1,0}, 
                                    {0,0,1}
                                };
            break;
        
        case Y_AXIS:
            reflection_matrix = {
                                    {-1,0,0},
                                    {0,1,0},
                                    {0,0,1}
                                };
            break;
        
        case ORIGIN:
            reflection_matrix = {  
                                    {-1,0,0},
                                    {0,-1,0},
                                    {0,0,1}
                                };
            break;
        
        case X_EQUALS_Y_LINE:
            reflection_matrix = {
                                    {0,1,0},
                                    {1,0,0},
                                    {0,0,1}
                                };                        
            break;
        
        default:
            reflection_matrix = {
                                    {1,0,0},
                                    {0,1,0},
                                    {0,0,1}
                                };
            break;
    }

    return multiply(reflection_matrix, point_matrix);
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