//Including the necessary files.
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
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

float fov = 90;

GLuint particleVertexArray, particleVertexBuffer;

OpenGLProgram *particleProgram, *boneMeshProgram, *skinMeshProgram,
*diffuseProgram;
Material *boneMeshMaterial, *skinMeshMaterial, *floorMaterial;
Camera *camera;
AssetManager *manager;
Armature *arm;

Quaternion lastFrameLerp;
Quaternion lastFrameSlerp;

Transform::TransformSpace space = Transform::Local;

StaticMesh *boneMesh, *skinMesh, *floorMesh;
ParticleEmitter *emitter;
Texture *smokeTexture, *particleTexture, *targetTexture, *floorTexture;
GLuint texture, texture2, texture3, floorTexturePointer;

int texUnit = 0;

float rotation = 0.0f;

Matrix4 _modelViewProjectionMatrixNew;
Matrix3 _normalMatrixNew;
int vertexCount, particleVertexCount;

std::clock_t updateClock;

bool loadShaders(std::string resourcesDirectory)
{
	//Particle program setup.
	particleProgram = 
		new OpenGLProgram(resourcesDirectory + "ParticleShader.vsh",
			resourcesDirectory + "ParticleShader.fsh");

	//Missile program setup.
	boneMeshProgram = 
		new OpenGLProgram(resourcesDirectory + "DefaultShader.vsh",
		resourcesDirectory + "DefaultShader.fsh");

	skinMeshProgram = 
		new OpenGLProgram(resourcesDirectory + "SkinnedMeshShader.vsh",
		resourcesDirectory + "SkinnedMeshShader.fsh");
	skinMeshProgram->addUniform("worldToEyeMatrix");
	skinMeshProgram->addUniform("projectionMatrix");

	diffuseProgram = new OpenGLProgram(resourcesDirectory + "Diffuse.vsh",
		resourcesDirectory + "Diffuse.fsh");

	//Setting up the material of the boneMesh.
	boneMeshMaterial = new Material();
	boneMeshMaterial->setProgram(boneMeshProgram);
	boneMeshMaterial->setTexture("diffuse", targetTexture);

	skinMeshMaterial = new Material();
	skinMeshMaterial->setProgram(skinMeshProgram);

	floorMaterial = new Material();
	floorMaterial->setProgram(diffuseProgram);
	floorMaterial->setTexture("diffuse", floorTexture);

	return true;
}

