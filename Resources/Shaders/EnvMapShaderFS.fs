precision mediump float;
uniform samplerCube u_texture;
uniform vec3 u_camPosition;
varying vec3 v_pos;
varying vec3 v_norm;
void main()
{
	vec3 toEye = u_camPosition - v_pos;
	vec3 reflectDir = reflect(normalize(-toEye), normalize(v_norm)); // reflect() in non linear
	gl_FragColor = textureCube(u_texture, reflectDir);
}