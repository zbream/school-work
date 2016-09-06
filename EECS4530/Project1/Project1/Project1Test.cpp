#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
using namespace std;

/*
* This is an example of drawing a cone as an intro to OpenGL.
*
* Author:  Jerry Heuring
* Date:    October 6, 2014
*
* Bugs:
*     
*
* Revisions:
*   8/24/2016 -- Changed to handle call for generateCone.  Removed some
*                "dead" code as well.
*     
*
*/
#define BUFFER_OFFSET(x)  ((const void*) (x))

float * generateCone(float baseRadius, float height, float topRadius, int nbrOfSteps, int &nbrOfValues);
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
bool   elements;
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
	/*
	 * get the vertices from the routine and set up OpenGL to display them.
	 *
	 * Note:  I've had to add a parameter to the generateCode routine to return the number
	 *        of elements in the array.
	 */
	int nbrOfElements = 0;
	float * vertices = generateCone(0.5, 0.7, 0.0, 10, nbrOfElements);
  
	/*
	* I'm using wide lines so that they are easier to see on the screen.
	*/
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	 * Create a vertex array for the buffers, 
     * generate an array buffer to copy the 
	 * vertex data and the color data into.
	 */

	glGenVertexArrays(1, vertexBuffers);  // generates ID for VAO
	glBindVertexArray(vertexBuffers[0]);  // Binds it for use
	glGenBuffers(1, arrayBuffers);        // Generates ID vor Buffer
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]); // Binds it for use
	glBufferData(GL_ARRAY_BUFFER, nbrOfElements * sizeof(float), vertices, GL_STATIC_DRAW);
	nbrTriangles = nbrOfElements / 9;

	/*
	 *  Use the Books code to load in the shaders.
	 */
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "pass.vert"},
		{GL_FRAGMENT_SHADER, "pass.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	/*
	 * Set up variables into the shader programs (Note:  We need the 
	 * shaders loaded and built into a program BEFORE we do this)
	 */
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE,
			      0, BUFFER_OFFSET(0));

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
	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles*3);
	glFlush();
}

/*
 * This is the basic main program.  It initializes things and
 * sets up the window.
 */
int main (int argCount, char *argValues[]) {
	glutInit(&argCount, argValues);

	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cone Test Code");
	
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000/30, timer, 1);
	glutMainLoop();
	return 0;
}
