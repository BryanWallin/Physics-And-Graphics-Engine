//============================================================================//
//                                                                            //
//  Physics and Graphics Engine                                               //
//                                                                            //
//  Hello, world!                                                             //
//                                                                            //
//  Author: Bryan Wallin                                                      //
//  Last modified on 11/21/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

//Including the necessary files.
#include "..\Common\Headers\glew.h"
#include "..\Common\Headers\freeglut.h"
#include <iostream>
#include <cmath>

#pragma comment(lib, "glew32.lib")

//==============================Global Variables==============================//

//Defining an enumeration to make the reading of key states easier.
enum Keys {
	UpArrow, DownArrow, LeftArrow, RightArrow, W, S, X, Z, Q, E, F, R,
	O, P, ONE, TWO, THREE, NumberOfKeys
};

//==============================Global Variables==============================//

//This array stores the state of the keys used.  If they a key is down, the 
//value for that key is true.  If not, the value for that key is false.
bool keyStates[NumberOfKeys];

//Defining the window width and height.
int windowWidth = 1200, windowHeight = 800;

int previousX, previousY;
bool leftMouseDown = false;
bool rightMouseDown = false;
bool isPaused = false;

float currentTime = 0;
float refreshRateInMillis = 5;
float motionBlurAmount = 0.01;

int currentPosition = 0;

//This method displays the objects sent to the graphics card.
void display(void)
{
	//Clearing the scene.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Rendering the scene.
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glEnd();

	//Swapping the buffers now that the drawing is complete.
	glutSwapBuffers();
}

//This method is called when a key is pressed.
void keysDown(unsigned char key, int x, int y)
{
	if (key == 'o')
	{

	}
}

void keyIsDown(Keys key)
{
	if (key == 'o')
	{

	}
}

void mouseChange(int button, int state, int x, int y)
{
	std::cout << "Mouse Change";
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		leftMouseDown = true;
		previousX = x;
		previousY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		rightMouseDown = true;
		previousX = x;
		previousY = y;
	}
	else if (state == GLUT_UP) {
		leftMouseDown = false;
		rightMouseDown = false;
	}
}

void mouseDragged(int x, int y)
{
	std::cout << "Mouse Dragged";
	if (leftMouseDown)
	{
		previousX = x;
		previousY = y;
	}
	else if (rightMouseDown)
	{
		previousY = y;
	}
}

//This method initializes the program.
void initializeProgram()
{
	//Enabling depth testing and texturing.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//Setting the background color.
	glClearColor(1, 0, 0, 1);
}

//This method reshapes the window and recalculates the new projection view and 
//viewport.
void reshape(int width, int height)
{
	//Changing the window width and height.
	windowWidth = width;
	windowHeight = height;

	//Creating a new projection view based on the changed width and height.
	//mat4 projection = Perspective(sceneManager->getCurrentCamera()->getFOV(),
	//	(float)width / (float)height, 0.25, 1000.0);

	//Updating the viewport.
	glViewport(0, 0, width, height);
}

//A method to update the earth's rotation.
void updateEarth()
{
	if (!isPaused)
	{
		currentTime += refreshRateInMillis / 1000;
	}
}

//This is the "heart" of the program, as it is called every 1/60th of a second 
//to update the program state.
void timer(int milliseconds)
{
	//Updating the earth.
	updateEarth();

	glutPostRedisplay();
	glutTimerFunc(refreshRateInMillis, timer, refreshRateInMillis);
}

//This is the main method, where program execution starts.
int main(int argc, char **argv)
{
	//Setting up the GLUT window.
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glEnable(GL_MULTISAMPLE);
	glutCreateWindow("Final Project");

	//Setting up GLEW.
	glewExperimental = GL_TRUE;
	glewInit();

	//Initializing the program.
	initializeProgram();

	//Setting up the GLUT function callbacks.
	glutDisplayFunc(display);
	glutKeyboardFunc(keysDown);
	glutMouseFunc(mouseChange);
	glutMotionFunc(mouseDragged);
	glutReshapeFunc(reshape);
	glutTimerFunc(refreshRateInMillis, timer, refreshRateInMillis);

	//Starting the GLUT main loop.
	glutMainLoop();

	return 0;
}