attribute vec4 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;

void main()
{
	gl_Position = a_posL;
	v_uv = a_uv;
}