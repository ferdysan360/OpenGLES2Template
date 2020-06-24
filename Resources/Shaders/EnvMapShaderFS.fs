precision mediump float;
uniform samplerCube u_texture;
uniform vec3 u_camPosition;
varying vec3 v_pos;
varying vec3 v_norm;
void main()
{
	float ambientStrength = 0.1;
	vec3 lightColor = vec3(1.0, 0.0, 0.0);
	vec3 ambient = ambientStrength * lightColor;

	vec3 toEye = u_camPosition - v_pos;
	vec3 reflectDir = reflect(normalize(-toEye), normalize(v_norm));
	gl_FragColor = textureCube(u_texture, reflectDir);
}