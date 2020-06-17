attribute vec3 a_posL;
attribute vec4 a_uv;
attribute vec3 a_normal;
uniform mat4 u_world;
uniform mat4 u_w;
varying vec3 v_pos;
varying vec3 v_norm;

void main()
{
	gl_Position = u_world * vec4(a_posL, 1.0);
	v_norm = mat3(u_world) * a_normal;
	v_pos = vec3(u_w * vec4(a_posL, 1.0));
}