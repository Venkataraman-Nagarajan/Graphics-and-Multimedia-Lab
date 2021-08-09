// To draw any object using line and circle drawing algorithms.

#include<bits/stdc++.h>
#include<GL/glut.h> 

using namespace std;
using ld = long double;
using ll = long long;

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 850;

void myInit();
void myDisplay();

void drawOmnitrix();
void printDDALine(ld x1, ld y1, ld x2, ld y2);
void printMidpointCircle(ll x, ll y, ll r);

ld radian(ll x);

const ld PADDING = 0;
const ld STEP = 1;
const ld SCALE = 1;
const ld PI = 3.141592653589793238;

int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("Omnitrix Scribble");             
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
    
    drawOmnitrix();
    
    glFlush();         
}

ld radian(ll x) {
    return x * PI / 180.0;
}

void drawOmnitrix() {
    //Draw circle frame
    glColor3f(0.184f, 0.310f, 0.310f);     
    for(ll radius = 150; radius >= 135; radius --)
        printMidpointCircle(0, 0, radius);
    
    //Print Omnitrix "X" Frame
    glColor3f(0.000f, 1.000f, 0.000f);
    for(ll point = 30; point >= 20; point -- ) {
        ll x = point;
        ll y = point+65;
        printDDALine(x, 0, y,y);
        printDDALine(x, 0, y, -y);  


        printDDALine(-x, 0, -y, y);
        printDDALine(-x, 0, -y, -y);
    }
    
    //Print Omnitrix Handle Frame
    glColor3f(0.294f, 0.000f, 0.510f);
    for(ld angle = 145; angle >= 35; angle-=0.1) {
        ll x = 150*cos(radian(angle));
        ll y = 150*sin(radian(angle));

        printDDALine(x, y, x, y + rand()%10+100);
        printDDALine(x, -y, x, -(y + rand()%10+100));
    }
 }

void printDDALine(ld x1, ld y1, ld x2, ld y2) {
    
    glBegin(GL_POINTS);
   
    ld pad = PADDING, scale = SCALE;
    
    x1 = x1*scale + pad; 
    x2 = x2*scale + pad; 
    y1 = y1*scale + pad; 
    y2 = y2*scale + pad;

    ld dx, dy, steps;
    ld xInc, yInc, x, y;

    dx = (x2-x1);
    dy = (y2-y1);

    if(abs(dx) > abs(dy))   steps = abs(dx);
    else                    steps = abs(dy);

    xInc = dx/steps;
    yInc = dy/steps;

    x = x1; y = y1;
    glVertex2d(x, y);

    for(long i=1;i<=steps;i++) {
        x += xInc;
        y += yInc;

        glVertex2d(x, y);
    }

    glEnd();
}


void printMidpointCircle(ll x0, ll y0, ll r) {
    
    glBegin(GL_POINTS);
   
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

    glEnd();

}
