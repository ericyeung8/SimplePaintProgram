// SimplePaintProgram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define pi 3.141592653
#define a 1.4142

int flag = 0;
int mouse_x = 1;
int mouse_y = 1;
int size = 1;
int red = 1;
int green = 0;
int blue = 0;
int clear = 0;
int brush = 1;
int spray = 1;
int r = 0;

/*initialization*/
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);

	/*For spray paint brush*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT);
}

void display(void)
{
	/*clear the screen if pressing c*/
	if (clear == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		clear = 0;
	}

	/*draw a graph if pressing and moving mouse*/
	if (flag == 1)
	{
		glColor3f(red, green, blue);	//setup brush's color
		if (brush == 1)	//draw a rectangle with rotation of r*10 degrees
		{
			glPushMatrix();
			glTranslatef(mouse_x, mouse_y, 0);
			glRotatef(r*10, 0, 0, 1);
			glBegin(GL_QUADS);
				glVertex2f(-size, size);
				glVertex2f(size, size);
				glVertex2f(size, -size);
				glVertex2f(-size, -size);
			glEnd();
			glPopMatrix();
			flag = 0;
		}
		else if (brush == 2)	//draw a triangle with rotation of r*10 degrees
		{
			glPushMatrix();
			glTranslatef(mouse_x, mouse_y, 0);
			glRotatef(r*10, 0, 0, 1);
			glBegin(GL_TRIANGLES);
				glVertex2f(-size, -size);
				glVertex2f(size, -size);
				glVertex2f(0, size);
			glEnd();
			glPopMatrix();
			flag = 0;
		}
		else if (brush == 3)	//draw a line with rotation of r*10 degrees
		{
			glPushMatrix();
			glTranslatef(mouse_x, mouse_y, 0);
			glRotatef(r*10, 0, 0, 1);
			glBegin(GL_LINES);
				glVertex2f(0, -size);
				glVertex2f(0, size);
			glEnd();
			glPopMatrix();
			flag = 0;
		}
		else if (brush == 4)	//draw a circle using triangle_fan
		{
			int i = 0;

			glBegin(GL_TRIANGLE_FAN);
				glShadeModel(GL_SMOOTH);
				glColor4f(red, green, blue, 1);
				glVertex2f(mouse_x, mouse_y);
				for (i=0; i <= 100; i++)
				{
					glColor4f(red, green, blue, spray);	//using spray paint brush if spray == 0
					glVertex2f(mouse_x+size*cos(2*pi*i/100), mouse_y+size*sin(2*pi*i/100));
				}
			glEnd();
			flag = 0;
		}
	}
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '+':	//increase brush size
		size += 2;
		if (size >= 128)
			size = 128;
		break;
	case '-':	//decrease brush size
		size -= 2;
		if (size <= 1)
			size = 1;
		break;
	case '1':	//change color
		red = 1;
		green = 0;
		blue = 0;
		break;
	case '2':	//change color
		red = 0;
		green = 1;
		blue = 0;
		break;
	case '3':	//change color
		red = 1;
		green = 1;
		blue = 0;
		break;
	case '4':	//change color
		red = 0;
		green = 0;
		blue = 1;
		break;
	case '5':	//change color
		red = 1;
		green = 0;
		blue = 1;
		break;
	case '6':	//change color
		red = 0;
		green = 1;
		blue = 1;
		break;
	case '7':	//change color
		red = 1;
		green = 1;
		blue = 1;
		break;
	case 'c':	//clear the screen
		clear = 1;
		break;
	case 'b':	//change brush
		brush ++;
		if (brush > 4)
			brush =1;
		break;
	case 'a':	//change brush
		if (spray == 0)
			spray = 1;
		else spray = 0;
		break;
	case 'r':	//degrees of rotation
		r++;
		break;
	}

	glutPostRedisplay();
}

void mouseMove(int x, int y)
{
	flag = 1;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Jiajun Yang - Assignment 1");
	init();
	glutDisplayFunc(display);
		glutMotionFunc(mouseMove);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
	return 0;
}