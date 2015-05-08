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
	result.data[11] = -1;
	result.data[14] = -(2.0 * zfar * znear) / (zfar - znear);
	return result;
}

mat4 Camera::frustum(){
	mat4 result;
	result.data[0] = (2.0 * znear) / (right - left);
	result.data[5] = (2.0 * znear) / (top - bottom);
	result.data[8] = (right + left) / (right - left);
	result.data[9] = (top + bottom) / (top - bottom);
	result.data[10] = -(zfar + znear) / (zfar - znear);
	result.data[11] = -1.0;
	result.data[14] = -(2.0 * zfar * znear) / (zfar - znear);
	return result;
}

mat4 Camera::lookAt(vec3 center, vec3 up){
	vec3 f = (center - position).normalize();
	vec3 u = up.normalize();
	vec3 s = crossProduct(f, u).normalize();
	u = crossProduct(s, f);
	mat4 result(1);
	result.data[0] = s.x();
	result.data[4] = s.y();
	result.data[8] = s.z();
	result.data[1] = u.x();
	result.data[5] = u.y();
	result.data[9] = u.z();
	result.data[2] =-f.x();
	result.data[6] =-f.y();
	result.data[10] =-f.z();
	result.data[12] =-(s*position);
	result.data[13] =-(u*position);
	result.data[14] = (f*position);
	return result;
}

mat4 Camera::view(){
	mat4 trm = translateMat() * rotateMat();
	vec3 f = trm * vec3(0, 0, 1);
	vec3 u = trm * vec3(0, 1, 0);
	vec3 s = trm * vec3(1, 0, 0);
	mat4 result(1);
	result.data[0] = s.x();
	result.data[4] = s.y();
	result.data[8] = s.z();
	result.data[1] = u.x();
	result.data[5] = u.y();
	result.data[9] = u.z();
	result.data[2] = f.x();
	result.data[6] = f.y();
	result.data[10] = f.z();
	result.data[12] = -(s*position);
	result.data[13] = -(u*position);
	result.data[14] = -(f*position);
	return result;
}