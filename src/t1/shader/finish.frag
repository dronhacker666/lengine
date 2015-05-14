#version 130

uniform sampler2D colorTex0;
uniform sampler2D colorTex1;
uniform sampler2D depthTex;
in vec2 fragTexcoord;

float line_depth(float z)
{
	float n = 1.0;
	float f = 100.0;
	return (2.0 * n) / (f + n - z * (f - n));
}


void main(void)
{
	//float c = line_depth(texture2D(iTex0, fragTexcoord.xy).r);
	//gl_FragColor = vec4(c, c, c, 0.6);

 	vec3 color = texture2D(colorTex0, fragTexcoord).rgb;
 	float depth = line_depth(texture2D(depthTex, fragTexcoord).r);

 	gl_FragColor = vec4(color, 1.0);

}
