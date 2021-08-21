// To apply the following 2D transformations on objects and to render the final output along with the original object. 

// 5) Shearing     
//     a) x-direction shear     
//     b) y-direction shear

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

enum ShearType {X_SHEAR, Y_SHEAR};

vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<ld> shear(vector<ll> &point_matrix, ShearType type=X_SHEAR, ld sh=1, ld refLine=0);
pair<ld,ld> getPoint(vector<ld> point_matrix);
void shearShape();


int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Shearing");             
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
    shearShape();

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

void shearShape() {
    
    vector<pair<ll,ll>> shape; 
    
    //QUAD - 1

    //Plot original shape;
    
    shape = {{0,0}, {40,0}, {40,40}, {0,40}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.5f,1.0f,0.6f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Shear the shape w.r.t x-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, 3));

        glVertex2d(sheared_point.X,sheared_point.Y);        
    }

    glEnd();

    //Shear the shape w.r.t x-axis with y_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.1f,0.7f,0.4f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, 3, -30));

        glVertex2d(sheared_point.X,sheared_point.Y);        
    }

    glEnd();

    //Shear the shape w.r.t y-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.502f,0.0f,0.502f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, 3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis with x_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.502f,0.0f,0.502f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, 3, -30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //QUAD - 2

    //Plot original shape;

    shape = {{0,0}, {-40,0}, {-40,40}, {0,40}};

    glBegin(GL_POLYGON);
    glColor4f(0.486f,0.988f,0.000f,0.4f);

    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.596f,0.984f,0.596f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, -3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis with y_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.596f,0.984f,0.596f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, -3, -30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.678f,1.0f,0.184f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, -3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis with x_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.678f,1.0f,0.184f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, -3, 30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //QUAD - 3

    //Plot original shape;

    shape = {{0,0}, {-40,0}, {-40,-40}, {0,-40}};

    glBegin(GL_POLYGON);
    glColor4f(0.824f,0.412f,0.118f,0.6f);

    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.722f,0.525f,0.043f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, 3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis with y_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.722f,0.525f,0.043f,0.7f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, 3, 30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.627f,0.322f,0.176f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, 3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis with x_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.627f,0.322f,0.176f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, 3, 30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //QUAD - 4

    //Plot original shape;

    shape = {{0,0}, {40,0}, {40,-40}, {0,-40}};

    glBegin(GL_POLYGON);
    glColor4f(0.498f,1.0f,0.831f,0.6f);

    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.545f,0.545f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, -3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t x-axis with y_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.0f,0.545f,0.545f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, X_SHEAR, -3, 30));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis;

    glBegin(GL_POLYGON);
    glColor4f(0.282f,0.820f,0.800f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, -3));

        glVertex2d(sheared_point.X,sheared_point.Y);
    }

    glEnd();

    //Shear the shape w.r.t y-axis with x_ref;

    glBegin(GL_POLYGON);
    glColor4f(0.282f,0.820f,0.800f,0.6f);

    for(auto point : shape) {
        vector<ll> point_matrix = getHomogeneousPointCoords(point);
        pair<ld,ld> sheared_point = getPoint(shear(point_matrix, Y_SHEAR, -3, -30));

        glVertex2d(sheared_point.X,sheared_point.Y);
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

vector<ld> shear(vector<ll> &point_matrix, ShearType type, ld sh, ld refLine) {
    
    vector<vector<ld>> shear_matrix;

    switch (type)
    {
        case X_SHEAR:
            shear_matrix = {
                                    {1,sh,-sh*refLine}, 
                                    {0,1,0}, 
                                    {0,0,1}
                                };
            break;
        
        case Y_SHEAR:
            shear_matrix = {
                                    {1,0,0},
                                    {sh,1,-sh*refLine},
                                    {0,0,1}
                                };
            break;
        
        default:
            shear_matrix = {
                                    {1,0,0},
                                    {0,1,0},
                                    {0,0,1}
                                };
            break;
    }

    return multiply(shear_matrix, point_matrix);
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