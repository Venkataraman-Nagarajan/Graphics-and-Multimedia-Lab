// To compute the composite transformation matrix for any 2 transformations given as input by the user and applying it on the object. 

// The transformation can be any combination of the following.  
//     1) Translation 
//     2) Rotation 
//     3) Scaling  
//     4) Reflection  
//     5) Shearing 

// Display the original and the transformed object. 

// Calculate the final transformation matrix by multiplying the two individual transformation 
// matrices and then apply it to the object. 

// Note: Use Homogeneous coordinate representations and matrix multiplication to perform 
// transformations. Divide the output window into four quadrants. (Use LINES primitive to draw x 
// and y axis) 

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

enum ReflectionType {X_AXIS, Y_AXIS, ORIGIN, X_EQUALS_Y_LINE, INVALID_};
enum ShearType {X_SHEAR, Y_SHEAR, INVALID};

void myInit();
void myDisplay();

void printAxes();
ld getRadian(ld degree);
ld multiply(vector<ld> a, vector<ll> b);
vector<ld> multiply(vector<vector<ld>> &a, vector<ll> b);
vector<vector<ld>> multiply(vector<vector<ld>> &a, vector<vector<ld>> &b);

pair<ld,ld> getPoint(vector<ld> point_matrix);
vector<ll> getHomogeneousPointCoords(pair<ll,ll> point, ll h=1);
vector<vector<ld>> getTransformMatrix();

vector<vector<ld>> translate(ld tx=0, ld ty=0);
vector<vector<ld>> rotate(ld angle=0, pair<ll,ll> pivot=make_pair(0,0));
vector<vector<ld>> scale(ld sx=1, ld sy=2, pair<ll,ll> pivot=make_pair(0,0));
vector<vector<ld>> reflect(ReflectionType type=ORIGIN);
vector<vector<ld>> shear(ShearType type=X_SHEAR, ld sh=1, ld refLine=0);

void transformShape();

int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("2D - Composite transforms");             
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
    transformShape();

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

vector<vector<ld>> getTransformMatrix() {
    ll no_of_transformations;
    string type;

    vector<vector<ld>> transform_matrix = {{1,0,0},{0,1,0},{0,0,1}};

    cout << "\n\t\t Composite Transformations \n\n";
    cout << "Input Format: \n";
    cout << "\t'T' tx ty (Translation by (tx,ty))\n";
    cout << "\t'Ro' angle rx ry (Rotation by angle with ref to (rx,ry))\n";
    cout << "\t'Sc' sx sy fx fy (Scale by sx & sy with ref to (fx,fy))\n";
    cout << "\t'Re' type['X'/'Y'/'O'/'XY'] (Reflection about x-axis, y-axis, origin or x=y line)\n";   
    cout << "\t'Sh' type['X'/'Y'] sh refline ('type'_Shear by sh with ref to refline)\n";

    cout << "\nSample Input: \n";
    cout << "\t3\n";
    cout << "\tT 4.5 10\n";
    cout << "\tRo 45 0 0\n";
    cout << "\tRe XY\n";

    cout << "\nYour Input: \n";
    cin >> no_of_transformations;

    for(ll i=0;i<no_of_transformations;i++) {
        cin>>type;
        if(type=="T") {
            ld tx,ty;
            cin>>tx>>ty;
            
            vector<vector<ld>> translation_matrix = translate(tx,ty);
            transform_matrix = multiply(translation_matrix, transform_matrix);
        } else if(type=="Ro") {
            ld angle,rx,ry;
            cin>>angle>>rx>>ry;
            
            vector<vector<ld>> rotation_matrix = rotate(angle, make_pair(rx,ry));
            transform_matrix = multiply(rotation_matrix, transform_matrix);
        } else if(type=="Sc") {
            ld sx,sy,fx,fy;
            cin>>sx>>sy>>fx>>fy;
            
            vector<vector<ld>> scaling_matrix = scale(sx,sy,make_pair(fx,fy));
            transform_matrix = multiply(scaling_matrix, transform_matrix);
        } else if(type=="Re") {
            string type;
            vector<vector<ld>> reflection_matrix;
            cin>>type;
            
            if(type=="X")       reflection_matrix = reflect(X_AXIS);
            else if(type=="Y")  reflection_matrix = reflect(Y_AXIS);
            else if(type=="O")  reflection_matrix = reflect(ORIGIN);
            else if(type=="XY") reflection_matrix = reflect(X_EQUALS_Y_LINE);
            else                reflection_matrix = reflect(INVALID_);

            transform_matrix = multiply(reflection_matrix, transform_matrix);
        } else if(type=="Sh") {
            string type;
            ld sh,refLine;
            vector<vector<ld>> shear_matrix;
            cin>>type>>sh>>refLine;
            
            if(type=="X")       shear_matrix = shear(X_SHEAR,sh,refLine);
            else if(type=="Y")  shear_matrix = shear(Y_SHEAR,sh,refLine);
            else                shear_matrix = shear(INVALID,sh,refLine);

            transform_matrix = multiply(shear_matrix, transform_matrix);
        }
    }

    cout << "\nOutput is displayed on the window\n\n";

    return transform_matrix;
}

