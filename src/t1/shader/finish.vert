#version 130

in vec2 iPosition;
in vec2 iTexCoord;
out vec2 fragTexcoord;

void main(void)
{
	fragTexcoord = iTexCoord;
	gl_Position = vec4(iPosition, 0.0, 1.0);
}
