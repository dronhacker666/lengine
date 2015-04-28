#version 130
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
in vec3 iPosition;

void main(void)
{
	gl_Position = viewMatrix * (modelMatrix * vec4(iPosition, 1.0));
}
