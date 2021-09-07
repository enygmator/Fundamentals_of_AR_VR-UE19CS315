#include <gl/glut.h>
#include <random>
#include <windows.h>
#include <cstdlib>

struct GLPoint {
	GLfloat x, y;
};

float randColorf()
{
	return ((float)(rand() % 100)) / 100;
}

float PI = 3.14;

/// <summary>
/// Displays a 3D cube made of polygons
/// </summary>
void draw_scene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	//right face
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	//back face
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();

	//back face
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glEnd();

	//topface
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glEnd();

	//bottom face
	//glColor3f(randColorf(), randColorf(), randColorf());
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glEnd();
}

GLfloat angle = 0;

/// <summary>
/// Each time the angle variable is changed, we call glutPostRedisplay in order to run the displayFunc again
/// </summary>
void timerCallBack_object()
{
	angle += 0.1;

	//Use it as a timer by sleeping 
	Sleep(1);

	//redisplay after the paramters are changed (glutPostRedisplay simply sets a flag, that tells glut to call the display callback on the next loop iteration. It doesn't actually call display)
	glutPostRedisplay();
}

/// <summary>
/// This function displays an object by drawing it and setting the projection matrix (and manipulates it) which we can view
/// </summary>
void display_object()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//ortho graphic view for 3D - sets the orthographics view matrix limits
	glOrtho(-5, 5, -5, 5, -10, 10);

	// rotates the current matrix and the objects in it to change the view. the vector specified is the one along which the rotation takes place
	glRotatef(angle, 0, 1, 0);

	draw_scene();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}


void display_camera_view()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix
	
	// replace current matrix with identity matrix
	glLoadIdentity();
	
	//ortho graphic view for 3D - sets the orthographics view matrix limits
	glOrtho(-5, 5, -5, 5, 10, -10);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the camera towards the point it's looking). The RotateCameraVector should generally be used as a cross product of the (eyePosition - lookingAtPosition) and one of the axis - which in most cases will make sure that the camera is looking at the object and not "roatated" in some random direction. (check youtube)
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);


	draw_scene();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}


float theta = 0;
float camX = 3, camZ = 3;

/// <summary>
/// a callback function that is executed at regular intervals of time registered under 'glutIdleFunc'
/// </summary>
void timerCallBack_camera()
{
	// HINT: the camera is moving on a curcumference of a 2D circle 
	// the points on the circle will be the position of the camera (camx,0,camy)
	theta++;
	float rad = theta * PI / 180;
	camX = 4 * cos(rad);
	camZ = 4 * sin(rad);

	Sleep(60);

	//redisplay after the paramters are changed.
	glutPostRedisplay();
}

void display_rotating_camera_view()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//ortho graphic view for 3D - sets the orthographics view matrix limits
	glOrtho(-5, 5, -5, 5, 10, -10);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the camera towards the point it's looking)
	gluLookAt(camX, 2, camZ, 0, 0, 0, 1, 1, 0);


	draw_scene();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}


int main(int argc, char* argv[])
{
	// Step1:  initialize GLUT using the command line parameters
	glutInit(&argc, argv);

	// Step2: Setup the size of the opengl window, display mode
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(1400, 400);
	glutInitDisplayMode(GLUT_RGB);

	// Step3: creating the window
	glutCreateWindow("Hello 3D polygon!");

	//set window background color
	glClearColor(0, 0, 0, 0);


	/// Step4: defining a callback function for looping into the rasterizer.
	/// Select any one below to run; make sure you enable/disbale the timer function as required
	
	///1. 
	/// If you enable the timerCallBack_object, you will see the object rotating
	///define a timer callback function !ENABLE THIS TO UPDATE THE WINDOW BASED ON A "TIMER"!
	///The mentioned function executes over and over, so use "Sleep(t)" function in order to use it like a timer
	
	//glutDisplayFunc(display_object);
	//glutIdleFunc(timerCallBack_object);


	///2.

	//glutDisplayFunc(display_camera_view);
	

	///3. 
	/// If you enable the timerCallBack_camera, you will see the camera rotating
	/// define a timer callback function !ENABLE THIS TO UPDATE THE WINDOW BASED ON A "TIMER"!
	/// The mentioned function executes over and over, so use "Sleep(t)" function in order to use it like a timer
	
	glutDisplayFunc(display_rotating_camera_view);
	glutIdleFunc(timerCallBack_camera);
	


	// Step5: Telling the GLUT to loop into the callback
	glutMainLoop();
}

