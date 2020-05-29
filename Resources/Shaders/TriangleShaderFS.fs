precision mediump float;
varying lowp vec4 posL;

void main()
{
	vec3 position = posL.xyz;
	vec3 color;
	color.r = -posL.x + 0.5;
	color.g = abs(posL.x + posL.y);
	color.b = -posL.y + 0.5;
	gl_FragColor = vec4(color, 1.0);
}