void transformShape() {
    
    vector<pair<ll,ll>> shape; 
    
    //Plot original shape;
    
    shape = {{20,60}, {60,60}, {60,20}, {20,20}};

    glBegin(GL_POLYGON);
    glColor4f(0.7f,0.0f,1.0f,0.6f);
    
    for(auto point : shape) {
        glVertex2d(point.X,point.Y);
    }
    
    glEnd();

    //Plot transformed shape;

    vector<vector<ld>> transform_matrix = getTransformMatrix();

    glBegin(GL_POLYGON);
    glColor4f(0.82f,0.53f,1.0f,1.0f);

    for(auto point : shape) {
        pair<ld,ld> transformed_point = getPoint(multiply(transform_matrix, getHomogeneousPointCoords(point)));
        glVertex2d(transformed_point.X,transformed_point.Y);
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

ld getRadian(ld degree) {
    return degree*PI/180;
}

vector<vector<ld>> translate(ld tx, ld ty) {
    vector<vector<ld>> translate_matrix = {
                                            {1,0,tx},
                                            {0,1,ty},
                                            {0,0,1}
                                        };
    return translate_matrix;
}

vector<vector<ld>> scale(ld sx, ld sy, pair<ll,ll> pivot) {
    
    ll xf = pivot.X;
    ll yf = pivot.Y;

    vector<vector<ld>> scale_matrix = {   
                                {sx, 0, xf*(1-sx)}, 
                                {0, sy, yf*(1-sy)},
                                {0,  0, 1}
                            };
    return scale_matrix;
}

vector<vector<ld>> rotate(ld angle, pair<ll,ll> pivot) {
    angle = getRadian(angle);
    ll xr = pivot.X;
    ll yr = pivot.Y;

    vector<vector<ld>> rotate_matrix = {   
                                {cos(angle), -sin(angle), xr*(1-cos(angle) + yr*sin(angle))}, 
                                {sin(angle),  cos(angle), yr*(1-cos(angle) - xr*sin(angle))},
                                {0         ,  0         ,1}
                            };
    return rotate_matrix;
}

vector<vector<ld>> reflect(ReflectionType type) {
    
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

    return reflection_matrix;
}

vector<vector<ld>> shear(ShearType type, ld sh, ld refLine) {
    
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

    return shear_matrix;
}

vector<vector<ld>> multiply(vector<vector<ld>> &a, vector<vector<ld>> &b) {
    vector<vector<ld>> result;
    for(int i=0; i<a.size(); i++) {
        vector<ld> row;
        for(int j=0; j<b[0].size(); j++) {
            ld sum = 0;
            for(int k=0; k<a[0].size(); k++) {
                sum += a[i][k]*b[k][j];
            }   
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}

vector<ld> multiply(vector<vector<ld>> &a, vector<ll> b) {
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