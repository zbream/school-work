#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
using namespace std;

/*
* We will try an Array Draw with color attributes using openGL.  
* It will use a simple object to test that is hardcoded into the 
* code.  Ideally, it would come from a file.
*
* Author:  Jerry Heuring
* Date:    September 7, 2016
*
* Bugs:
*     
*
* Revisions:
*  Cleaned up code some September 12, 2016
*   
*/
#define BUFFER_OFFSET(x)  ((const void*) (x))

/*
* Arrays to store the indices/names of the Vertex Array Objects and
* Buffers.  Rather than using the books enum approach I've just 
* gone out and made a bunch of them and will use them as needed.  
*
* Not the best choice I'm sure.
*/

GLuint vertexBuffers[10], arrayBuffers[10], elementBuffers[10];
/*
* Global variables
*   The location for the transformation and the current rotation 
*   angle are set up as globals since multiple methods need to 
*   access them.
*/

GLuint transformLocation;
float  rotationAngle;
int    nbrTriangles;

/*
* Timer routine -- when called it increments the angle by 1 degree,
* tells Glut to redraw the screen, and sets a timer for 1/30 of a 
* second later. 
*/
void timer(int value) {
	rotationAngle += 1.0f;
	if (rotationAngle > 360) {
		rotationAngle = rotationAngle - 360;
	}
	glutPostRedisplay();
	glutTimerFunc(1000/30, timer, 1);
}

/*
 * Init will set up our array objects, buffers, and shaders. 
 * The shaders are hard coded right now.  I'm really tempted to 
 * build something into the main program to handle a command line
 * argument for the shaders and pass the result into here to make
 * it easy to change shaders. 
 */
void init() {
	float vertices[] = {
//       x    y    z    w
		0.0, 0.0, 0.0, 1.0,   // The vertices of a unit cube.
		0.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,   
		0.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0
	};

	float vertexColors[] = {
//       r    g    b    a
		0.0, 0.0, 0.0, 1.0,   // The vertex colors of a unit cube.
		0.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,   
		0.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,  
		0.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
	};

	/*
	*  Use the Books code to load in the shaders.
	*/
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "pass2.vert" },
		{ GL_FRAGMENT_SHADER, "pass.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	/*
	 * get the vertices from the routine and set up OpenGL to display them.
	 *
	 * Note:  I've had to add a parameter to the generateCode routine to return the number
	 *        of elements in the array.
	 */
	int nbrOfElements = 0;
	/*
	 * I'm using wide lines so that they are easier to see on the screen.
	 */
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*
	 * Create a vertex array for the buffers, 
     * generate an array buffer to copy the 
	 * vertex data and the color data into.
	 */
	glGenVertexArrays(1, vertexBuffers);  // generates ID for VAO
	glBindVertexArray(vertexBuffers[0]);  // Binds it for use
	glGenBuffers(1, arrayBuffers);        // Generates ID vor Buffer
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]); // Binds it for use
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertexColors), vertexColors);
	nbrTriangles = nbrOfElements / 9;

	/*
	 * Set up variables into the shader programs (Note:  We need the 
	 * shaders loaded and built into a program BEFORE we do this)
	 */
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);

	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE,
			      0, BUFFER_OFFSET(0));
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

	transformLocation = glGetUniformLocation(program, "transform");
	/*
	 * Enable depth testing to remove hidden surfaces.
	 */
	glEnable(GL_DEPTH_TEST);
}

/*
 * display sets the current transformation and draws the elements
 * in the vertex array.  It does clear the color and depth information
 * before it does this.
 */

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vmath::mat4 currentMatrix = vmath::scale(1.0f) * 
	                            vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);
	glUniformMatrix4fv( transformLocation, 1, GL_TRUE, currentMatrix);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0,  9);
	glFlush();
}

/*
 * process a "q" keystroke as a quit 
 */

void keypress(unsigned char keycode, int x, int y) {
	if (keycode == 'q' || keycode == 'Q') {
		exit(0);
	}
}

/*
 * This is the basic main program.  It initializes things and
 * sets up the window.
 */
int main (int argCount, char *argValues[]) {
	glutInit(&argCount, argValues);

	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Attribute Test Code");
	
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewInit();
	init();
	glutKeyboardFunc(keypress);
	glutDisplayFunc(display);
	glutTimerFunc(1000/30, timer, 1);
	glutMainLoop();
	return 0;
}
