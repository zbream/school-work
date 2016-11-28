#version 150

out vec4 fColor;
in vec4 passedColor;

void main() {
	fColor = passedColor;
}
