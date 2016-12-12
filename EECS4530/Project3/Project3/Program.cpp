#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include <cmath>

float *readOBJFile(std::string filename, int &nbrTriangles, float * &normalArray);

#define BUFFER_OFFSET(x) ((const void*) (x))

// === ELEMENT DATA

GLuint vertexBuffers[10], arrayBuffers[10], elementBuffers[10];
int nbrTriangles;

// === TOGGLE-ABLE SETTINGS

bool light0On = true, light1On = true, light2On = true;
int materialID = 0;

// === UNIFORM VARIABLES

GLint modelingTransformLocation, projectionTransformLocation, normalTransformLocation;
GLint light0OnLocation, light1OnLocation, light2OnLocation;
GLint eyePositionLocation, materialIDLocation;

// === BEZIER CURVES

const vmath::vec4 bezierP0(+0.0f, +0.0f, +0.5f, +0.0f);
const vmath::vec4 bezierP1(-1.5f, +0.0f, +0.0f, +0.0f);
const vmath::vec4 bezierP2(+1.5f, +0.0f, -0.5f, +0.0f);
const vmath::vec4 bezierP3(+0.0f, +0.0f, +0.5f, +0.0f);

const vmath::mat4 bezierM(
	vmath::vec4(-1.0f, +3.0f, -3.0f, +1.0f),
	vmath::vec4(+3.0f, -6.0f, +3.0f, +0.0f),
	vmath::vec4(-3.0f, +3.0f, +0.0f, +0.0f),
	vmath::vec4(+1.0f, +0.0f, +0.0f, +0.0f)
);
const vmath::mat4 bezierB(bezierP0, bezierP1, bezierP2, bezierP3);

const vmath::mat4 bezierMB = bezierM.transpose() * bezierB.transpose();

vmath::vec4 bezierU(float u) {
	return vmath::vec4(u * u * u, u * u, u, 1);
}

// === GL TIMER AND INTERPOLATION

float interpolant = 0.0f;

void timer(int value) {
	interpolant += 0.01f;
	if (interpolant >= 1.0f) {
		interpolant = 0.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 1);
}

// === GL FUNCTIONS

void init() {
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	// load object
	float *trianglesArray, *normalArray;
	trianglesArray = readOBJFile("marvinDos2ndTry.obj", nbrTriangles, normalArray);
	int trianglesArraySize = nbrTriangles * 3 * 4 * sizeof(float);
	int normalArraySize = nbrTriangles * 3 * 3 * sizeof(float);

	glGenVertexArrays(1, vertexBuffers);
	glBindVertexArray(vertexBuffers[0]);

	glGenBuffers(1, arrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);

	glBufferData(GL_ARRAY_BUFFER, trianglesArraySize + normalArraySize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, trianglesArraySize, trianglesArray);
	glBufferSubData(GL_ARRAY_BUFFER, trianglesArraySize, normalArraySize, normalArray);

	// load program / shaders
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "proj3.vert"},
		{GL_FRAGMENT_SHADER, "proj3.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(trianglesArraySize));

	// load uniform locations
	modelingTransformLocation = glGetUniformLocation(program, "modelingTransform");
	projectionTransformLocation = glGetUniformLocation(program, "projectionTransform");
	normalTransformLocation = glGetUniformLocation(program, "normalTransform");
	light0OnLocation = glGetUniformLocation(program, "light0On");
	light1OnLocation = glGetUniformLocation(program, "light1On");
	light2OnLocation = glGetUniformLocation(program, "light2On");
	eyePositionLocation = glGetUniformLocation(program, "eyePosition");
	materialIDLocation = glGetUniformLocation(program, "materialID");

	// initialize uniform variables
	glUniform1i(materialIDLocation, materialID);
	glUniform1f(light0OnLocation, light0On ? GL_TRUE : GL_FALSE);
	glUniform1f(light1OnLocation, light1On ? GL_TRUE : GL_FALSE);
	glUniform1f(light2OnLocation, light2On ? GL_TRUE : GL_FALSE);

	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// scale + rotate (modelingTransform and normalTransform)
	vmath::mat4 modelingTransform = vmath::scale(0.2f);

	vmath::mat3 normalTransform;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			normalTransform[i][j] = modelingTransform[i][j];

	// translate (modelingTransform only)
	vmath::vec4 bezierPosition = bezierU(interpolant) * bezierMB;
	modelingTransform *= vmath::translate(bezierPosition[0], bezierPosition[1], bezierPosition[2]);

	glUniformMatrix4fv(modelingTransformLocation, 1, GL_FALSE, modelingTransform);
	glUniformMatrix3fv(normalTransformLocation, 1, GL_FALSE, normalTransform);

	// change view
	vmath::mat4 projectionTransform = vmath::scale(1.5f) * vmath::rotate(180.0f, 0.0f, 1.0f, 0.0f) * vmath::rotate(20.0f, 1.0f, 0.0f, 0.0f)
		* vmath::translate(0.0f, 0.0f, 0.3f);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, projectionTransform);

	GLfloat eyePosition[] = { 0.0f, 0.0f, 10.0f };
	glUniform3fv(eyePositionLocation, 1, eyePosition);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

	glFlush();
}

void keypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
		std::cout << "User => Quit" << std::endl;
		exit(0);
		break;
	case '0':
		light0On = !light0On;
		std::cout << "User => Light0: " << (light0On ? "On" : "Off") << std::endl;
		glUniform1f(light0OnLocation, light0On ? GL_TRUE : GL_FALSE);
		glutPostRedisplay();
		break;
	case '1':
		light1On = !light1On;
		std::cout << "User => Light1: " << (light1On ? "On" : "Off") << std::endl;
		glUniform1f(light1OnLocation, light1On ? GL_TRUE : GL_FALSE);
		glutPostRedisplay();
		break;
	case '2':
		light2On = !light2On;
		std::cout << "User => Light2: " << (light2On ? "On" : "Off") << std::endl;
		glUniform1f(light2OnLocation, light2On ? GL_TRUE : GL_FALSE);
		glutPostRedisplay();
		break;
	case '3':
		// material down
		materialID = (materialID != 0 ? materialID - 1 : 23);
		std::cout << "User => Material: " << materialID << std::endl;
		glUniform1i(materialIDLocation, materialID);
		glutPostRedisplay();
		break;
	case '4':
		// material up
		materialID = (materialID != 23 ? materialID + 1 : 0);
		std::cout << "User => Material: " << materialID << std::endl;
		glUniform1i(materialIDLocation, materialID);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argCount, char *argValues[]) {
	glutInit(&argCount, argValues);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Interpolation - Project3 - Zack Ream");

	std::cout << "Initializing...";

	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW." << std::endl;
		exit(EXIT_FAILURE);
	}
	init();

	std::cout << "Done." << std::endl;

	glutKeyboardFunc(keypress);
	glutDisplayFunc(display);
	glutTimerFunc(1000 / 30, timer, 1);
	glutMainLoop();

	return 0;
}
