/*to make cube active - c
to make prism active - p
to make both active - b
to make bigger/smaller - +/-
to move use arrows
to rotate use wasd
to change rotation mode - r*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#define GL_BGR   0x80E0
#define pi (3.14)

#define CUBE (0)
#define PRISM (1)
#define	BOTH (2)

#define X (0)
#define Y (1)

float size_cube = 0.5;
float size_prism = 0.5;
float color_cube[3];
float color_prism[3];
float pos_cube[3];
float pos_prism[3];
int angle_cube[2];
int angle_prism[2];
int timer = 0;
int state = CUBE;
int rotating_state = 0;

int xpos, ypos;

void init(void) 
{
	pos_cube[0] = -1.0;
	pos_cube[1] = 0.0;
	pos_cube[2] = 0.0;
	pos_prism[0] = 1.0;
	pos_prism[1] = 0.0;
	pos_prism[2] = 0.0;

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 20.2, 20.0, 30.0, 0.0 };
	glClearColor(0.6, 0.3, 0.2, 0.3); //screen's color
	glShadeModel(GL_FLAT);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void mouse(int x, int y) 
{
	xpos = x;
	ypos = y;

	glutPostRedisplay();
}

void timer_func(int a) 
{
	if (timer < 350) {
		timer++;
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer_func, a);
}

void drawAxes()
{
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glPopMatrix();

	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
}

void drawCube(float size) 
{
	glTranslatef(pos_cube[0], pos_cube[1], pos_cube[2]);
	glColor3f(color_cube[0], color_cube[1], color_cube[2]);
	glPushMatrix();
	glPopMatrix();

	glRotatef(angle_cube[0], 1.0, 0.0, 0.0);
	glRotatef(angle_cube[1], 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	//front
	glNormal3f(0.0f, 0.0f, size); 
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);
	//back
	glNormal3f(0.0f, 0.0f, -1.0*size);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	//top
	glNormal3f(0.0f, 1.0*size, 0.0f);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	//bottom
	glNormal3f(0.0f, -1.0*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	//right
	glNormal3f(1.0*size, 0.0f, 0.0f);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	//left
	glNormal3f(-1.0*size, 0.0f, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawPrism(float size) 
{
	glTranslatef(pos_prism[0], pos_prism[1], pos_prism[2]);
	glColor3f(color_prism[0], color_prism[1], color_prism[2]);
	glPushMatrix();
	glPopMatrix();

	glRotatef(angle_prism[0], 1.0, 0.0, 0.0);
	glRotatef(angle_prism[1], 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	//top
	glNormal3f(0.0f, 1.5*size, 0.0f);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	glVertex3f(size, 0.5*size, 0.0f);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);
	glVertex3f(-size, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	glEnd();
	glBegin(GL_POLYGON);
	//bottom
	glNormal3f(0.0f, -1.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(size, -0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(-size, -0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glEnd();
	glBegin(GL_QUADS);
	//back
	glNormal3f(0.0f, 0.0f, -1.0*size);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	//front
	glNormal3f(0.0f, 0.0f, size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);
	//left-front - right-back
	glNormal3f(1.25*size, 0.0f, -0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(size, -0.5*size, 0.0f);
	glVertex3f(size, 0.5*size, 0.0f);
	glVertex3f(0.5*size, 0.5*size, -0.5*size);
	//left-back - right-front
	glNormal3f(1.25*size, 0.0f, 0.5*size);
	glVertex3f(size, -0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, 0.5*size, 0.5*size);
	glVertex3f(size, 0.5*size, 0.0f);
	//right-front  - left-back
	glNormal3f(-1.25*size, 0.0f, -0.5*size);
	glVertex3f(-size, -0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, 0.5*size, -0.5*size);
	glVertex3f(-size, 0.5*size, 0.0f);
	//right-back   - left-front
	glNormal3f(-1.25*size, 0.0f, 0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(-size, -0.5*size, 0.0f);
	glVertex3f(-size, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, 0.5*size, 0.5*size);

	glEnd();

	/*glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// Front
	glNormal3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	// Right
	glNormal3f(1.0*size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0*size);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	// Left
	glNormal3f(-1.0*size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glEnd();   
	glBegin(GL_QUADS);
	//bottom
	glNormal3f(0.0f, -1.0*size, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glEnd();// Done drawing the pyramid*/

	glDisable(GL_TEXTURE_2D);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 4.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glScalef(1.0, 1.0, 1.0);

	drawAxes();

	//DRAWING CUBE
	glPushMatrix();
	//rotate to get the right perspective
	glRotatef(1.0, 5.0, 0.0, 0.0);
	drawCube(size_cube);
	glPopMatrix();

	//DRAWING Prism
	glPushMatrix();
	//rotate to get the right perspective
	glRotatef(11.0, 3.0, 0.0, 0.0);
	drawPrism(size_prism);
	glPopMatrix();

	glFlush();
}

