#version 130

uniform sampler2D iTex0;
in vec2 fragTexcoord;

void main(void)
{
	float z = texture2D(iTex0, fragTexcoord.xy).r;
	float n = 1.0;
	float f = 3000.0;
	float c = (2.0 * n) / (f + n - z * (f - n));

	gl_FragColor.rgb = vec3(c);
}
