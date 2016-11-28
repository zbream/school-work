#version 330 core
/*
 * This is the project 3 shader file for the vertices.  It hopefully contains
 * all the pieces we are going to need for many of our projects.  It is 
 * Lots of uniform variables -- mostly dealing with color and 
 * transformations.
 */
uniform mat4 modelingTransform;
uniform mat4 projectionTransform = {{1.0, 0.0, 0.0, 0.0}, 
                                    {0.0, 1.0, 0.0, 0.0}, 
									{0.0, 0.0, 1.0, 0.0}, 
									{0.0, 0.0, 0.0, 1.0}};
uniform mat3 normalTransform;
uniform bool light0On = true, light2On=true, light1On=true;
uniform vec3 eyePosition = { 0.0, 0.0, 10.0};
uniform int materialID = 0;

in vec4 vPosition;
in vec3 vNormal;
out vec4 passedColor;
out vec3 passedNormal;

#define DIRECTIONAL 0
#define POINT 1

struct light_t {
	int		type;
	vec4	position;
	vec3	ambientColor;
	vec3	diffuseColor;
	vec3	specularColor;
};

struct material_t {
	vec3   ambientColor;
	vec3   diffuseColor;
	vec3   specularColor;
	float  shininess;
};


/*
 * Indices:
 *   0 -- Emerald			12 -- Black Plastic
 *   1 -- Jade				13 -- Cyan Plastic
 *   2 -- Obsidian			14 -- Green Plastic
 *   3 -- Pearl				15 -- Red Plastic
 *   4 -- Ruby				16 -- White Plastic
 *   5 -- Turquoise			17 -- Yellow Plastic
 *   6 -- Brass				18 -- Black Rubber
 *   7 -- Bronze			19 -- Cyan Rubber
 *   8 -- Chrome			20 -- Green Rubber
 *   9 -- Copper			21 -- Red Rubber
 *  10 -- Gold				22 -- White Rubber
 *  11 -- Silver			23 -- Yellow Rubber
 */

uniform material_t materialList[24] = {
				{{0.0215, 0.1745, 0.0215}, {0.07568, 0.61424, 0.07568}, {0.633, 0.727811, 0.633}, 76.8},
				{{0.135, 0.2225, 0.1575}, {0.54, 0.89, 0.63}, {0.316228, 0.316228, 0.316228}, 12.8},
				{{0.05375, 0.05, 0.06625}, {0.18275, 0.17, 0.22525}, {0.332741, 0.328634, 0.346435}, 38.4},
				{{0.25, 0.20725, 0.20725}, {1.0, 0.829, 0.829}, {0.296648, 0.296648, 0.296648}, 0.088*128},
				{{0.1745, 0.01175, 0.01175}, {0.61424, 0.04136, 0.04136}, {0.727811, 0.626959, 0.626959}, 76.8},
				{{0.1, 0.18725, 0.1745}, {0.296, 0.74151, 0.69102}, {0.297254, 0.30829, 0.306678}, 12.8},
				{{0.329412, 0.223529, 0.027451}, {0.780392, 0.568627, 0.113725}, {0.992157, 0.941176, 0.807843}, 0.21794872*128},
				{{0.2125, 0.1275, 0.054}, {0.714, 0.4284, 0.18144}, {0.393548, 0.271906, 0.166721}, 25.6},
				{{0.25, 0.25, 0.25}, {0.4, 0.4, 0.4}, {0.774597, 0.774797, 0.774797}, 76.8},
				{{0.1925, 0.0735, 0.0225}, {0.7038, 0.27048, 0.0828}, {0.256777, 0.137622, 0.086014}, 12.8},
				{{0.24725, 0.1995, 0.0745}, {0.75164, 0.60648, 0.22648}, {0.628281, 0.555802, 0.366065}, 51.2},
				{{0.19255, 0.19225, 0.19225}, {0.5074, 0.5074, 0.5074}, {0.508723, 0.508723, 0.508723}, 51.2},
				{{0.0, 0.0, 0.0}, {0.01, 0.01, 0.01}, {0.50, 0.50, 0.50}, 32.0},
				{{0.0, 0.1, 0.06}, {0.0, 0.50980392, 0.50980392}, {0.50196078, 0.50196078, 0.50196078}, 32.0},
				{{0.0, 0.0, 0.0}, {0.1, 0.35, 0.1}, {0.45, 0.55, 0.45}, 32.0},
				{{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.7, 0.6, 0.6}, 32.0}, 
				{{0.0, 0.0, 0.0}, {0.55, 0.55, 0.55}, {0.7, 0.7, 0.7}, 32.0},
				{{0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.6, 0.6, 0.5}, 32.0},
				{{0.02, 0.02, 0.02}, {0.01, 0.01, 0.01}, {0.4, 0.4, 0.4}, 10.0 },
				{{0.0, 0.05, 0.05}, {0.4, 0.5, 0.5}, {0.04, 0.7, 0.7}, 10},
				{{0.0, 0.05, 0.0}, {0.4, 0.5, 0.04},{0.04, 0.7, 0.04}, 10},
				{{0.05, 0.0, 0.0}, {0.5, 0.4, 0.4}, {0.7, 0.04, 0.04}, 10},
				{{0.05, 0.05, 0.05}, {0.5, 0.5, 0.5}, {0.7, 0.7, 0.7}, 10},
				{{0.05, 0.05, 0.0}, {0.5, 0.5, 0.4}, {0.7, 0.7, 0.04}, 10}
				};


