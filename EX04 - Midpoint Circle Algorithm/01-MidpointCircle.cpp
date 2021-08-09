// To plot points that make up the circle with center (xc,yc) and radius r using Midpoint circle drawing 
// algorithm. Give atleast 2 test cases. 
    
//     Case 1: With center (0,0) 
//     Case 2: With center (xc,yc) 

#include<bits/stdc++.h>
#include<GL/glut.h> 

using namespace std;
using ld = long double;
using ll = long long;

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 850;

void myInit();
void myDisplay();

void printCircles();
void printMidpointCircle(ll x, ll y, ll r);

const ld PADDING = 0;
const ld STEP = 1;
const ld SCALE = 1;

int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("Midpoint Circle Drawing Algorithm");             
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
    glLoadIdentity();     
    gluOrtho2D(-300.0, 300.0, -300.0, 300.0); 
}     

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    printCircles();
    
    glFlush();         
}


void printCircles() {
    glBegin(GL_POINTS);

    // Case 1: With center (0,0)
    glColor3f(1.0f,0.0f,0.0f);     
    printMidpointCircle(0, 0, 50);

    // Case 2: With center (xc,yc)
    glColor3f(0.5f,0.5f,0.0f);     
    printMidpointCircle(175, 25, 100);
    
    glEnd();
}

void printMidpointCircle(ll x0, ll y0, ll r) {
    
    ld pad = PADDING, scale = SCALE;
    
    x0 = x0*scale + pad; 
    y0 = y0*scale + pad; 
    r  = r*scale + pad; 
    
    int x = 0, y = r;
	int p = 1 - r; // Decision parameter
	
    //Plot the centre
    glVertex2d(x0 , y0 );
    
    //Draw the circle
    while (x < y) {
		// Plotting symmetrically in all 8 octants
		glVertex2d(x0 + x, y0 + y);
		glVertex2d(x0 + y, y0 + x);
		glVertex2d(x0 - x, y0 + y);
		glVertex2d(x0 - y, y0 + x);
		glVertex2d(x0 - x, y0 - y);
		glVertex2d(x0 - y, y0 - x);
		glVertex2d(x0 + x, y0 - y);
		glVertex2d(x0 + y, y0 - x);

		if (p < 0) {
			x += 1;
			p += 2 * x + 1;
		}
		else {
			x += 1;
			y -= 1;
			p = p + 2 * x + 1 - 2 * y;
		}
	}

}
