#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
using namespace std;

float *readOBJFile(string filename, int &nbrTriangles, float * &normalArray);

/*
* This version reads in the cow model including normals and displays it using
* shading.  It is still being worked on to have options to the shading.
*
* Author:  Jerry Heuring
* Date:    November 7, 2014
*
* Bugs:
*     Still checking out the shading.  
*
*     Get rid of dead code
*
*     NormalTransform looks wrong -- disabled right now but needs
*       to be fixed.
*
* Revisions:
*	10/7/2014 -- added a command line option to choose between using
                 glDrawElements and glDrawArray.
*     
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
GLint transformLocation, colorLocation,
lightPositionLocation, ambientLightColorLocation,
diffuseLightColorLocation, specularLightColorLocation,
specularPowerLocation, eyePositionLocation, normalTransformLocation, materialAmbientLocation, materialDiffuseLocation, materialEmissiveLocation, materialSpecularLocation, materialShininessLocation;
float rotationAngle;
bool elements;
int nbrTriangles;

/*
* Timer routine -- when called it increments the angle by 1 degree,
* tells Glut to redraw the screen, and sets a timer for 1/30 of a 
* second later. 
*/
void timer(int value) {
	rotationAngle += 1.0f;
	glutPostRedisplay();
	glutTimerFunc(1000/30, timer, 1);
}