uniform light_t lightList[3] = {
					{DIRECTIONAL, {0.0f, -0.7071f, -0.7071f, 1.0f}, {0.05f, 0.05f, 0.05f}, {0.7f, 0.7f, 0.7f}, {1.0f, 1.0f, 1.0f}},
                    {POINT, {-2.0, 2.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.5}, {0.8, 0.8, 0.8}},
					{POINT, {2.0, 2.0, 2.0, 1.0}, {1.0,1.0,1.0}, {0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}}
};


void main() {

	vec3 useColor;
	bool lightEnabled[3];
	lightEnabled[0] = light0On;
	lightEnabled[1] = light1On;
	lightEnabled[2] = light2On;
	vec3 light;
	vec3 ambientTotal, diffuseTotal, specularTotal;
	vec3 ambient, diffuse, eyeDirection, halfVector, specularVec;
	float specular;
	int lightNbr;

	ambientTotal = vec3(0.0f);
	diffuseTotal = vec3(0.0f);
	specularTotal = vec3(0.0f);

	gl_Position = modelingTransform * vPosition/vPosition.w;
	passedColor = vec4(1.0f);

	mat3 m = transpose(inverse(normalTransform));
    // The correction for the normals must be postmultiplied -- not the other way around.
	vec3 normal = normalize( vNormal * m );
	//normal = normalize(vNormal);
	for (lightNbr = 0; lightNbr < 3; lightNbr++) {
		if (lightEnabled[lightNbr]) {
			if (lightList[lightNbr].type == POINT) {
				light = normalize (lightList[lightNbr].position.xyz - gl_Position.xyz);
			} else if (lightList[lightNbr].type == DIRECTIONAL) {
				light = normalize(lightList[lightNbr].position.xyz);
			}
			ambient = clamp(materialList[materialID].ambientColor * lightList[lightNbr].ambientColor, vec3(0.0f), vec3(1.0f));
			diffuse = min(materialList[materialID].diffuseColor * lightList[lightNbr].diffuseColor * dot(normal, light), vec3(1.0f));
			eyeDirection = normalize (eyePosition - gl_Position.xyz);
			halfVector = normalize(light + eyeDirection);
			specular = max(0.0, dot(normal, halfVector));
			specularVec = materialList[materialID].specularColor * lightList[lightNbr].specularColor * pow(specular, materialList[materialID].shininess);
			if (dot (normal, light) <= 0.0f) {
				diffuse = vec3(0.0f);
				specularVec = vec3(0.0f);
			}
			ambientTotal += ambient;
			diffuseTotal += diffuse;
			specularTotal += specularVec;
		}
	}
	// do the projection thing now...
	gl_Position = projectionTransform * modelingTransform * vPosition/vPosition.w;
	// pass color through to fragment shader...
	passedColor.rgb = clamp(ambientTotal + diffuseTotal + specularTotal, vec3(0.0f), vec3(1.0f));
	passedColor.a = 1.0f;
}