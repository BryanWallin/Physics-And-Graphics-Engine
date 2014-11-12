//Including the necessary files.
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "..\Common\Headers\glew.h"
#include "..\Common\Headers\freeglut.h"
#include <GL\gl.h>
#include <cmath>
#include <ostream>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "..\..\..\Physics and Graphics Engine\Math Library\MathLibrary.h"
#include "..\..\..\Physics and Graphics Engine\Graphics Library\GraphicsLibrary.h"
#include "..\..\..\Physics and Graphics Engine\Physics Library\PhysicsLibrary.h"

#pragma comment(lib, "glew32.lib")

using namespace GraphicsEngine;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//==============================Global Variables==============================//

//Defining an enumeration to make the reading of key states easier.
enum Keys 
{
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
float refreshRateInMillis = 1;
float fov = 90;
float rotationX = 0.0f;
float rotationY = 0.0f;
int mipmapLevel = 0;

bool conservativeRasterization = false;

OpenGLProgram *diffuseProgram, *voxelizationProgram, *voxelRenderProgram;
Material *diffuseMaterial, *voxelMaterial;
Camera *camera;
AssetManager *manager;

StaticMesh *floorMesh, *leftWallMesh, *backWallMesh, *rightWallMesh, 
*ceilingMesh, *backBallMesh, *frontBallMesh;
GLuint voxelTexture, voxelFBO;

Matrix4 _modelViewProjectionMatrixNew;

void setupGL(std::string resourcesDirectory)
{
	//Voxelization program setup.
	voxelizationProgram = new OpenGLProgram(
		resourcesDirectory + "VoxelizationShader.vsh",
		resourcesDirectory + "VoxelizationShader.gsh",
		resourcesDirectory + "VoxelizationShader.fsh");

	voxelRenderProgram = new OpenGLProgram(
		resourcesDirectory + "VoxelRayTraceVolume.vsh",
		resourcesDirectory + "VoxelRayTraceVolume.fsh");

	//Diffuse program setup.
	diffuseProgram = new OpenGLProgram(resourcesDirectory + "DefaultShader.vsh",
		resourcesDirectory + "DefaultShader.fsh");

	diffuseMaterial = new Material();
	diffuseMaterial->setProgram(diffuseProgram);

	voxelMaterial = new Material();
	voxelMaterial->setProgram(voxelizationProgram);

	//StaticMesh Creation.
	manager = new AssetManager();
	manager->loadFile(resourcesDirectory + "CornellBox_Floor.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_LeftWall.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_BackWall.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_RightWall.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_Ceiling.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_BackBall.obj");
	manager->loadFile(resourcesDirectory + "CornellBox_FrontBall.obj");

	floorMesh = manager->getStaticMesh("CornellBox_Floor");
	floorMesh->setMaterial(voxelMaterial);
	leftWallMesh = manager->getStaticMesh("CornellBox_LeftWall");
	leftWallMesh->setMaterial(voxelMaterial);
	backWallMesh = manager->getStaticMesh("CornellBox_BackWall");
	backWallMesh->setMaterial(voxelMaterial);
	rightWallMesh = manager->getStaticMesh("CornellBox_RightWall");
	rightWallMesh->setMaterial(voxelMaterial);
	ceilingMesh = manager->getStaticMesh("CornellBox_Ceiling");
	ceilingMesh->setMaterial(voxelMaterial);
	backBallMesh = manager->getStaticMesh("CornellBox_BackBall");
	backBallMesh->setMaterial(voxelMaterial);
	frontBallMesh = manager->getStaticMesh("CornellBox_FrontBall");
	frontBallMesh->setMaterial(voxelMaterial);

	//Camera Creation.
	camera = new Camera("MainCamera");
	camera->getTransform()->setPosition(Vector3(0, 0, 2));

	//Creating voxel texture.
	glGenTextures(1, &voxelTexture);
	glBindTexture(GL_TEXTURE_3D, voxelTexture);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, 128, 128, 128, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_3D, 0);

