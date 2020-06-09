attribute vec4 a_posL;
attribute vec2 a_uv;
uniform mat4 u_world;
varying vec2 v_uv;

void main()
{
	gl_Position = u_world * a_posL;
	v_uv = a_uv;
}