// Zack Ream
// EECS 4530 - Fall 2016

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"

float *readOBJFile(std::string filename, int &nbrTriangles, float * &normalArray);

#define BUFFER_OFFSET(x) ((const void*) (x))

// === GLOBALS

GLuint vertexBuffers[10], arrayBuffers[10], elementBuffers[10];

float rotationAngle;
int nbrTriangles;

GLint transformLocation, colorLocation, lightPositionLocation,
	ambientLightColorLocation, diffuseLightColorLocation, specularLightColorLocation, specularPowerLocation, eyePositionLocation, normalTransformLocation,
	materialAmbientLocation, materialDiffuseLocation, materialEmissiveLocation, materialSpecularLocation, materialShininessLocation;

// === GL FUNCTIONS

void timer(int value) {
	rotationAngle += 2.0f;
	if (rotationAngle >= 360) {
		rotationAngle = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 1);
}

void init() {
	float *trianglesArray;
	float *normalArray;

	trianglesArray = readOBJFile("triangulatedCowDos.obj", nbrTriangles, normalArray);

	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glGenVertexArrays(1, vertexBuffers);
	glBindVertexArray(vertexBuffers[0]);

	glGenBuffers(1, arrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);

	glBufferData(GL_ARRAY_BUFFER, nbrTriangles * 3 * 4 * sizeof(float) + nbrTriangles * 3 * 3 * sizeof(float), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, nbrTriangles * 3 * 4 * sizeof(float), trianglesArray);
	glBufferSubData(GL_ARRAY_BUFFER, nbrTriangles * 3 * 4 * sizeof(float), nbrTriangles * 3 * 3 * sizeof(float), normalArray);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "pass.vert"},
		{GL_FRAGMENT_SHADER, "pass.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(nbrTriangles * 3 * 4 * sizeof(float)));

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

	glEnable(GL_DEPTH_TEST);
}

void display() {
	static GLfloat 
		red[4] = { 1.0f, 0.0f, 0.0f, 1.0f },
		white[4] = { 1.0f, 1.0f, 1.0f, 1.0f },
		blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	GLfloat lightPosition[] = { 0.0f, 0.0f, 10.0f };
	GLfloat diffuseLightColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat ambientLightColor[] = { 0.3f, 0.3f, 0.3f };
	GLfloat eyePosition[] = { 0.0f, 0.0f, 10.0f };
	GLfloat specularLightColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat specularPower[] = { 64.0f };
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

	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);
	glUniformMatrix3fv(normalTransformLocation, 1, GL_TRUE, (const GLfloat *)normalTransformation);
	glUniform4fv(colorLocation, 1, white);
	glUniform3fv(lightPositionLocation, 1, lightPosition);
	glUniform3fv(diffuseLightColorLocation, 1, diffuseLightColor);
	glUniform3fv(ambientLightColorLocation, 1, (const GLfloat *)&ambientLightColor);
	glUniform3fv(eyePositionLocation, 1, eyePosition);
	glUniform3fv(specularLightColorLocation, 1, specularLightColor);
	glUniform1fv(specularPowerLocation, 1, specularPower);

	// Pearl material
	GLfloat ambient[] = { 0.25f, 0.20725f, 0.20725f };
	GLfloat diffuse[] = { 1.0f, 0.829f, 0.829f };
	GLfloat specular[] = { 0.296648f, 0.296648f, 0.296648f };
	GLfloat shininess = (128.0f*0.088f);
	glUniform3fv(materialDiffuseLocation, 1, diffuse);
	glUniform3fv(materialAmbientLocation, 1, ambient);
	glUniform3fv(materialSpecularLocation, 1, specular);
	glUniform1fv(materialShininessLocation, 1, &shininess);

	// cow 1
	vmath::mat4 c1Transform(vmath::vec4(1.0f, 0.0f, 0.0f, 2.00f), // x
							vmath::vec4(0.0f, 1.0f, 0.0f, 0.00f), // y
							vmath::vec4(0.0f, 0.0f, 1.0f, 0.00f), // z
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	currentMatrix = c1Transform * vmath::scale(0.08f) * 
					vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f); // overall rotation
	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

	// cow 2 (top gun)
	vmath::mat4 c2Transform(vmath::vec4(1.0f, 0.0f, 0.0f, 3.00f), // x
							vmath::vec4(0.0f, 1.0f, 0.0f, -6.00f), // y
							vmath::vec4(0.0f, 0.0f, 1.0f, 0.00f), // z
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	currentMatrix = c2Transform * vmath::scale(0.07f) * 
					vmath::rotate(180.0f, 1.0f, 0.0f, 0.0f) * // flip upside down
					vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f); // overall rotation
	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

	// cow 3 (calf)
	vmath::mat4 c3Transform(vmath::vec4(1.0f, 0.0f, 0.0f, -6.00f), // x
							vmath::vec4(0.0f, 1.0f, 0.0f, -4.00f), // y
							vmath::vec4(0.0f, 0.0f, 1.0f, -14.00f), // z
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	currentMatrix = c3Transform * vmath::scale(0.04f) * 
					vmath::rotate(90.0f, 0.0f, 1.0f, 0.0f) * // face the mother
					vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f); // overall rotation
	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

	// cow 4 (next to, looking behind)
	vmath::mat4 c4Transform(vmath::vec4(1.0f, 0.0f, 0.0f, 0.00f), // x
							vmath::vec4(0.0f, 1.0f, 0.0f, -1.00f), // y
							vmath::vec4(0.0f, 0.0f, 1.0f, -8.00f), // z
							vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	currentMatrix = c4Transform * vmath::scale(0.06f) *
					vmath::rotate(180.0f, 0.0f, 1.0f, 0.0f) * // face behind the mother
					vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f); // overall rotation
	glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);

	glBindVertexArray(vertexBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

	glFlush();
}

void keypress(unsigned char keycode, int x, int y) {
	if (keycode == 'q' || keycode == 'Q') {
		exit(0);
	}
}

// === ENTRY POINT

int main(int argCount, char *argValues[]) {
	glutInit(&argCount, argValues);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cows Everywhere - Zack Ream");

	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewInit();
	init();
	glutKeyboardFunc(keypress);
	glutDisplayFunc(display);
	glutTimerFunc(1000 / 30, timer, 1);
	glutMainLoop();
	return 0;
}