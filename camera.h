#ifndef CAMERA_H
#define CAMERA_H

#include "gameobject.h"
#include "mat.h"
#include "vec.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	mat4 perspective();
	mat4 frustum();
	mat4 projectionMat();
	mat4 lookAt(vec3 center, vec3 up);
	mat4 view();
	bool isPerspective;
	float fov;
	float aspect;
	float left;
	float right;
	float bottom;
	float top;
	float znear;
	float zfar;
};

#endif // CAMERA_H
