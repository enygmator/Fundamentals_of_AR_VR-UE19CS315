#include <gl/glut.h>

void display_point();
void display_triangle();
void display_polygon();

int main(int argc, char* argv[])
{
	// 1. init GLUT using CLI args
	glutInit(&argc, argv);

	// 2. Setup Size of openGL Window, display Mode
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_RGB);

	// 3. create a window
	glutCreateWindow("Hello Teapot!");

	// Set window background color
	glClearColor(150, 150, 150, 255);

	// 4. calling a call back function for looping into the rasterizer
	// Uncomment any one of the below to view the result
	
	//glutDisplayFunc(display_point);
	//glutDisplayFunc(display_triangle);
	glutDisplayFunc(display_polygon);


	// 5. Setup projection Window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 640); //Set the coordinates of the "window" inside of the Graphics through which you will be able to see the objects in front via orthogonal projection
	glPointSize(10);

	// 6. Telling GLUT to loop into the callback
	glutMainLoop();

	return 0;
}

/// <summary>
/// Displays a single point
/// </summary>
void display_point()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(320, 320);
	glEnd();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}

/// <summary>
/// Displays a Triangle
/// </summary>
void display_triangle()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(320, 10);
	glVertex2i(10, 206);
	glVertex2d(10, 412);
	glEnd();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}

/// <summary>
/// Displays a Polygon
/// </summary>
void display_polygon()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(320, 10);
	glVertex2i(10, 206);
	glVertex2d(10, 412);
	glVertex2d(300, 630);
	glVertex2d(620, 412);
	glVertex2d(630, 206);
	glEnd();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}
