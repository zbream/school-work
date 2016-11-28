#version 330 core

out vec4 fragColor;
in vec4 passedColor;

void main() {
	fragColor = passedColor;
}
