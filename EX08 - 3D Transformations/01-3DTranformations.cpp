// Perform the following basic 3D Transformations on any 3D Object. 
//      1) Translation 
//      2) Rotation 
//      3) Scaling 

// Use only homogeneous coordinate representation and matrix multiplication to 
// perform transformations. 

// Set the camera to any position on the 3D space. Have (0,0,0) at the center of the 
// screen. Draw X , Y and Z axis.

#include <GL/glut.h>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
using ld = long double;
using ll = long long;

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

const int X_MIN = -600;
const int X_MAX = 600;
const int Y_MIN = -600;
const int Y_MAX = 600;
const int Z_MIN = -600;
const int Z_MAX = 600;

const ld PADDING = 0;
const ld STEP = 10;
const ld SCALE = 1;
const ld PI = 3.14159265358979323846264338327950288419716939937510582;

struct Point {
    ld X, Y, Z;
    Point(ld x, ld y, ld z) : X(x), Y(y), Z(z) {}
    Point() : X(0), Y(0), Z(0) {}
};

struct Face {
    vector<Point> points;
    Face(vector<Point> &points) : points(points) {}
};

struct Object {
    vector<Face> faces;
    Object(vector<Face> &faces) : faces(faces) {}
};

enum RotationType {X_AXIS, Y_AXIS, Z_AXIS, INVALID};

void init();
void disp();
void display();

void printAxes();
ld getRadian(ld degree);
ld multiply(vector<ld> a, vector<ll> b);
vector<ld> multiply(vector<vector<ld>> &a, vector<ll> b);
vector<vector<ld>> multiply(vector<vector<ld>> &a, vector<vector<ld>> &b);

Point getPoint(vector<ld> point_matrix);
vector<ll> getHomogeneousPointCoords(Point point, ll h=1);
vector<vector<ld>> getTransformMatrix();

vector<vector<ld>> translate(ld tx=0, ld ty=0, ld tz=0);
vector<vector<ld>> scale(ld sx=1, ld sy=1, ld sz=1, Point pivot=Point(0,0,0));
vector<vector<ld>> rotate(ld angle=0.0, RotationType type=Z_AXIS);

void transformShape();

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D - Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );     
    glLoadIdentity();     
    glOrtho(X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX);
    glEnable(GL_DEPTH_TEST);
}

//Transformations - Built-in functions- only for reference
void disp() {
    glRotatef(50, 1, 0, 0);
    glRotatef(50, 0, 1, 0);
    glRotatef(50, 0, 0, 1);
}

bool twoEqual(Point a, Point b) {
    return (a.X == b.X && a.Y == b.Y ) || (a.X == b.X && a.Z == b.Z) || (a.Y == b.Y && a.Z == b.Z);
}

Face orderSquare(Face face, string commonPlane="X") {
    vector<Point> points = face.points;
    vector<Point> newface;
    if(points.size() != 4) return face;
    
    Point current = points[0];
    newface.push_back(current);
    ll cou = 0;

    points.erase(points.begin());

    while(cou < 4) {
        for(auto point: points) {
            if(twoEqual(point, current)) {
                current = point;
                newface.push_back(current);
                points.erase(
                    remove_if(points.begin(), points.end(), [&](Point const & point) {
                        return point.X == current.X && point.Y == current.Y && point.Z == current.Z;
                    }), points.end());
                break;
            }
        }
        cou++;
    }

    return Face(newface);
}
// Returns a cube
Object getObject() {
    vector<Point> front, back, left, right, top, bottom;
    vector<Face> faces;

    for(ll x=-100; x<=100; x+=200) {
        for(ll y=-100; y<=100; y+=200) {
            for(ll z=-100; z<=100; z+=200) {
                if(z > 0) {
                    front.push_back(Point(x, y, z));
                } else {
                    back.push_back(Point(x, y, z));
                }

                if(x > 0) {
                    right.push_back(Point(x, y, z));
                } else {
                    left.push_back(Point(x, y, z));
                }

                if(y > 0) {
                    top.push_back(Point(x, y, z));
                } else {
                    bottom.push_back(Point(x, y, z));
                }
            }
        }
    }

    faces.push_back(orderSquare(Face(front), "Z"));
    faces.push_back(orderSquare(Face(back), "Z"));
    faces.push_back(orderSquare(Face(left), "X"));
    faces.push_back(orderSquare(Face(right), "X"));
    faces.push_back(orderSquare(Face(top), "Y"));
    faces.push_back(orderSquare(Face(bottom), "Y"));
    
    return Object(faces);
}

