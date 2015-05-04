#include "camera.h"
#include <cmath>
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#ifndef RADIAN
#define RADIAN(x) (x*(PI/180.0))
#endif
#ifndef DEGREE
#define DEGREE(x) (x*(180.0/PI))
#endif

Camera::Camera()
{

}

Camera::~Camera()
{

}

mat4 Camera::perspective(){
	float range = tan(RADIAN(fov / 2.0)) * znear;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;
	mat4 result;
	result.data[0] = (2.0 * znear) / (right - left);
	result.data[5] = (2.0 * znear) / (top - bottom);
	result.data[10] = -(zfar + znear) / (zfar - znear);
	result.data[11] = -(2.0 * zfar * znear) / (zfar - znear);
	result.data[14] = -1;
	return result;
}

mat4 Camera::frustum(){
	mat4 result;
	result.data[0] = (2.0 * znear) / (right - left);
	result.data[5] = (2.0 * znear) / (top - bottom);
	result.data[2] = (right + left) / (right - left);
	result.data[6] = (top + bottom) / (top - bottom);
	result.data[10] = -(zfar + znear) / (zfar - znear);
	result.data[14] = -1.0;
	result.data[11] = -(2.0 * zfar * znear) / (zfar - znear);
	return result;
}

mat4 Camera::lookAt(){
	mat4 rm = rotateMat();
	vec3 f = rm*vec3(0, 0, -1);
	vec3 u = rm*vec3(0, 1, 0);
	vec3 s = crossProduct(f, u).normalize();
	u = crossProduct(s, f);
	mat4 result(1);
	result.data[0] = s.x();
	result.data[1] = s.y();
	result.data[2] = s.z();
	result.data[4] = u.x();
	result.data[5] = u.y();
	result.data[6] = u.z();
	result.data[8] =-f.x();
	result.data[9] =-f.y();
	result.data[10] =-f.z();
	result.data[3] =-(s*position);
	result.data[7] =-(u*position);
	result.data[11] = (f*position);
	return result;
}
