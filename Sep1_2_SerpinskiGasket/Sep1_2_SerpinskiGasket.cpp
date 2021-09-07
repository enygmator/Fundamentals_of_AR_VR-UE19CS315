#include <gl/glut.h>
#include <random>

float randColorf()
{
	return ((float)(rand() % 100)) / 100;
}

void display();
void SerpinskiGasket();

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
	glClearColor(0, 0, 0, 0);

	// 4. calling a call back function for looping into the rasterizer

	glutDisplayFunc(SerpinskiGasket);


	// 5. Setup projection Window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 640); //Set the coordinates of the "window" inside of the Graphics through which you will be able to see the objects in front via orthogonal projection
	glPointSize(2);

	// 6. Telling GLUT to loop into the callback
	glutMainLoop();

	return 0;
}

struct GLPoint
{
	GLfloat x, y;
};

void drawPoint(GLPoint point)
{
	glBegin(GL_POINTS);
		glColor3f(randColorf(), randColorf(), randColorf());
		glVertex2f(point.x, point.y);
	glEnd();
}

void SerpinskiGasket()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Select vertices that will form a triangle
	GLPoint T[3] = { {10, 10}, {600, 10}, {300, 600} };

	//select one point randomly
	int index = rand() % 3;

	// Draw the point as a dot
	GLPoint point = T[index];
	drawPoint(point);

	// loop into 5000 iterations
	for (int i = 0; i < 500000; i++)
	{
		// randomly select a vertex in the triangle
		// we'll just select a vertex in this case
		index = rand() % 3;

		// find the midpoint
		// switch the new point to the inital point for next iteration
		point.x = (point.x + T[index].x) / 2;
		point.y = (point.y + T[index].y) / 2;
		

		// Draw the midpoint
		drawPoint(point);
		
	}
	

	// Flush contents to screen
	glFlush();
}

/// <summary>
/// Displays a Polygon (Hexagon) using Triangles
/// </summary>
void display()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 255.0, 0.0);
	glVertex2d(320, 10);
	glVertex2i(10, 206);
	glVertex2d(620, 206);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 255.0);
	glVertex2d(620, 206);
	glVertex2i(10, 206);
	glVertex2d(10, 412);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(255.0, 0.0, 0.0);
	glVertex2d(620, 412);
	glVertex2i(620, 206);
	glVertex2d(10, 412);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 150.0, 150.0);
	glVertex2d(320, 630);
	glVertex2i(620, 412);
	glVertex2d(10, 412);
	glEnd();

	// Flush the drawing routines to the window (pushing drawing onto window)
	glFlush();
}
