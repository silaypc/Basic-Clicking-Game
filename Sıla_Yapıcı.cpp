
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define START 1
#define RUN 2

int status = START;

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

struct fish_t{
	int x, y;
};

fish_t fish[10];
int mX, mY, fCount;



//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

void displayCoral()
{
	//CORAL 1
	glBegin(GL_POLYGON);
	glColor3ub(252, 188, 58);
	glVertex2f(-400, -400);
	glVertex2f(-400, -275);
	glVertex2f(-375, -250);
	glVertex2f(-350, -250);
	glVertex2f(-375, -275);
	glVertex2f(-375, -325);
	glVertex2f(-325, -275);
	glVertex2f(-325, -250);
	glVertex2f(-300, -250);
	glVertex2f(-300, -275);
	glVertex2f(-350, -325);
	glVertex2f(-350, -350);
	glVertex2f(-300, -300);
	glVertex2f(-275, -300);
	glVertex2f(-275, -250);
	glVertex2f(-300, -225);
	glVertex2f(-300, -200);
	glVertex2f(-275, -200);
	glVertex2f(-275, -225);
	glVertex2f(-250, -250);
	glVertex2f(-250, -300);
	glVertex2f(-275, -325);
	glVertex2f(-300, -325);
	glVertex2f(-375, -400);
	glVertex2f(-400, -400);
	glEnd();

	//CORAL 2
	glBegin(GL_POLYGON);
	glColor3ub(219, 105, 29);
	glVertex2f(300, -400);
	glVertex2f(350, -350);
	glVertex2f(350, -275);
	glVertex2f(375, -250);
	glVertex2f(375, -175);
	glVertex2f(350, -175);
	glVertex2f(350, -250);
	glVertex2f(325, -275);
	glVertex2f(300, -250);
	glVertex2f(300, -225);
	glVertex2f(275, -225);
	glVertex2f(275, -250);
	glVertex2f(325, -300);
	glVertex2f(325, -325);
	glVertex2f(300, -350);
	glVertex2f(300, -300);
	glVertex2f(275, -275);
	glVertex2f(275, -250);
	glVertex2f(275, -300);
	glVertex2f(275, -375);
	glVertex2f(225, -325);
	glVertex2f(225, -225);
	glVertex2f(250, -200);
	glVertex2f(250, -175);
	glVertex2f(225, -175);
	glVertex2f(225, -200);
	glVertex2f(200, -225);
	glVertex2f(200, -275);
	glVertex2f(175, -250);
	glVertex2f(175, -225);
	glVertex2f(150, -225);
	glVertex2f(150, -250);
	glVertex2f(200, -300);
	glVertex2f(150, -225);
	glVertex2f(200, -350);
	glVertex2f(150, -225);
	glVertex2f(275, -400);
	glEnd();
}
//
// To display onto window using OpenGL commands
//

void displayFish()
{

	glBegin(GL_TRIANGLES);
	glColor3ub(197, 224, 105);
	glVertex2f(25, 75);
	glVertex2f(25, 125);
	glVertex2f(100, 125);
	glEnd();
	
	glColor3ub(167, 204, 114);
	glRectf(0, 25, 25, 75);
	glRectf(125, 75, 150, 150);
	glRectf(150, 75, 175, 100);

	glBegin(GL_TRIANGLES);
	glColor3ub(166, 209, 109);
	glVertex2f(0, 0);
	glVertex2f(0, 50);
	glVertex2f(-50, 50);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(166, 209, 109);
	glVertex2f(0, 50);
	glVertex2f(-25, 50);
	glVertex2f(0, 75);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(166, 209, 109);
	glVertex2f(125, 75);
	glVertex2f(125, 150);
	glVertex2f(0, 75);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(176, 214, 124);
	glVertex2f(25, 25);
	glVertex2f(25, 75);
	glVertex2f(175, 75);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(176, 214, 124);
	glVertex2f(150, 150);
	glVertex2f(150, 100);
	glVertex2f(200, 100);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(217, 143, 93);
	glVertex2f(175, 75);
	glVertex2f(175, 100);
	glVertex2f(200, 100);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(197, 224, 105);
	glVertex2f(100, 75);
	glVertex2f(100, 25);
	glVertex2f(50, 75);
	glEnd();

	glColor3ub(247, 240, 240);
	circle(137, 112, 13);
	glColor3ub(201, 192, 169);
	circle(137, 112, 10);
	glColor3ub(74, 69, 56);
	circle(137, 112, 7);

    glLineWidth(5);
	glColor4ub(116, 156, 95, 70);
	glBegin(GL_LINES);
	glVertex2f(200, 100);
	glVertex2f(180, 100);
	glEnd();

	glColor4ub(247, 240, 240, 75);
	circle(230, 110, 10);
	glColor4ub(247, 240, 240, 75);
	circle(260, 128, 6);
	glColor4ub(247, 240, 240, 75);
	circle(228, 160, 5);

}

