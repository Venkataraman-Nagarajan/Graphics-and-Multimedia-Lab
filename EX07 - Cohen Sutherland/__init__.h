#include<bits/stdc++.h>
#include<GL/glut.h> 

using namespace std;
using ld = long double;
using ll = long long;

#define X       first
#define Y       second

typedef pair<ld,ld> pld;

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

const int X_MIN = -300;
const int X_MAX = 300;
const int Y_MIN = -300;
const int Y_MAX = 300;

enum pos {LEFT, RIGHT, BOTTOM, TOP};

struct Window {
    ld X_MIN, X_MAX, Y_MIN, Y_MAX;

    Window(): X_MAX(::X_MAX), X_MIN(::X_MIN), Y_MAX(::Y_MAX), Y_MIN(::Y_MIN) {}
    Window(ld X_MIN, ld X_MAX, ld Y_MIN, ld Y_MAX): X_MAX(X_MAX), X_MIN(X_MIN), Y_MAX(Y_MAX), Y_MIN(Y_MIN) {}
    
    void displayFull(ld r = 1.0, ld g = 0.0, ld b = 0.0) {
        glColor3f(r,g,b);
        glBegin(GL_LINES);
            glVertex2d(::X_MIN, Y_MIN);
            glVertex2d(::X_MAX, Y_MIN);

            glVertex2d(::X_MIN, Y_MAX);
            glVertex2d(::X_MAX, Y_MAX);

            glVertex2d(X_MIN, ::Y_MIN);
            glVertex2d(X_MIN, ::Y_MAX);

            glVertex2d(X_MAX, ::Y_MIN);
            glVertex2d(X_MAX, ::Y_MAX);
        glEnd();
    }

    void displayWindow(ld r = 1.0, ld g = 0.0, ld b = 0.0) {
        glColor3f(r,g,b);
        glBegin(GL_LINE_LOOP);
            glVertex2d(X_MIN, Y_MIN);
            glVertex2d(X_MIN, Y_MAX);
            glVertex2d(X_MAX, Y_MAX);
            glVertex2d(X_MAX, Y_MIN);
        glEnd();
    }

};

struct CohenVector {
    ll vector;
    ll TOP, BOTTOM, RIGHT, LEFT;
    
    CohenVector(): TOP(8), BOTTOM(4), RIGHT(2), LEFT(1), vector(0) {};

    ll calcCohenValue(pld point, Window window) {
        vector = 0;
        
        vector += (point.Y > window.Y_MAX)*TOP;
        vector += (point.Y < window.Y_MIN)*BOTTOM;
        vector += (point.X > window.X_MAX)*RIGHT;
        vector += (point.X < window.X_MIN)*LEFT;

        return vector;
    }

    bool trivialAccept(CohenVector next) {
        return (vector | next.vector) == 0;
    }

    bool trivialReject(CohenVector next) {
        return (vector & next.vector);
    }
};

struct Line {
    pld A,B;
    ld slope;
    Line(pld A, pld B): A(A), B(B), slope((B.Y - A.Y)/(B.X - A.X)) {}

    void display(ld r = 1.0, ld g = 0.0, ld b = 0.0) {
        glColor3f(r,g,b);
        glBegin(GL_LINES);
            glVertex2d(A.X, A.Y);
            glVertex2d(B.X, B.Y);
        glEnd();
    }
};

pld findNewPosition(pld A, Line l, Window window, pos i) {
    pld c;
    if(i == TOP) {
        c.Y = window.Y_MAX;
        c.X = A.X + 1/l.slope * (c.Y - A.Y);
    } else if(i == BOTTOM) {
        c.Y = window.Y_MIN;
        c.X = A.X + 1/l.slope * (c.Y - A.Y);
    } else if(i == LEFT) {
        c.X = window.X_MIN;
        c.Y = A.Y + l.slope * (c.X - A.X);    
    } else {
        c.X = window.X_MAX;
        c.Y = A.Y + l.slope * (c.X - A.X);
    }

    return c;
}

Line findIntersection(Line line, Window window) {
    CohenVector c = CohenVector();
    c.calcCohenValue(line.A, window);

    for(ll i=0;i<4;i++) {
        if((c.vector & (1<<i))) {
            line.A = findNewPosition(line.A, line, window, (pos)i);
            return line;
        }
    }

    c.calcCohenValue(line.B, window);
    
    for(ll i=0;i<4;i++) {
        if((c.vector & (1<<i))) {
            line.B = findNewPosition(line.B, line, window, (pos)i);
            return line;
        }
    }

    return line;
}

