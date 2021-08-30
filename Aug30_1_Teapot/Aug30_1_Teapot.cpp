#include <gl/glut.h>

void displayTeapot();

int main(int argc, char* argv[])
{
	// 1. init GLUT using CLI args
	glutInit(&argc, argv);

	// 2. Setup Size of openGL Window, display Mode
	glutInitWindowSize(640, 640); // width, height
	glutInitWindowPosition(50, 50); // x, y from top left corner
	glutInitDisplayMode(GLUT_RGB);

	// 3. create a window
	glutCreateWindow("Hello Teapot!");

	// 4. calling a call back function for looping into the rasterizer
	glutDisplayFunc(displayTeapot);

	// 5. Telling GLUT to loop into the callback
	glutMainLoop();

	return 0;
}

void displayTeapot()
{
	// 1. Clear the Window
	glClear(GL_COLOR_BUFFER_BIT);

	// 2. Draw the scene
	glutSolidTeapot(0.5);

	// 3. Flush the drawing routines to the window. (pushing drawing onto window)
	glFlush();
}
