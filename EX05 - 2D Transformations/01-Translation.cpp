// To apply the following 2D transformations on objects and to render the final output along with the original object. 

// 1) Translation

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

void myInit();
void myDisplay();

void printAxes();
ll multiply(vector<ll> a, vector<ll> b);
vector<ll> multiply(vector<vector<ll>> a, vector<ll> b);

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<ll> translate(vector<ll> &point_matrix, ll tx=0, ll ty=0);
pair<ll,ll> getPoint(vector<ll> point_matrix);
void translateShape();

const ld PADDING = 0;
const ld STEP = 10;
const ld SCALE = 1;

int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Translation");             
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
    translateShape();

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

void translateShape() {
    //Plot original shape;
    
    vector<pair<ll,ll>> shape = {{20,20}, {20,50}, {50,50}, {50,20}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,1.0f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Translate shape;

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ll,ll> translated_point = getPoint(translate(point_matrix,50,50));

        glVertex2d(translated_point.X,translated_point.Y);        
    }

    glEnd();
}

pair<ll,ll> getPoint(vector<ll> point_matrix) {
    ll h = point_matrix[2];
    ll x = point_matrix[0];
    ll y = point_matrix[1];

    return {x/h,y/h};
}


vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h) {
    vector<ll> point_matrix;
    point_matrix.push_back(h*point.first);
    point_matrix.push_back(h*point.second);
    point_matrix.push_back(h);
    return point_matrix;
}

vector<ll> translate(vector<ll> &point_matrix, ll tx, ll ty) {
    vector<vector<ll>> translate_matrix = {
                                            {1,0,tx},
                                            {0,1,ty},
                                            {0,0,1}
                                        };
    return multiply(translate_matrix, point_matrix);
}

vector<ll> multiply(vector<vector<ll>> a, vector<ll> b) {
    vector<ll> result;
    for(int i=0;i<a.size();i++) {
        ll temp = multiply(a[i],b);
        result.push_back(temp);
    }
    return result;
}

ll multiply(vector<ll> a, vector<ll> b) {
    ll result=0;
    for(int i=0;i<a.size();i++) {
        result+=(a[i]*b[i]);
    }
    return result;
}