	// Create an fbo for clearing the 3D texture.
	glGenFramebuffers(1, &voxelFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, voxelFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, voxelTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void clearVoxels()
{
	glBindFramebuffer(GL_FRAMEBUFFER, voxelFBO);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void voxelizeScene()
{
	//Rendering all created fragments, but not storing any color or depth 
	//information.
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, 128, 128);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, voxelTexture);

	Matrix4 projection = Matrix4::Ortho(0.0f, 128.0f, 0.0f, 128.0f, 0.0f,
		-128.0f);
	Matrix4 voxelViewModel = Matrix4::Scale(128, 128, 128) *
		Matrix4::Translate(0.5f, 0.5f, 0.5f) *
		Matrix4::Scale(0.5f, 0.5f, 0.5f);

	float pixelDiagonal = sqrt(2.0f) / 128.0f;

	glUseProgram(voxelizationProgram->getProgramID());

	//Uploading shader uniforms.
	glUniform1f(voxelizationProgram->getUniformID("pixelDiagonal"), 
		pixelDiagonal);
	glUniform1i(voxelizationProgram->getUniformID("conservativeRasterization"), 
		conservativeRasterization);
	glUniform1f(voxelizationProgram->getUniformID("colorCode"),
		true);
	glUniformMatrix4fv(voxelizationProgram->getUniformID("projectionMatrix"),
		1, GL_FALSE, projection);
	glUniformMatrix4fv(voxelizationProgram->getUniformID("modelMatrix"),
		1, GL_FALSE, voxelViewModel);
	glUniform4f(glGetUniformLocation(voxelizationProgram->getProgramID(), 
		"LightPosition"), 0.0f, 0.0f, -1.0f, 0.0f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), 
		"LightAmbient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), 
		"LightDiffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), 
		"MaterialKa"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), 
		"MaterialKd"), 1.0f, 1.0f, 1.0f);
	glBindImageTexture(0, voxelTexture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	//Drawing items.
	glBindVertexArray(floorMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, floorMesh->getVertexData()->getVertexCount());
	glBindVertexArray(leftWallMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, leftWallMesh->getVertexData()->getVertexCount());
	glBindVertexArray(backWallMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, backWallMesh->getVertexData()->getVertexCount());
	glBindVertexArray(rightWallMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, rightWallMesh->getVertexData()->getVertexCount());
	glBindVertexArray(ceilingMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, ceilingMesh->getVertexData()->getVertexCount());
	glBindVertexArray(backBallMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, backBallMesh->getVertexData()->getVertexCount());
	glBindVertexArray(frontBallMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, frontBallMesh->getVertexData()->getVertexCount());


	glGenerateMipmap(GL_TEXTURE_3D);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}


	//Re-enabling depth writes, color writes, and depth testing.
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void renderVoxels()
{
	// Setup and clear viewport.
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculate transformation matrices.
	Matrix4 projectionMe = Matrix4::Perspective(60.0f, windowWidth /
		(float)windowHeight, 0.001f, 10.0f);

	Matrix4 modelviewMe = Matrix4::Translate(0.0f, 0.0f, -2.0f)
		* Matrix4::Scale(1.0f / 128.0f, 1.0f / 128.0f, 1.0f / 128.0f)
		* Matrix4::Translate(-128.0f * 0.5f, -128.0f * 0.5f, -128.0f * 0.5f);

	Matrix4 modelViewProjectionMe = (projectionMe * modelviewMe);
	Matrix4 modelViewProjectionInverseMe = (projectionMe * modelviewMe).invert();

	// Bind shader.
	glUseProgram(voxelRenderProgram->getProgramID());
	glUniform1i(glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"VolumeTexture"), 0);

	GLuint a = glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"MipmapLevel");
	glUniformMatrix4fv(glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"ModelViewProjectionInverse"), 1, GL_FALSE, modelViewProjectionInverseMe);
	glUniform3f(glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"VolumeDimensions"), 128.0f, 128.0f, 128.0f);
	glUniform1f(glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"StepSize"), 0.9f);
	glUniform1f(glGetUniformLocation(voxelRenderProgram->getProgramID(),
		"MipmapLevel"), mipmapLevel);

	// Bind texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, voxelTexture);

	// Render fullscreen quad.
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();

	// Undo state changes.
	glBindTexture(GL_TEXTURE_3D, 0);
	glUseProgram(0);
}