void rotate_cube_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_cube[0] * pos_cube[0] + pos_cube[2] * pos_cube[2]);
		if (radius == 0)
		{
			angle_cube[1] += direction;
			return;
		}
		angle_x = acos(pos_cube[0] / radius);
		angle_x += direction*pi / 180; 
		pos_cube[0] = radius*cos(angle_x);
		pos_cube[2] = radius*sin(angle_x);
		std::cout << pos_cube[2] << std::endl;
	}
	else
	{
		radius = sqrt(pos_cube[1] * pos_cube[1] + pos_cube[2] * pos_cube[2]);
		if (radius == 0)
		{
			angle_cube[0] += direction;
			return;
		}
		angle_y = acos(pos_cube[1] / radius);
		angle_y += direction*pi / 180;
		pos_cube[1] = radius*cos(angle_y);
		pos_cube[2] = radius*sin(angle_y);
	}
}

void rotate_prism_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_prism[0] * pos_prism[0] + pos_prism[2] * pos_prism[2]);
		if (radius == 0)
		{
			angle_prism[1] += direction;
			return;
		}
		angle_x = acos(pos_prism[0] / radius);
		std::cout << angle_x << std::endl;
		angle_x += direction*pi / 180;
		std::cout << angle_x << std::endl;
		pos_prism[0] = radius*cos(angle_x);
		pos_prism[2] = radius*sin(angle_x);
	}
	else
	{
		radius = sqrt(pos_prism[1] * pos_prism[1] + pos_prism[2] * pos_prism[2]);
		if (radius == 0)
		{
			angle_prism[0] += direction;
			return;
		}
		angle_y = acos(pos_prism[1] / radius);
		angle_y += direction*pi / 180;
		pos_prism[1] = radius*cos(angle_y);
		pos_prism[2] = radius*sin(angle_y);
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c': state = CUBE; break;
	case 'p': state = PRISM; break;
	case 'b': state = BOTH; break;
	case 'r':
		if (rotating_state == 0) rotating_state = 1;
		else rotating_state = 0;
		break;
	case '+':
		switch (state)
		{
		case CUBE:
			if (size_cube <= 1)
				size_cube += 0.1;
			break;
		case PRISM:
			if (size_prism <= 1)
				size_prism += 0.1;
			break;
		case BOTH:
			if (size_cube <= 1)
				size_cube += 0.1;
			if (size_prism <= 1)
				size_prism += 0.1;
			break;
		}
		break;
	case '-':
		switch (state)
		{
		case CUBE:
			if (size_cube >= 0.2)
				size_cube -= 0.1;
			break;
		case PRISM:
			if (size_prism >= 0.2)
				size_prism -= 0.1;
			break;
		case BOTH:
			if (size_cube >= 0.2)
				size_cube -= 0.1;
			if (size_prism >= 0.2)
				size_prism -= 0.1;
			break;
		}
		break;
	case 'w':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case CUBE: angle_cube[0]++; break;
			case PRISM: angle_prism[0]++; break;
			case BOTH: angle_cube[0]++; angle_prism[0]++; break;
			}
		}
		else
		{
			switch (state)
			{
			case CUBE: rotate_cube_global_axes(X, 1); break;
			case PRISM: rotate_prism_global_axes(X, 1); break;
			case BOTH: rotate_cube_global_axes(X, 1); rotate_prism_global_axes(X, 1); break;
			}
		}
		break;
	case 's':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case CUBE: angle_cube[0]--; break;
			case PRISM: angle_prism[0]--; break;
			case BOTH: angle_cube[0]--; angle_prism[0]--; break;
			}
		}
		else
		{
			switch (state)
			{
			case CUBE: rotate_cube_global_axes(X, -1); break;
			case PRISM: rotate_prism_global_axes(X, -1); break;
			case BOTH: rotate_cube_global_axes(X, -1); rotate_prism_global_axes(X, -1); break;
			}
		}
		break;
	case 'd':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case CUBE: angle_cube[1]++; break;
			case PRISM: angle_prism[1]++; break;
			case BOTH: angle_cube[1]++; angle_prism[1]++; break;
			}
		}
		else
		{
			switch (state)
			{
			case CUBE: rotate_cube_global_axes(Y, 1); break;
			case PRISM: rotate_prism_global_axes(Y, 1); break;
			case BOTH: rotate_cube_global_axes(Y, 1); rotate_prism_global_axes(Y, 1); break;
			}
		}
		break;
	case 'a':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case CUBE: angle_cube[1]--; break;
			case PRISM: angle_prism[1]--; break;
			case BOTH: angle_cube[1]--; angle_prism[1]--; break;
			}
		}
		else
		{
			switch (state)
			{
			case CUBE: rotate_cube_global_axes(Y, -1); break;
			case PRISM: rotate_prism_global_axes(Y, -1); break;
			case BOTH: rotate_cube_global_axes(Y, -1); rotate_prism_global_axes(Y, -1); break;
			}
		}
		break;
	}
}

void skeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		switch (state)
		{
		case CUBE: pos_cube[1] -= 0.1; break;
		case PRISM: pos_prism[1] -= 0.1; break;
		case BOTH: pos_cube[1] -= 0.1; pos_prism[1] -= 0.1; break;
		}
		break;
	case GLUT_KEY_UP:
		switch (state)
		{
		case CUBE: pos_cube[1] += 0.1; break;
		case PRISM: pos_prism[1] += 0.1; break;
		case BOTH: pos_cube[1] += 0.1; pos_prism[1] += 0.1; break;
		}
		break;
	case GLUT_KEY_LEFT:
		switch (state)
		{
		case CUBE: pos_cube[0] -= 0.1; break;
		case PRISM: pos_prism[0] -= 0.1; break;
		case BOTH: pos_cube[0] -= 0.1; pos_prism[0] -= 0.1; break;
		}
		break;
	case GLUT_KEY_RIGHT:
		switch (state)
		{
		case CUBE: pos_cube[0] += 0.1; break;
		case PRISM: pos_prism[0] += 0.1; break;
		case BOTH: pos_cube[0] += 0.1; pos_prism[0] += 0.1; break;
		}
		break;
	}

}

void set_color()
{
	char answer = 0;
	std::cout << "Do you want to choose color of the figures? y/n\n";
	while (answer != 'y' && answer != 'n')
		std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Enter cube color: ";
		std::cin >> color_cube[0] >> color_cube[1] >> color_cube[2];
		std::cout << "Enter prism color: ";
		std::cin >> color_prism[0] >> color_prism[1] >> color_prism[2];
	}
	else
	{
		color_cube[0] = 0.2; color_cube[1] = 0.5; color_cube[2] = 0.8;
		color_prism[0] = 0.8; color_prism[1] = 0.1; color_prism[2] = 0.2;
	}
}

int main(int argc, char** argv) 
{
	set_color();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(skeyboard);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, timer_func, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	return 0;
}
