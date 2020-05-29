attribute vec3 a_posL;
varying lowp vec4 posL;

void main()
{
	posL = vec4(a_posL, 1.0);
	gl_Position = posL;
}
   