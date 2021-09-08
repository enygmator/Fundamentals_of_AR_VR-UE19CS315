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
	GLfloat specular[] = { specularR, specularG, specularB};

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //sets how ambience should work for the material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); //sets how diffuse should work for the material
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); //sets how specular should work for the material
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}


float theta = 0;
float camX = 3, camZ = 3;
float angle = 0;

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

	angle+=0.5;

	Sleep(60);

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
	gluPerspective(80, 1, 0.1, 50);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the camera towards the point it's looking)
	gluLookAt(camX, 2, camZ, 0, 0, 0, 0, 1, 0);

	///Draw the scene

	/*
	
	///1. a cube
	/// Here, a stack is maintained in which all stuff like transformations done only aply to scenes drawn within the matrix that was push/poped
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5); // this scales the scene. without push/pop, everything drawn would have been scaled
		glTranslatef(-1, 0, 0); //translates the scene on x-axis
		draw_scene();
	glPopMatrix();
	
	///2. default gl cube
	glColor3f(0, 1, 1);
	glPushMatrix();
		glTranslatef(1, 0, 0);
		glutSolidCube(1);
	glPopMatrix();

	*/

	
	/// Here, a stack is maintained in which all stuff like transformations done only aply to scenes drawn within the matrix that was push/poped
	glColor3f(0, 1, 1);
	glPushMatrix();
		glTranslatef(-1, 0, 0); //translates the scene on x-axis
		///render A simple Teapot
		//set color
		//set material for teapot
		//parametres: ambient (r,g,b), diffuse (r,g,b), specular (r,g,b), reflectibility/shininess (0-128)
		setMaterial(0.2, 0.2, 0.2, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, 40); //differnet intensities of white light
		glRotatef(angle, 1, 0, 0);
		//draw teapot
		glutSolidTeapot(1);
	glPopMatrix();

	///2. default gl cube
	glColor3f(0, 1, 1);
	glPushMatrix();
		glTranslatef(1, 0, 0);
		glutSolidCube(1);
	glPopMatrix();

	

	// Flush the drawing routines to the window (pushing drawing onto window)
	// glFlush();

	// Insteda of glFlush(), Swap buffers are used when fast rendering of the screen needs to be done
	// they use two beffers which are written to/rendered alternatively
	// Only the modifed parts of one buffer as compared to the previous buffer are actually changed to save CPU/GPU
	//(make sure you have enabled GL_)
	glutSwapBuffers();
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
	/// Select any one below to run; make sure you enable/disbale the timer function as required

	///1. 
	/// If you enable the timerCallBack_camera, you will see the camera rotating
	/// define a timer callback function !ENABLE THIS TO UPDATE THE WINDOW BASED ON A "TIMER"!
	/// The mentioned function executes over and over, so use "Sleep(t)" function in order to use it like a timer

	glutDisplayFunc(display_rotating_camera_view);
	glutIdleFunc(timerCallBack_camera);


	// Step5: Telling the GLUT to loop into the callback
	glutMainLoop();
}