void setupGL(std::string resourcesDirectory)
{
	using namespace GraphicsEngine;

	//StaticMesh Creation.
	manager = new AssetManager();
	manager->loadFile(resourcesDirectory + "Bone.dae");
	manager->loadFile(resourcesDirectory + "Armature.dae");
	manager->loadFile(resourcesDirectory + "Floor.dae");
	boneMesh = manager->getStaticMesh("Bone");
	skinMesh = manager->getStaticMesh("Skin");
	floorMesh = manager->getStaticMesh("Floor");
	boneMesh->setMaterial(boneMeshMaterial);
	skinMesh->setMaterial(skinMeshMaterial);
	floorMesh->setMaterial(floorMaterial);
	arm = manager->getArmature("Armature");

	//Camera Creation.
	camera = new Camera("MainCamera");
	camera->getTransform()->setPosition(Vector3(0, 5, 10));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	smokeTexture = new Texture(resourcesDirectory + "Smoke.tga");
	smokeTexture->setTextureType(DiffuseTexture);
	particleTexture = new Texture(resourcesDirectory + "Particle.tga");
	particleTexture->setTextureType(DiffuseTexture);
	targetTexture = new Texture(resourcesDirectory + "Target.tga");
	targetTexture->setTextureType(DiffuseTexture);
	floorTexture = new Texture(resourcesDirectory + "ConcreteTileFloor.tga");
	floorTexture->setTextureType(DiffuseTexture);

	GLfloat maxAniso;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);

	std::cout << "Max Aniso: " << maxAniso << "\n";

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		smokeTexture->getWidth(), smokeTexture->getHeight(), 0,
		GL_BGRA, GL_UNSIGNED_BYTE, smokeTexture->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		particleTexture->getWidth(), particleTexture->getHeight(), 0,
		GL_BGRA, GL_UNSIGNED_BYTE, particleTexture->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		targetTexture->getWidth(), targetTexture->getHeight(), 0,
		GL_BGRA, GL_UNSIGNED_BYTE, targetTexture->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	glGenTextures(1, &floorTexturePointer);
	glBindTexture(GL_TEXTURE_2D, floorTexturePointer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		floorTexture->getWidth(), floorTexture->getHeight(), 0,
		GL_BGRA, GL_UNSIGNED_BYTE, floorTexture->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting the texture parameters.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//float *data = boneMesh->getVertexData()->getData();
	//for(int i = 0; i < boneMesh->getVertexData()->getDataCount(); i++)
	//    std::cout << data[i] << "\n";

	//ParticleGravity pg;

	//Vector3 gravity = Vector3(1, 2, 3);
	//pg.setGravity(gravity);

	////    std::cout << "(" << gravity.x << ", " << gravity.y << ", " << gravity.z
	////              << ")\n";

	//pg.updateForce(new Particle(), 1);

	////    std::cout << "(" << gravity.x << ", " << gravity.y << ", " << gravity.z
	////    << ")\n";

	////sceneManager->createRenderableObject("boneMeshObject", "");

	//emitter = new ParticleEmitter(750);
	//emitter->setPositionAndVariance(Vector3(0, 0, -2), Vector3(0.005, .005, 0.005));
	//emitter->setMinAndMaxAngle(Vector2(0, 179), Vector2(360, 180));
	//emitter->setSpeedAndVariance(5, .1);
	//emitter->setStartColorAndVariance(Vector4(.75, .75, .75, 1),
	//	Vector4(0, 0, 0, 0));
	//emitter->setEndColorAndVariance(Vector4(.75, .75, .75, 0),
	//	Vector4(0, 0, 0, 0));
	//emitter->setStartSizeAndVariance(50, 0);
	//emitter->setEndSizeAndVariance(75, 0);
	//emitter->setLifetimeAndVariance(1.5, .75);
	//emitter->setEmissionRate(1);
	//emitter->setEmissionTime(0);

	////Adding forces to the emitter.
	//emitter->addForce(new ParticleDrag(0.5, 1));

	//emitter->start();

	////Particle VAO and VBO setup.
	//glGenVertexArrays(1, &particleVertexArray);
	//glBindVertexArray(particleVertexArray);

	//glGenBuffers(1, &particleVertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, particleVertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, emitter->getDataCount() * sizeof(float),
	//	emitter->getData(), GL_DYNAMIC_DRAW);

	//glEnableVertexAttribArray(particleProgram->getAttributeID("position"));
	//glVertexAttribPointer(particleProgram->getAttributeID("position"),
	//	3, GL_FLOAT, GL_FALSE,
	//	8 * sizeof(float), BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(particleProgram->getAttributeID("color"));
	//glVertexAttribPointer(particleProgram->getAttributeID("color"),
	//	4, GL_FLOAT, GL_FALSE,
	//	8 * sizeof(float), BUFFER_OFFSET(12));
	//glEnableVertexAttribArray(particleProgram->getAttributeID("size"));
	//glVertexAttribPointer(particleProgram->getAttributeID("size"),
	//	1, GL_FLOAT, GL_FALSE,
	//	8 * sizeof(float), BUFFER_OFFSET(28));

	////Unbinding the current vertex array.
	//glBindVertexArray(0);
}

