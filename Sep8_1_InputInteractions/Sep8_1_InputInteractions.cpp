#include <gl/glut.h>
#include <random>
#include <windows.h>
#include <cstdlib>
#include <iostream>

using namespace std;

struct GLPoint {
	GLfloat x, y;
};

float randColorf()
{
	return ((float)(rand() % 100)) / 100;
}

float PI = 3.14;

/// <summary>
/// ambient (r,g,b), diffuse (r,g,b), specular (r,g,b), reflectibility/shininess (0-128)
/// </summary>
void setMaterial(
	GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
	GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
	GLfloat specularR, GLfloat specularG, GLfloat specularB,
	int shine)
{
	///create "vectors" from the values for the light
	GLfloat ambient[] = { ambientR, ambientG, ambientB };
	GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
	GLfloat specular[] = { specularR, specularG, specularB };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //sets how ambience should work for the material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); //sets how diffuse should work for the material
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); //sets how specular should work for the material
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

float zoom = 4;
int axisX = 1, axisY = 0, axisZ = 0;
float tX = 0, tY = 0, tZ = 0;
float angle = 0;

/// <summary>
/// a callback function that is executed at regular intervals of time registered under 'glutIdleFunc'
/// </summary>
void timerCallBack_camera()
{
	angle += 0.5;

	Sleep(10);

	//redisplay after the paramters are changed.
	glutPostRedisplay();
}

void display_rotating_camera_view()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //you need to clear GL_DEPTH_BUFFER_BIT when depth is enabled

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//perspective graphic view for 3D - makes distant objects smaller. Includes FOV, aspect ratio, near, far [near and far are distances FROM the camera to the zNearPlane and zFarPlane]
	gluPerspective(80, 1, 0.5, 50);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the camera towards the point it's looking)
	gluLookAt(zoom, zoom, zoom, 0, 0, 0, 0, 1, 0);


	glColor3f(0, 1, 1);
	//glRotatef(angle, axisX, axisY, axisZ);
	glTranslatef(tX, tY, tZ);	
	//parametres: ambient (r,g,b), diffuse (r,g,b), specular (r,g,b), reflectibility/shininess (0-128)
	setMaterial(0.2, 0.2, 0.2, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, 40); //differnet intensities of white light
	//draw teapot
	glutSolidTeapot(1);


	// Insteda of glFlush(), Swap buffers are used when fast rendering of the screen needs to be done
	// they use two beffers which are written to/rendered alternatively
	// Only the modifed parts of one buffer as compared to the previous buffer are actually changed to save CPU/GPU
	//(make sure you have enabled GL_)
	glutSwapBuffers();
}

/// <summary>
/// 
/// </summary>
/// <param name="key">The key that was pressed on the keyboard</param>
/// <param name="x">Mouse pointer position x</param>
/// <param name="y">Mouse pointer position y</param>
void customKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-': zoom++; break;
	case '=': zoom--; break;
	case 'x': axisX = 1, axisY = 0, axisZ = 0;break;
	case 'y': axisX = 0, axisY = 1, axisZ = 0;break;
	case 'z': axisX = 0, axisY = 0, axisZ = 1;break;
	case 'q': tZ -= 0.2; break;
	case 'e': tZ += 0.2; break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN: tY -= 0.2; break;
	case GLUT_KEY_UP: tY += 0.2; break;
	case GLUT_KEY_LEFT:tX -= 0.2; break;
	case GLUT_KEY_RIGHT: tX += 0.2; break;
	default:
		break;
	}

	glutPostRedisplay();
}

void customMouseFunc(int button, int state, int x, int y)
{
	switch (button)
	{

	case GLUT_MIDDLE_BUTTON:
		switch (state)
		{
		case GLUT_UP: break;
		case GLUT_DOWN: break;
		default:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON: 
		switch (state)
		{
		case GLUT_UP:  break;
		case GLUT_DOWN: tZ += 0.2; break;
		default:
			break;
		}
		break;

	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_UP: break;
		case GLUT_DOWN: tZ -= 0.2; break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	
	glutPostRedisplay();
}

void customMotionFunc(int x, int y)
{
	cout << x << ", " << y << endl;
}

int main(int argc, char* argv[])
{
	// Step1:  initialize GLUT using the command line parameters
	glutInit(&argc, argv);

	// Step2: Setup the size of the opengl window, display mode
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(1400, 400);
	//here we add depth buffer to the rgb buffer display
	//we also enable double buffering
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GL_DOUBLE);

	// Step3: creating the window
	glutCreateWindow("Open GL Lighting");

	//set up lighting for the scene
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//only enabling this

	//This tells opengl to allow us to change the color of the material (without this, the lighting - GL_LIGHT0 - will result in a grayscale view)
	glEnable(GL_COLOR_MATERIAL);

	//enable depth test - do depth comparisons and update the depth buffer
	glEnable(GL_DEPTH_TEST);

	//set window background color
	glClearColor(0, 0, 0, 0);


	/// Step4: defining a callback function for looping into the rasterizer.
	glutDisplayFunc(display_rotating_camera_view);

	/// If you enable the timerCallBack_camera, you will see the camera rotating
	/// define a "timer" callback function which is called over and voer again
	glutIdleFunc(timerCallBack_camera);

	//define callback for keyboard interactions
	glutKeyboardFunc(customKeys);
	glutSpecialFunc(specialKeys);

	// define a callback for mouse event
	glutMouseFunc(customMouseFunc);

	// defining callback for mouse movement
	glutMotionFunc(customMotionFunc);

	// Step5: Telling the GLUT to loop into the callback
	glutMainLoop();
}