void displayChest()
{
	glColor3ub(150, 96, 69);
	glRectf(-175, -400, 75, -250);
	circle(-100, -250, 75);
	circle(-0, -250, 75);
	glRectf(-100, -250, 0, -175);

	glColor3ub(235, 204, 70);
	circle(-100, -250, 75);
	circle(-0, -250, 75);
	glColor3ub(150, 96, 69);
	circle(-100, -250, 65);
	circle(-0, -250, 65);
	glRectf(-175, -400, 75, -250);
	glRectf(-100, -250, 0, -175);
	glColor3ub(235, 204, 70);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2f(-100, -180);
	glVertex2f(0, -180);

	glLineWidth(5);
	glColor4ub(61, 57, 39, 50);
	glBegin(GL_LINES);
	glVertex2f(-150, -400);
	glVertex2f(-150, -250);
	glVertex2f(-125, -400);
	glVertex2f(-125, -250);
	glVertex2f(-100, -400);
	glVertex2f(-100, -250);
	glVertex2f(-75, -400);
	glVertex2f(-75, -250);
	glVertex2f(-50, -400);
	glVertex2f(-50, -250);
	glVertex2f(-25, -400);
	glVertex2f(-25, -250);
	glVertex2f(0, -400);
	glVertex2f(0, -250);
	glVertex2f(25, -400);
	glVertex2f(25, -250);
	glVertex2f(50, -400);
	glVertex2f(50, -250);
	glEnd();
	

	glLineWidth(10);
	glColor3ub(235, 204, 70);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-175, -400);
	glVertex2f(-175, -250);
	glVertex2f(75, -250);
	glVertex2f(75, -400);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(61, 57, 39);
	glVertex2f(-180, -350);
	glVertex2f(-180, -400);
	glVertex2f(-150, -400);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(61, 57, 39);
	glVertex2f(80, -400);
	glVertex2f(50, -400);
	glVertex2f(80, -350);
	glEnd();
	
	glColor3ub(235, 204, 70);
	glRectf(-75, -275, -25, -230);
	glColor3ub(61, 57, 39);
	circle(-50, -245, 8);
	glBegin(GL_TRIANGLES);
	glColor3ub(61, 57, 39);
	glVertex2f(-50, -245);
	glVertex2f(-63, -265);
	glVertex2f(-37, -265);
	glEnd();

	


}


void display_shape(int x, int y)
{
	glColor3ub(207, 95, 87);
	glRectf(x - 25, y - 25, x + 25, y + 25);
	glBegin(GL_TRIANGLES);

	glColor3ub(209, 104, 96);
	glVertex2f(x - 12, y + 25);
	glVertex2f(x - 33, y);
	glVertex2f(x - 40, y + 33);
	glColor3ub(189, 123, 100);
	glVertex2f(x - 75, y - 25);
	glVertex2f(x - 75, y + 25);
	glVertex2f(x - 50, y);
	
	glVertex2f(x + 25, y - 25);
	glVertex2f(x + 25, y + 25);
	glVertex2f(x + 50, y);
	glColor3ub(217, 143, 93);
	glVertex2f(x - 25, y - 25);
	glVertex2f(x - 25, y + 25);
	glVertex2f(x - 50, y);

	glVertex2f(x, y);
	glVertex2f(x, y - 33);
	glVertex2f(x - 25, y - 29);
	glEnd();
	
	glColor3ub(247, 240, 240);
	circle(x + 25, y + 12, 6);
	glColor3ub(201, 192, 169);
	circle(x + 25, y + 12, 4);
	glColor3ub(74, 69, 56);
	circle(x + 25, y + 12, 2);
	
}



void display() {
	
	//background gradient
	glBegin(GL_POLYGON);
	glColor3ub(181, 213, 230);
	glVertex2f(-400, 400);
	glVertex2f(400, 400);
	glColor3ub(120, 175, 191);
	glVertex2f(400, -400);
	glVertex2f(-400, -400);
	glEnd();
	

	//fish1
	displayFish();
	//chest
	displayChest();

	//label
	glColor3ub(204, 225, 230);
	glRectf(-400, 325, -275, 400);
	glColor3f(1, 1, 1);
	vprint(-390, 375, GLUT_BITMAP_HELVETICA_18, "Sila Yapici");
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3ub(240, 244, 245);
	glVertex2f(-400, 400);
	glVertex2f(-275, 400);
	glVertex2f(-275, 325);
	glVertex2f(-400, 325);
	glEnd();

	//info
	glColor3f(1, 1, 1);
	vprint(-200, 375, GLUT_BITMAP_HELVETICA_12, "[Click left mouse button to create fish (Max 10)]                 [Press F1 to make the fish move]");


	int i;
	for (i = 0; i < fCount; i++)
	{
		display_shape(fish[i].x, fish[i].y);
	}

    //corals // corals after object so the object can pass behind the corals
    displayCoral();
	glutSwapBuffers();
	
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	if (key == GLUT_KEY_F1 && status == START)
		status = RUN;
	else if (key == GLUT_KEY_F1 && status == RUN)
	{
		status = START;
	}

	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.

	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && fCount < 10)
	{
		if (status == START) {
			fish[fCount].x = mX;
			fish[fCount].y = mY;
			fCount++;
		}

	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.
	mX = x - winWidth / 2;
	mY = winHeight / 2 - y;


	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	int i ,counter = 0;
	if (status == RUN)
	{
		for (i = 0; i < fCount; i++) {

			fish[i].x += 4;
			if (fish[i].x - 75 > 399)
				counter++;
			if (counter == fCount)
			{
				counter = 0;
				fCount = 0;
				status = START;
			}
		}
		
	}

	




	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("Rapture");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}