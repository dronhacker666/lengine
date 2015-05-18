#version 130
uniform sampler2D colorTex0;

in vec2 fragTexcoord;

void main(void)
{
	gl_FragData[0] = texture(colorTex0, fragTexcoord);
	gl_FragData[1] = vec4(0.0, 0.0, 1.0, 1.0);
}
