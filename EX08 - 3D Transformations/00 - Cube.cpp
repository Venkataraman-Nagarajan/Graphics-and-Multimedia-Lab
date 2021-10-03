#include <GL/glut.h>
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-600.0, 600.0, -600.0, 600.0, -600.0, 600.0);
    glEnable(GL_DEPTH_TEST);
}
void disp();
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    disp();
    //front
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 100.0, 100.0);
    glVertex3f(100.0, 100.0, 100.0);
    glVertex3f(100.0, -100.0, 100.0);
    glVertex3f(-100.0, -100.0, 100.0);
    glEnd();
    //back
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 100.0, -100.0);
    glVertex3f(100.0, 100.0, -100.0);
    glVertex3f(100.0, -100.0, -100.0);
    glVertex3f(-100.0, -100.0, -100.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    //left
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 100.0, -100.0);
    glVertex3f(-100.0, 100.0, 100.0);
    glVertex3f(-100.0, -100.0, 100.0);
    glVertex3f(-100.0, -100.0, -100.0);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glVertex3f(100.0, 100.0, -100.0);
    glVertex3f(100.0, 100.0, 100.0);
    glVertex3f(100.0, -100.0, 100.0);
    glVertex3f(100.0, -100.0, -100.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    //top
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 100.0, -100.0);
    glVertex3f(100.0, 100.0, -100.0);
    glVertex3f(100.0, 100.0, 100.0);
    glVertex3f(-100.0, 100.0, 100.0);
    glEnd();

    //bottom
    glBegin(GL_QUADS);
    glVertex3f(-100.0, -100.0, -100.0);
    glVertex3f(100.0, -100.0, -100.0);
    glVertex3f(100.0, -100.0, 100.0);
    glVertex3f(-100.0, -100.0, 100.0);
    glEnd();
    glBegin(GL_POINTS);
    glVertex3f(300, 300, 300);
    glEnd();
    glFlush();
}

//Transformations - Built-in functions- only for reference

void disp()
{
    glRotatef(50, 1, 0, 0);
    glRotatef(50, 0, 1, 0);
    glRotatef(50, 0, 0, 1);
}

int main(int argc, char *argv[])
{
    // insert code here...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cube");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    //    std::cout << "Hello, World!\n";
    return 0;
}
