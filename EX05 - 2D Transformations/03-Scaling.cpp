// To apply the following 2D transformations on objects and to render the final output along with the original object. 

// 3) Scaling with respect to     
//      a) origin - Uniform Vs Differential Scaling     
//      b) fixed point (xf,yf)


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

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<ld> scale(vector<ll> &point_matrix, ld sx=1, ld sy=2, pair<ll,ll> pivot=make_pair(0,0));
pair<ld,ld> getPoint(vector<ld> point_matrix);
void scaleShape();


int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Scaling");             
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
    scaleShape();

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

void scaleShape() {
    
    vector<pair<ll,ll>> shape; 
    
    //Plot original shape;
    
    shape = {{20,40}, {60,40}, {40,80}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,1.0f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Scale shape w.r.t. origin - Uniform Scaling;

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> scaled_point = getPoint(scale(point_matrix, 2, 2));

        glVertex2d(scaled_point.X,scaled_point.Y);        
    }

    glEnd();




    //Plot original shape;
    
    shape = {{-20,40}, {-60,40}, {-40,80}};

    glBegin(GL_POLYGON);
    glColor4f(0.0f,1.0f,0.7f,1.0f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Scale shape w.r.t. origin - Differential Scaling;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,1.0f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> scaled_point = getPoint(scale(point_matrix, 0.5, 2));

        glVertex2d(scaled_point.X,scaled_point.Y);        
    }

    glEnd();




    //Plot original shape;
    
    shape = {{20,-40}, {60,-40}, {40,-80}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,1.0f,0.0f,0.7f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Scale shape w.r.t. fixed point - Uniform Scaling;

    pair<ll,ll> pivot = {40, -60};

    glBegin(GL_POINTS);
    glColor4f(0.0f,0.0f,1.0f,0.9f);
    glVertex2d(pivot.X, pivot.Y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.7f,1.0f,0.0f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> scaled_point = getPoint(scale(point_matrix, 1.5, 1.5, pivot));

        glVertex2d(scaled_point.X,scaled_point.Y);        
    }

    glEnd();




    //Plot original shape;
    
    shape = {{-20,-40}, {-60,-40}, {-40,-80}};

    glBegin(GL_POLYGON);
    glColor4f(1.0f,0.7f,0.0f,0.7f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Scale shape w.r.t. fixed point - Differential Scaling;

    pivot = {-40, -60};

    glBegin(GL_POINTS);
    glColor4f(1.0f,0.0f,0.0f,0.9f);
    glVertex2d(pivot.X, pivot.Y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(1.0f,0.7f,0.0f,0.5f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> scaled_point = getPoint(scale(point_matrix, 0.5, 1.5, pivot));

        glVertex2d(scaled_point.X,scaled_point.Y);        
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

vector<ld> scale(vector<ll> &point_matrix, ld sx, ld sy, pair<ll,ll> pivot) {
    
    ll xf = pivot.X;
    ll yf = pivot.Y;

    vector<vector<ld>> scale_matrix = {   
                                {sx, 0, xf*(1-sx)}, 
                                {0, sy, yf*(1-sy)},
                                {0,  0, 1}
                            };
    return multiply(scale_matrix,point_matrix);
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