vector<vector<ld>> getTransformMatrix() {
    ll no_of_transformations;
    string type;

    vector<vector<ld>> transform_matrix = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    cout << "\n\t\t Composite Transformations \n\n";
    cout << "Input Format: \n";
    cout << "\t'T' tx ty tz (Translation by (tx,ty,tz))\n";
    cout << "\t'Ro' angle type['X'/'Y'/'Z'] (Rotation by angle about x-axis,y-axis,z-axis)\n";
    cout << "\t'Sc' sx sy sz fx fy fz (Scale by sx & sy with ref to (fx,fy,fz))\n";
    
    cout << "\nSample Input: \n";
    cout << "\t3\n";
    cout << "\tT 4.5 10 20\n";
    cout << "\tRo 45 X\n";
    cout << "\tSc 3 2 0.5 0 0 0\n";

    cout << "\nYour Input: \n";
    cin >> no_of_transformations;

    for(ll i=0;i<no_of_transformations;i++) {
        cin>>type;
        if(type=="T") {
            ld tx,ty,tz;
            cin>>tx>>ty>>tz;
            
            vector<vector<ld>> translation_matrix = translate(tx,ty,tz);
            
            transform_matrix = multiply(translation_matrix, transform_matrix);
        } else if(type=="Ro") {
            ld angle;
            string type;
            cin>>angle>>type;
            
            vector<vector<ld>> rotation_matrix; 
            
            if(type=="X")       rotation_matrix = rotate(angle, X_AXIS);
            else if(type=="Y")  rotation_matrix = rotate(angle, Y_AXIS);
            else if(type=="Z")  rotation_matrix = rotate(angle, Z_AXIS);
            else                rotation_matrix = rotate(angle, INVALID);
            
            transform_matrix = multiply(rotation_matrix, transform_matrix);
        } else if(type=="Sc") {
            ld sx,sy,sz,fx,fy,fz;
            cin>>sx>>sy>>sz>>fx>>fy>>fz;
            
            vector<vector<ld>> scaling_matrix = scale(sx,sy,sz,Point(fx,fy,fz));
            transform_matrix = multiply(scaling_matrix, transform_matrix);
        }
    }

    cout << "\nOutput is displayed on the window\n\n";

    return transform_matrix;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Object obj = getObject();
    disp();
    printAxes();
    
    // Print Original Object

    ll cou = 0;
    for(Face face : obj.faces) {
        
        if(cou < 6) glColor3f(0.0, 0.0, 1.0);
        if(cou < 4) glColor3f(0.0, 1.0, 0.0);
        if(cou < 2) glColor3f(1.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        for(Point point : face.points) {
            glVertex3f(point.X, point.Y, point.Z);
        }
        glEnd();
        cou++;
    }

    vector<vector<ld>> transform_matrix = getTransformMatrix();

    // Print Transformed Object

    cou = 0;
    for(Face face : obj.faces) {

        if(cou < 6) glColor4f(0.0, 0.0, 1.0, 0.5);
        if(cou < 4) glColor4f(0.0, 1.0, 0.0, 0.5);
        if(cou < 2) glColor4f(1.0, 0.0, 0.0, 0.5);

        glBegin(GL_QUADS);
        for(Point point : face.points) {
            Point transformed_point = getPoint(multiply(transform_matrix, getHomogeneousPointCoords(point)));
            glVertex3f(transformed_point.X, transformed_point.Y, transformed_point.Z);
        }
        glEnd();
        cou++;
    }

    glFlush();
}

void printAxes() {
    glBegin(GL_LINES);
    
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3d(2*X_MIN,0,0);
    glVertex3d(2*X_MAX,0,0);
    
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3d(0,2*Y_MIN,0);
    glVertex3d(0,2*Y_MAX,0);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3d(0,0,2*Z_MIN);
    glVertex3d(0,0,2*Z_MAX);

    glEnd();
}

Point getPoint(vector<ld> point_matrix) {
    ll h = point_matrix[3];
    ld x = point_matrix[0];
    ld y = point_matrix[1];
    ld z = point_matrix[2];

    return {x/h,y/h,z/h};
}

vector<ll> getHomogeneousPointCoords(Point point, ll h) {
    vector<ll> point_matrix;
    point_matrix.push_back(h*point.X);
    point_matrix.push_back(h*point.Y);
    point_matrix.push_back(h*point.Z);
    point_matrix.push_back(h);
    return point_matrix;
}

ld getRadian(ld degree) {
    return degree*PI/180;
}

vector<vector<ld>> translate(ld tx, ld ty, ld tz) {
    vector<vector<ld>> translate_matrix = {
                                            {1,0,0,tx},
                                            {0,1,0,ty},
                                            {0,0,1,tz},
                                            {0,0,0,1}
                                        };
    return translate_matrix;
}

vector<vector<ld>> scale(ld sx, ld sy, ld sz, Point pivot) {
    
    ll xf = pivot.X;
    ll yf = pivot.Y;
    ll zf = pivot.Z;

    vector<vector<ld>> scale_matrix = {   
                                {sx, 0, 0, xf*(1-sx)}, 
                                {0, sy, 0, yf*(1-sy)},
                                {0,  0, sz, zf*(1-sz)},
                                {0,  0,  0, 1}
                            };
    return scale_matrix;
}

vector<vector<ld>> rotate(ld angle, RotationType type) {
    angle = getRadian(angle);
    
    vector<vector<ld>> rotate_matrix;
    
    switch(type) {
        case X_AXIS:
            rotate_matrix = {
                                {1, 0, 0, 0},
                                {0, cos(angle), -sin(angle), 0},
                                {0, sin(angle), cos(angle), 0},
                                {0, 0, 0, 1}
                            };  
            break;

        case Y_AXIS:
            rotate_matrix = {
                                {cos(angle), 0, sin(angle), 0},
                                {0, 1, 0, 0},
                                {-sin(angle), 0, cos(angle), 0},
                                {0, 0, 0, 1}
                            };
            break;

        case Z_AXIS:
            rotate_matrix = {
                                {cos(angle), -sin(angle), 0, 0},
                                {sin(angle), cos(angle), 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}
                            };
            break;
        default:
            rotate_matrix = {
                                {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,0,1}
                            };
            break;
            
    }

    return rotate_matrix;
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