//This method displays the objects sent to the graphics card.
void display()
{
	//Clearing the scene.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Quaternion q1 = Quaternion(-90, Vector3(0, 0, 1));
	Quaternion q2 = Quaternion(90, Vector3(0, 0, 1));

	if (rotation >= 1.0f || rotation <= -1.0)
		rotation = 0.0f;

	Quaternion mixed = Quaternion::Slerp(q1, q2, rotation);
	Quaternion lerpMixed = Quaternion::Nlerp(q1, q2, rotation);

	//camera->getTransform()->setRotation(mixed);

	lastFrameLerp = lerpMixed;
	lastFrameSlerp = mixed;


	//--------RigidBody Testing!--------

	/*Matrix3 iitWorld = Matrix3();
	Matrix3 iitBody = Matrix3(1, 2, 3,
		4, 5.5, 6,
		7, 8, 7);
	Quaternion q = lerpMixed;

	RigidBody body = RigidBody();
	body.transformInertiaTensor(iitWorld, q, iitBody);

	std::cout << "iitBody Version:\n";
	iitBody.print();
	std::cout << "iitWorld Book Version:\n";
	iitWorld.print();

	body._transformInertiaTensor(iitWorld, q, iitBody, Matrix4(q));

	std::cout << "iitWorld My Version:\n";
	iitWorld.print();*/


	//    std::cout << "\t\t\tW: " << mixed.w << "\tX: " << mixed.x << "\tY: "
	//    << mixed.y << "\tZ: " << mixed.z << "\tLength:\t" << mixed.length() << "\n";

	//    std::cout << "Normalized:\tW: " << mixed.w << "\tX: " << mixed.x << "\tY: "
	//    << mixed.y << "\tZ: " << mixed.z << "\tLength:\t" << mixed.length() << "\n";

	//    _modelViewProjectionMatrixNew;
	//
	//    glBindVertexArrayOES(particleVertexArray);
	//    
	//    glDepthMask(GL_FALSE);
	//    glUseProgram(particleProgram->getProgramID());
	//    glActiveTexture(GL_TEXTURE0);
	//    glBindTexture(GL_TEXTURE_2D, texture3);
	//    
	//    glUniform1i(glGetUniformLocation(particleProgram->getProgramID(), "diffuse"), texUnit);
	//    glUniformMatrix4fv(particleProgram->getUniformID("worldToEyeMatrix"),
	//                       1, GL_FALSE, _modelViewProjectionMatrixNew);
	//    glDrawArrays(GL_POINTS, 0, particleVertexCount);
	//    glDepthMask(GL_TRUE);

	arm->getBone("Bone1")->getLocalTransform().setRotation(lerpMixed);
	arm->getBone("Bone2")->getLocalTransform().setRotation(lerpMixed);
	arm->getBone("Bone3")->getLocalTransform().setRotation(lerpMixed);
	arm->getBone("Bone4")->getLocalTransform().setRotation(lerpMixed);

	arm->update();

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

	//Drawing the skin.
	glUseProgram(skinMesh->getMaterial()->getProgram()->getProgramID());
	glUniformMatrix4fv(skinMeshProgram->getUniformID("projectionMatrix"),
		1, GL_FALSE, _modelViewProjectionMatrixNew);

	glUniformMatrix4fv(skinMeshProgram->getUniformID("worldToEyeMatrix"),
		4, GL_FALSE, arm->getMatrices()[0]);

	glBindVertexArray(skinMesh->getVertexData()->getVertexDataPointer());
	glDrawArrays(GL_TRIANGLES, 0, skinMesh->getVertexData()->getVertexCount());

	//Drawing each bone.
	glUseProgram(boneMesh->getMaterial()->getProgram()->getProgramID());
	std::vector<Bone *> bones = arm->getBones();
	for (Bone *bone : bones)
	{
		Matrix4 targetMatrix = _modelViewProjectionMatrixNew *
			bone->getGlobalTransform();

		glUniformMatrix4fv(boneMeshProgram->getUniformID("worldToEyeMatrix"),
			1, GL_FALSE, targetMatrix);

		glBindVertexArray(boneMesh->getVertexData()->getVertexDataPointer());
		glDrawArrays(GL_TRIANGLES, 0, boneMesh->getVertexData()->getVertexCount());
	}

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
		std::cout << "X Change:\t" << (float)(x - previousX);
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

	//Setting the background color.
	glClearColor(1, 0, 0, 1);

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

	//Creating a new projection view based on the changed width and height.
	//mat4 projection = Perspective(sceneManager->getCurrentCamera()->getFOV(),
	//	(float)width / (float)height, 0.25, 1000.0);

	//Updating the viewport.
	glViewport(0, 0, width, height);
}

void update()
{
	float aspect = (float)windowWidth / (float)windowHeight;
	Matrix4 projectionMatrixNew = Matrix4::Perspective(fov, aspect, 0.1f, 200.0f);

	Matrix4 modelViewMatrixNew = camera->getTransform()->getInverseTransform();

	_normalMatrixNew = Matrix3(modelViewMatrixNew).invert().transpose();

	_modelViewProjectionMatrixNew = projectionMatrixNew * modelViewMatrixNew;

	Matrix4 rotate = projectionMatrixNew * Matrix4::Translate(0, -1.75, 0);

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
	//Updating.
	update();

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