/*
* Init will set up our array objects, buffers, and shaders. 
* The shaders are hard coded right now.  I'm really tempted to 
* build something into the main program to handle a command line
* argument for the shaders and pass the result into here to make
* it easy to change shaders. 
*
* 
*/
void init() {

	/*
	* our data is static so that it doesn't disappear with the stack.
	*/



	float *fileTriangles;
	float *normalArray;
		/*
		 * Read in the OBJ file with the normal data.  The function returns a pointer to the
		 * file triangle data, and modifies nbrTriangles, and normalArray to have appropriate
		 * values.
		 */
		fileTriangles = readOBJFile("triangulatedCowDos.obj", nbrTriangles, normalArray);
	/*
	* I'm using wide lines so that they are easier to see on the screen.
	* In addition, this version fills in the polygons rather than leaving it
	* as lines.
	*/
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*
	* Create a vertex array for the buffers, generate an array buffer to copy the 
	* vertex data and the color data into.
	*/


	glGenVertexArrays(1, vertexBuffers);
	glBindVertexArray(vertexBuffers[0]);
	glGenBuffers(1, arrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER,
		nbrTriangles * 3 * 4 * sizeof(float) + nbrTriangles * 3 * 3 *sizeof(float), 
		NULL ,GL_STATIC_DRAW);



	glBufferSubData(GL_ARRAY_BUFFER, 0, nbrTriangles*3*4*sizeof(float),fileTriangles);
	glBufferSubData(GL_ARRAY_BUFFER, nbrTriangles*3*4*sizeof(float), 
		nbrTriangles*3*3*sizeof(float), normalArray);

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
	* shaders loaded and built into a program before we do this)
	*/
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(nbrTriangles*3*4*sizeof(float)));


	transformLocation = glGetUniformLocation(program, "transform");
	colorLocation = glGetUniformLocation(program, "cowcolor");
	lightPositionLocation = glGetUniformLocation(program, "lightPosition");
	ambientLightColorLocation = glGetUniformLocation(program, "ambientLightColor");
	diffuseLightColorLocation = glGetUniformLocation(program, "diffuseLightColor");
	specularLightColorLocation = glGetUniformLocation(program, "specularLightColor");
	specularPowerLocation = glGetUniformLocation(program, "specularPower");
	eyePositionLocation = glGetUniformLocation(program, "eyeLocation");
	normalTransformLocation = glGetUniformLocation(program, "normalTransform");

	materialAmbientLocation = glGetUniformLocation(program, "material.ambient");
	materialSpecularLocation = glGetUniformLocation(program, "material.specular");
	materialDiffuseLocation = glGetUniformLocation(program, "material.diffuse");
	materialShininessLocation = glGetUniformLocation(program, "material.shininess");
	materialEmissiveLocation = glGetUniformLocation(program, "material.emissive");

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

	static GLfloat red[4] = {1.0f, 0.0f, 0.0f, 1.0f},
		white[4] = {1.0f, 1.0f, 1.0f, 1.0f},
		blue[4] = {0.0f, 0.0f, 1.0f, 1.0f};

	GLfloat lightPosition[] = {0.0f, 0.0f, 10.0f};
	GLfloat diffuseLightColor[] = {0.5f, 0.5f, 0.5f};
	GLfloat ambientLightColor[] = {0.3f, 0.3f, 0.3f};
	GLfloat eyePosition[] = {0.0f, 0.0f, 10.0f};
	GLfloat specularLightColor[] = {0.5f, 0.5f, 0.5f};
	GLfloat specularPower[] = {64.0f};
	GLfloat normalTransformation[3][3];
	vmath::mat4 normalTrans;

	vmath::perspective(60.0f, 1.0f, 0.01f, 100.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vmath::mat4 currentMatrix = vmath::scale(0.08f) * 
                  vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);

	/*
	 * m seems to be wrong.  Need to go back and make sure I've got these in the 
	 * right positions.
	 */
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			normalTransformation[i][j] = currentMatrix[i][j];
		}
	}

	glUniformMatrix4fv( transformLocation, 1, GL_TRUE, currentMatrix);
	glUniformMatrix3fv( normalTransformLocation, 1, GL_TRUE, 
		(const GLfloat *)normalTransformation);
	glUniform4fv(colorLocation, 1, white);
	glUniform3fv(lightPositionLocation, 1, lightPosition);
	glUniform3fv(diffuseLightColorLocation, 1, diffuseLightColor);
	glUniform3fv(ambientLightColorLocation, 1, (const GLfloat *)&ambientLightColor);
	glUniform3fv(eyePositionLocation, 1, eyePosition);
	glUniform3fv(specularLightColorLocation, 1, specularLightColor);
	glUniform1fv(specularPowerLocation, 1, specularPower);

	// Pick a group for this material -- copper
	GLfloat ambient[] = { 0.19225f, 0.0735f, 0.0225f };
	GLfloat diffuse[] = { 0.7038f, 0.27048f, 0.0828f };
	GLfloat specular[] = { 0.256777f, 0.137622f, 0.086014f };
	GLfloat shininess = 12.8f;

	glUniform3fv(materialDiffuseLocation, 1, diffuse);
	glUniform3fv(materialAmbientLocation, 1, ambient);
	glUniform3fv(materialSpecularLocation, 1, specular);
	glUniform1fv(materialShininessLocation, 1, &shininess);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles*3);


	vmath::mat4 translation(vmath::vec4(1.0f, 0.0f, 0.0f, 5.00f), 
		                    vmath::vec4(0.0f, 1.0f, 0.0f, 5.00f),
							vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	currentMatrix =  translation * vmath::scale(0.08f) * vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);

	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);
	glUniform4fv(colorLocation, 1,  red);

	// Pearl material
	GLfloat ambient2[] = { 0.25f, 0.20725f, 0.20725f };
	GLfloat diffuse2[] = { 1.0f, 0.829f, 0.829f };
	GLfloat specular2[] = { 0.296648f, 0.296648f, 0.296648f };
	GLfloat shininess2 = (128.0f*0.088f);

	glUniform3fv(materialDiffuseLocation, 1, diffuse2);
	glUniform3fv(materialAmbientLocation, 1, ambient2);
	glUniform3fv(materialSpecularLocation, 1, specular2);
	glUniform1fv(materialShininessLocation, 1, &shininess2);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles*3);

	vmath::mat4 translation2(vmath::vec4(1.0f, 0.0f, 0.0f, -5.00f), 
		                    vmath::vec4(0.0f, 1.0f, 0.0f, 5.00f),
							vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    currentMatrix = translation2 * vmath::scale(0.08f) * vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);
	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);
	glUniform4fv(colorLocation, 1, blue);
	// silver
	GLfloat ambient3[] = { 0.19225f, 0.19225f, 0.19225f };
	GLfloat diffuse3[] = { 0.50754f, 0.50754f, 0.50754f };
	GLfloat specular3[] = { 0.508273f, 0.508273f, 0.508273f };
	GLfloat shininess3 = (128.0f * 0.4f);

	glUniform3fv(materialDiffuseLocation, 1, diffuse3);
	glUniform3fv(materialAmbientLocation, 1, ambient3);
	glUniform3fv(materialSpecularLocation, 1, specular3);
	glUniform1fv(materialShininessLocation, 1, &shininess3);

	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles*3);

	glFlush();
}

/*
* This is the basic main program.  It initializes things and
* sets up the window.
*/
int main (int argCount, char *argValues[]) {
	glutInit(&argCount, argValues);

	// Check for a flag to determine if we are using glDrawElements or 
	// glDrawArray.  I'm looking for either --elements or --array.
	// The default is the elements.
	elements = true;
	for (int argNbr=1; argNbr < argCount; argNbr++) {
		if (argValues[argNbr] == "--elements") {
			cout << "Drawing using glDrawElements" << endl;
			elements = true;
		} else if (argValues[argNbr] == "--array") {
			elements = false;
		}
	}
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(500, 500);
	glutCreateWindow("Icosahedron Sample");

	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000/30, timer, 1);
	glutMainLoop();
	return 0;
}
