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

float currentTime = 0;
float refreshRateInMillis = 5;
float motionBlurAmount = 0.01;

int currentPosition = 0;

float fov = 90;

GLuint particleVertexArray, particleVertexBuffer;

OpenGLProgram *diffuseProgram, *defaultProgram, *voxelizationProgram, *voxelRenderProgram;
Material *floorMaterial, *monkeyMaterial;
Camera *camera;
AssetManager *manager;

Transform::TransformSpace space = Transform::Local;

StaticMesh *floorMesh, *monkeyMesh, *bunnyMesh;
Texture *floorTexture;
GLuint floorTexturePointer, voxelTexture, voxelFBO;

int texUnit = 0;

float rotation = 0.0f;

Matrix4 _modelViewProjectionMatrixNew;
Matrix3 _normalMatrixNew;
int vertexCount, particleVertexCount;

std::clock_t updateClock;

bool loadShaders(std::string resourcesDirectory)
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
	diffuseProgram = new OpenGLProgram(resourcesDirectory + "Diffuse.vsh",
		resourcesDirectory + "Diffuse.fsh");
	
	//Default program setup.
	defaultProgram = new OpenGLProgram(resourcesDirectory + "DefaultShader.vsh",
		resourcesDirectory + "DefaultShader.fsh");

	//Floor material setup.
	floorMaterial = new Material();
	floorMaterial->setProgram(diffuseProgram);
	floorMaterial->setTexture("diffuse", floorTexture);

	monkeyMaterial = new Material();
	monkeyMaterial->setProgram(defaultProgram);

	return true;
}

