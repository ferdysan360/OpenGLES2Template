#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"

Matrix Camera::GetViewMatrix() {
	Vector3 r = transform.rotation;
	Vector3 p = transform.position;

	Matrix View, RotZ, RotX, RotY, Translate;

	View.SetIdentity();

	// set Rotation
	RotZ.SetIdentity();
	RotZ.SetRotationZ(-r.z);
	RotY.SetIdentity();
	RotY.SetRotationY(-r.y);
	RotX.SetIdentity();
	RotX.SetRotationX(-r.x);

	// set Translation
	Translate.SetIdentity();
	Translate.SetTranslation(-p);

	View = Translate * RotY * RotX * RotZ;
	return View;
}

Matrix Camera::GetProjectionMatrix() {
	Matrix proj;
	GLfloat fovY = 1.0f; // radians
	GLfloat aspectRatio = (float)Globals::screenWidth / (float)Globals::screenHeight;
	GLfloat nearPlane = 0.001f;
	GLfloat farPlane = 500.0f;

	proj.SetIdentity();
	proj.SetPerspective(fovY, aspectRatio, nearPlane, farPlane);
	
	return proj;
}