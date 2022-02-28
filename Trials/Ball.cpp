//Ball Bounce

#include <GL/glut.h>

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS = 10;

int motion = 0;		//For animation
int direction = 1;	//For direction

void initializeDisplay();
void bounceBall();
void mainLoop(int val);
void keyboardKeys(unsigned int val, int x, int y);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutCreateWindow("Ball Bounce");

	initializeDisplay();

	glutDisplayFunc(bounceBall);
	glutTimerFunc(1000/FPS, mainLoop, 0);
	glutMainLoop();
	
	return 1;
}

void initializeDisplay(){
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(120, 1, 0.01, 3);
	glOrtho(-2, 2, -2, 2, -2, 2);
	//gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
}

void mainLoop(int val){
	motion += 100 * direction;

	direction *= -1;

	bounceBall();
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, mainLoop, 0);
}

void bounceBall(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glPushMatrix();
	glColor3d(0, 1, 0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3d(-8, 0, 0);
	glVertex3d(8, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0, 0, 1);
	//glRotatef(45, 1, 1, 1);
	glTranslatef(0, motion, 0);
	//glutSolidCube(1);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPopMatrix();
	

	glFlush();
	//glutSwapBuffers();
}