void setupGL(std::string resourcesDirectory)
{
	using namespace GraphicsEngine;

	//StaticMesh Creation.
	manager = new AssetManager();
	manager->loadFile(resourcesDirectory + "Monkey.obj");
	manager->loadFile(resourcesDirectory + "Bunny.obj");
	manager->loadFile(resourcesDirectory + "Floor.dae");
	floorMesh = manager->getStaticMesh("Floor");
	floorMesh->setMaterial(floorMaterial);

	monkeyMesh = manager->getStaticMesh("\\Monkey.obj");
	monkeyMesh->setMaterial(monkeyMaterial);

	bunnyMesh = manager->getStaticMesh("\\Bunny.obj");
	bunnyMesh->setMaterial(monkeyMaterial);

	//Camera Creation.
	camera = new Camera("MainCamera");
	camera->getTransform()->setPosition(Vector3(0, 0, 2));

	floorTexture = new Texture(resourcesDirectory + "ConcreteTileFloor.tga");
	floorTexture->setTextureType(DiffuseTexture);

	//Creating voxel texture.
	glGenTextures(1, &voxelTexture);
	glBindTexture(GL_TEXTURE_3D, voxelTexture);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, 128, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glBindTexture(GL_TEXTURE_3D, 0);

	// Create an fbo for clearing the 3D texture.
	glGenFramebuffers(1, &voxelFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, voxelFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, voxelTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenTextures(1, &floorTexturePointer);
	glBindTexture(GL_TEXTURE_2D, floorTexturePointer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		floorTexture->getWidth(), floorTexture->getHeight(), 0,
		GL_BGRA, GL_UNSIGNED_BYTE, floorTexture->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	GLubyte *imgPointer = (GLubyte *)malloc(floorTexture->getHeight() * 
		floorTexture->getWidth()*4);
	for (int i = 0; i < floorTexture->getHeight() *
		floorTexture->getWidth(); i++)
		imgPointer[i] = 0;

	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgPointer);
	for (int i = 0; i < floorTexture->getHeight() *
		floorTexture->getWidth(); i++)
	{
		//if (imgPointer[i] > 0)
			//std::cout << "Voxel at (" << i << ") is " << (int)imgPointer[i] << ".\n";
	}
	free(imgPointer);


	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
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

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	Matrix4 projection = Matrix4::Ortho(0.0f, 128.0f, 0.0f, 128.0f, 0.0f,
		-128.0f);
	Matrix4 floorModelView = Matrix4::Scale(128, 128, 128) * 
		Matrix4::Translate(0.5f, 0.5f, 0.5f) * 
		Matrix4::Scale(0.5f, 0.5f, 0.5f);
	Matrix4 monkeyModelView = floorModelView *
		Matrix4::RotationX(0) * Matrix4::RotationY(0);

	float pixelDiagonal = sqrt(2.0f) / 128.0f;

	glUseProgram(voxelizationProgram->getProgramID());

	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	//Uploading shader uniforms.
	glUniform1f(voxelizationProgram->getUniformID("pixelDiagonal"), 
		pixelDiagonal);
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}
	glUniform1i(voxelizationProgram->getUniformID("conservativeRasterization"), 
		false);
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}
	glUniform1f(voxelizationProgram->getUniformID("colorCode"),
		false);
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}
	glUniformMatrix4fv(voxelizationProgram->getUniformID("projectionMatrix"),
		1, GL_FALSE, projection);
	glUniformMatrix4fv(voxelizationProgram->getUniformID("modelMatrix"),
		1, GL_FALSE, floorModelView);
	glUniform4f(glGetUniformLocation(voxelizationProgram->getProgramID(), "LightPosition"), 0.0f, 0.0f, -1.0f, 0.0f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), "LightAmbient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), "LightDiffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), "MaterialKa"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(voxelizationProgram->getProgramID(), "MaterialKd"), 1.0f, 1.0f, 1.0f);

	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	glBindImageTexture(0, voxelTexture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	//Drawing items.
	glBindVertexArray(floorMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, floorMesh->getVertexData()->getVertexCount());

	glUniformMatrix4fv(voxelizationProgram->getUniformID("worldToEyeMatrix"),
		1, GL_FALSE, monkeyModelView);

	glBindVertexArray(bunnyMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, bunnyMesh->getVertexData()->getVertexCount());

	//Re-enabling depth writes, color writes, and depth testing.
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void renderVoxels()
{
	// Setup and clear viewport.
	//glViewport(0, 0, windowWidth, windowHeight);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate transformation matrices.
	Matrix4 projection = Matrix4::Perspective(60.0f, windowWidth / 
		(float)windowHeight, 0.001f, 10.0f);

	Matrix4 modelview = Matrix4::Translate(0.0f, 0.0f, -2.0f)//-cameraZoom)
		* Matrix4::Scale(1.0f / 128.0f, 1.0f / 128.0f, 1.0f / 128.0f)
		* Matrix4::Translate(-128.0f * 0.5f, -128.0f * 0.5f, -128.0f * 0.5f);

	Matrix4 modelViewProjectionInverse = modelview.invert();

	// Bind shader.
	glUseProgram(voxelRenderProgram->getProgramID());
	glUniform1i(glGetUniformLocation(voxelRenderProgram->getProgramID(), "VolumeTexture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(voxelRenderProgram->getProgramID(), "ModelViewProjectionInverse"), 1, GL_FALSE, modelViewProjectionInverse);
	glUniform3f(glGetUniformLocation(voxelRenderProgram->getProgramID(), "VolumeDimensions"), 128.0f, 128.0f, 128.0f);
	glUniform1f(glGetUniformLocation(voxelRenderProgram->getProgramID(), "StepSize"), 0.9f);

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

	// Render bounding box.
	if (true)
	{
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION); glLoadMatrixf(projection);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(modelview);
		glTranslatef(128.0f * 0.5f, 128.0f * 0.5f, 128.0f * 0.5f);

		glColor4f(1, 1, 1, 1);
		glutWireCube(128.0f);
		glEnable(GL_DEPTH_TEST);
	}
}

//This method displays the objects sent to the graphics card.
void display()
{
	//Clearing the scene.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Settinng the viewport.
	glViewport(0, 0, windowWidth, windowHeight);

	//Drawing the floor.
	glUseProgram(floorMesh->getMaterial()->getProgram()->getProgramID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexturePointer);
	glUniform1i(glGetUniformLocation(diffuseProgram->getProgramID(),
		"diffuse"), 0);

	glUniformMatrix4fv(diffuseProgram->getUniformID("projectionMatrix"),
		1, GL_FALSE, _modelViewProjectionMatrixNew);

	glUniformMatrix4fv(diffuseProgram->getUniformID("worldToEyeMatrix"),
		1, GL_FALSE, floorMesh->getTransform()->getTransform());

	glBindVertexArray(floorMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, floorMesh->getVertexData()->getVertexCount());

	glUseProgram(bunnyMesh->getMaterial()->getProgram()->getProgramID());

	glUniformMatrix4fv(diffuseProgram->getUniformID("projectionMatrix"),
		1, GL_FALSE, _modelViewProjectionMatrixNew);

	glUniformMatrix4fv(diffuseProgram->getUniformID("worldToEyeMatrix"),
		1, GL_FALSE, bunnyMesh->getTransform()->getTransform());

	glBindVertexArray(bunnyMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, bunnyMesh->getVertexData()->getVertexCount());

	renderVoxels();

	//Swapping the buffers now that the drawing is complete.
	glutSwapBuffers();
}

//This method is called when a key is pressed.
void keysDown(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		_CrtDumpMemoryLeaks();
		glutLeaveMainLoop();
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
		rotation -= (float) (x - previousX) * .001f;

		previousX = x;
		previousY = y;
	}
	else if (rightMouseDown)
	{
		previousY = y;
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

	loadShaders(resourcesDirectory);
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

	//Matrix4 rotate = projectionMatrixNew * Matrix4::Translate(0, -1.75, 0);




	//Matrix4 projection = Matrix4::Perspective(60.0f,(float) windowWidth /
	//	(float)windowHeight, 0.001f, 10.0f);

	//Matrix4 modelview = Matrix4::Translate(0.0f, 0.0f, -2.0f)//-cameraZoom)
	//	* Matrix4::Scale(1.0f / 128.0f, 1.0f / 128.0f, 1.0f / 128.0f)
	//	* Matrix4::Translate(-128.0f * 0.5f, -128.0f * 0.5f, -128.0f * 0.5f);

	//_modelViewProjectionMatrixNew = projection;

	//emitter->update(1.0f / 30.0f, rotate);
	//glBindBuffer(GL_ARRAY_BUFFER, particleVertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, emitter->getDataCount() * sizeof(float),
	//	emitter->getData(), GL_DYNAMIC_DRAW);
	//particleVertexCount = emitter->getNumberOfActiveParticles();
}

//This is the "heart" of the program, as it is called every 1/60th of a second 
//to update the program state.
void timer(int milliseconds)
{
	glBindTexture(GL_TEXTURE_3D, voxelTexture);
	GLubyte *imgPointer = (GLubyte *)malloc(128 * 128 * 128 * 4);
	for (int i = 0; i < 128 * 128 * 128 * 4; i++)
		imgPointer[i] = 0;

	glGetTexImage(GL_TEXTURE_3D, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgPointer);
	for (int i = 0; i < 128*128*128; i++)
	{
		if (imgPointer[i] > 0)
			std::cout << "Voxel at (" << i << ") is " << (int) imgPointer[i] << ".\n";
	}
	free(imgPointer);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: " << err << "\n";
	}

	//Updating.
	update();

	//Clearing and voxelizing.
	//clearVoxels();
	voxelizeScene();

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