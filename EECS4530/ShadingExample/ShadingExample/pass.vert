#version 400 core


struct MaterialProperties {
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform MaterialProperties material; // one material for now...

uniform mat4 transform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform vec3 ambientLightColor;
uniform vec3 diffuseLightColor;
uniform vec3 specularLightColor;
uniform float specularPower;
uniform vec3 eyePosition;
uniform vec4 cowcolor;

in vec4 vPosition;
in vec3 vNormal;
out vec4 passedColor;

void main() {

	gl_Position = transform * vPosition/vPosition.w;
	mat3 m = transpose(inverse(normalTransform));
	vec3 normal = normalize(vNormal * m);
	vec3 useColor = vec3(1.0f, 1.0f, 1.0f);

	// Have hard coded the ambient light color in as vec3(0.3f)
	vec3 ambient;
	if (material.ambient[0] == 0.0 && material.ambient[1] == 0.0 && material.ambient[2] == 0.0) {
		ambient = vec3(0.5f);
	} else {
		 ambient = min(material.ambient * vec3(0.5f), vec3(1.0f));
	}
	vec4 rotatedLightPosition = transform * vec4(lightPosition, 1);
	vec3 light = normalize (rotatedLightPosition.xyz-gl_Position.xyz);
	vec3 diffuse = min(material.diffuse * vec3(0.5f) * dot(normal, light), vec3(1.0f));
	vec3 eyeDirection = normalize (eyePosition - gl_Position.xyz);
	vec3 halfVector = normalize(light + eyeDirection);
	float specular = max(0.0f, dot(normal, halfVector));
	vec3 specularVec = material.specular * vec3(0.5f) * pow(specular, material.shininess);

	if (dot (normal, light) <= 0.0f) {
		diffuse = vec3(0.0f);
		specularVec = vec3(0.0f);
	}

	passedColor.rgb = min (ambient + diffuse + specularVec, vec3(1.0f));
	passedColor.a = 1.0f;
}