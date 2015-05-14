#version 130
uniform vec3 uColor;
uniform sampler2D colorTex0;

in vec2 fragTexcoord;

void main(void)
{
	//gl_FragColor = vec4(uColor, 1.0);

	gl_FragData[0] = vec4(fract(fragTexcoord.x), fract(fragTexcoord.y), 1.0, 1.0);
	gl_FragData[1] = vec4(0.0, 0.0, 1.0, 1.0);
}
