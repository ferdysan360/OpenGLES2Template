attribute vec4 a_posL;
attribute vec4 a_uv;
uniform mat4 u_world;
varying vec4 v_pos;

void main()
{
	gl_Position = u_world * a_posL;
	v_pos = a_posL;
}