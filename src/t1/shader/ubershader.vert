#version 130
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

in vec3 iPosition;
in vec2 iTexCoord;

out vec2 fragTexcoord;

void main(void)
{
	fragTexcoord = iTexCoord;
	gl_Position = viewMatrix * (modelMatrix * vec4(iPosition, 1.0));
}
