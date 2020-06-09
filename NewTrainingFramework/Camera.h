#pragma once
#include "../Utilities/utilities.h"
#include "Object3D.h"

class Camera : public Object3D {
public:
	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();
};