//This method displays the objects sent to the graphics card.
void display()
{
	//Clearing the voxels and generating the new voxel structure.
	clearVoxels();
	voxelizeScene();

	//Rendering the voxels.
	renderVoxels();

	//Swapping the buffers now that the drawing is complete.
	glutSwapBuffers();
}

//This method is called when a key is pressed.
void keysDown(unsigned char key, int x, int y)
{
	if (key == 'q')
		glutLeaveMainLoop();
	if (key == 'c')
		conservativeRasterization = !conservativeRasterization;
	if (key == 'o')
		mipmapLevel--;
	if (key == 'p')
		mipmapLevel++;

	if (mipmapLevel < 0)
		mipmapLevel = 0;
	if (mipmapLevel > 10)
		mipmapLevel = 10;
}

void keyIsDown(Keys key)
{
	if (key == 'o')
	{

	}
}

void mouseChange(int button, int state, int x, int y)
{
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
	if (leftMouseDown)
	{
	}
	else if (rightMouseDown)
	{
	}
}

//This method initializes the program.
void initializeProgram(std::string resourcesDirectory)
{
	//Enabling depth testing and texturing.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_3D);

	//Setting the background color.
	glClearColor(0, 0, 0, 1);

	setupGL(resourcesDirectory);
}

//This method reshapes the window and recalculates the new projection view and 
//viewport.
void reshape(int width, int height)
{
	//Changing the window width and height.
	windowWidth = width;
	windowHeight = height;

	//Updating the viewport.
	glViewport(0, 0, width, height);
}

void update()
{
	float aspect = (float)windowWidth / (float)windowHeight;
	Matrix4 projectionMatrixNew = Matrix4::Perspective(60.0f, aspect, 0.001f, 10.0f);

	Matrix4 modelViewMatrixNew = camera->getTransform()->getInverseTransform();

	_modelViewProjectionMatrixNew = projectionMatrixNew * modelViewMatrixNew;

	rotationX += .5;
	rotationY += .5;
}

//This is the "heart" of the program, as it is called every 1/60th of a second 
//to update the program state.
void timer(int milliseconds)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	//Updating.
	update();

	//Drawing a new frame and resetting the timer.
	glutPostRedisplay();
	glutTimerFunc(refreshRateInMillis, timer, refreshRateInMillis);
}

//This is the main method, where program execution starts.xzc
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
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit() failed, aborting.\n";
	}

	printf("OpenGL version: %s\n", (char*)glGetString(GL_VERSION));

	std::string path = argv[0];
	std::string directory = path.substr(0, path.find_last_of('\\'));
	std::string resourcesDirectory = 
		directory.substr(0, directory.find_last_of('\\')) + "\\Resources\\";

	//Initializing the program.
	initializeProgram(resourcesDirectory);

	//Setting up the GLUT function callbacks.
	glutDisplayFunc(display);
	glutKeyboardFunc(keysDown);
	glutMouseFunc(mouseChange);
	glutMotionFunc(mouseDragged);
	glutReshapeFunc(reshape);
	glutTimerFunc(refreshRateInMillis, timer, refreshRateInMillis);

	//Starting the GLUT main loop.
	glutMainLoop();

	_CrtDumpMemoryLeaks();

	std::cout << "\nFinished Program.\n";

	return 0;
}