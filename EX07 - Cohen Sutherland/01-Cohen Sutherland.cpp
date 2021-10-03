// Apply Cohen Sutherland line clipping on a line (x1,y1) (x2,y2) with respect to a clipping window 
// (XWmin,YWmin) (XWmax,YWmax). 

// After clipping with respect to an edge, display the line segment with the calculated intermediate 
// intersection points and the vertex list. 

// Input: The clipping window co-ordinates and the line endpoints 

// Note: The output should show the clipping window and the line to be clipped in different colors. 

// You can show the intermediate steps using time delay. 

#include "__init__.h"
#include <unistd.h>
const ld PADDING = 0;
const ld STEP = 10;
const ld SCALE = 1;
const ld PI = 3.14159265358979323846264338327950288419716939937510582;

void myInit();
void myDisplay();

void LineCuttingAlgorithm();
Line getLineInput();
Window getWindowInput();

int main(int argc,char* argv[]) {             
    glutInit(&argc,argv);             
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);             
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);             
    glutCreateWindow("Cohen Sutherland");             
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
    
    LineCuttingAlgorithm();

    glFlush();         
}

Window getWindowInput() {
    ld X_MAX, X_MIN, Y_MAX, Y_MIN;

    cout << "Enter Window Limits: \n";
    cout << "\t X_MIN : "; cin >> X_MIN;
    cout << "\t X_MAX : "; cin >> X_MAX;
    cout << "\t Y_MIN : "; cin >> Y_MIN;
    cout << "\t Y_MAX : "; cin >> Y_MAX;

    return Window(X_MIN, X_MAX, Y_MIN, Y_MAX);
}

Line getLineInput() {
    pld a,b;

    cout << "\nEnter End-points of the line: \n";
    cout << "\t A(x,y) : "; cin >> a.X >> a.Y;
    cout << "\t B(x,y) : "; cin >> b.X >> b.Y;

    return Line(a, b);
}

void LineCuttingAlgorithm() {
    cout << "\t\t Cohen Sutherland Line Cutting \n\n";
    
    Window window = getWindowInput();
    Line line = getLineInput();

    // Handle corner cases of infinite loop
    ll local_counter = 0;

    do {
        window.displayFull(1,1,1);
        line.display(0,0,1);
        
        CohenVector c = CohenVector();
        CohenVector d = CohenVector();
        
        ll vec1 = c.calcCohenValue(line.A, window);
        ll vec2 = d.calcCohenValue(line.B, window);
        
        if(c.trivialAccept(d)) {
            window.displayWindow(1,0,0);
            line.display(0,1,0);
            break;
        }

        
        if(c.trivialReject(d)) break;

        
        line = findIntersection(line, window);
        
        
        local_counter ++;
    } while(local_counter <= 5);

}   
