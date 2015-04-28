#version 130
uniform vec3 uColor;

in vec2 fragTexcoord;

void main(void)
{
	gl_FragColor.rgb = uColor;
}
