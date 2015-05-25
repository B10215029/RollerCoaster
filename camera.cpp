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

Camera::Camera():GameObject()
{

}

Camera::~Camera()
{

}

mat4 Camera::perspective(){
	mat4 result;
//	float range = tan(RADIAN(fov / 2.0)) * zNear;
//	float left = -range * aspect;
//	float right = range * aspect;
//	float bottom = -range;
//	float top = range;
//	result.data[0] = (2.0 * zNear) / (right - left);
//	result.data[5] = (2.0 * zNear) / (top - bottom);
//	result.data[10] = -(zFar + zNear) / (zFar - zNear);
//	result.data[11] = -1;
//	result.data[14] = -(2.0 * zFar * zNear) / (zFar - zNear);

	result.data[0] = 2.0 / (right - left);
	result.data[5] = 2.0 / (top - bottom);
	result.data[10] = 2.0 / (zNear - zFar);
//	result.data[11] = 1/(zNear - zFar);
	result.data[11] = 1/-100.0f;
//	result.data[11] = 1/(zNear - zFar)*20;
	result.data[12] = (right + left) / (right - left);
	result.data[13] = (top + bottom) / (top - bottom);
	result.data[14] = (zNear + zFar) / (zNear - zFar);
	result.data[15] = 1;
	return result;
}

mat4 Camera::frustum(){
	mat4 result;
	result.data[0] = 2.0 / (right - left);
	result.data[5] = 2.0 / (top - bottom);
	result.data[10] = 2.0 / (zNear - zFar);
	result.data[12] = (right + left) / (right - left);
	result.data[13] = (top + bottom) / (top - bottom);
	result.data[14] = (zNear + zFar) / (zNear - zFar);
	result.data[15] = 1;
	return result;
}

mat4 Camera::projectionMat(){
	return isPerspective?perspective():frustum();
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

mat4 Camera::skyViewMat(){
	mat4 p;
	if(aspect<1){
		p.data[0] = 2.0 / 1200/aspect;
		p.data[5] = 2.0 / 1200;
	}
	else{
		p.data[0] = 2.0 / 1200;
		p.data[5] = 2.0 / 1200*aspect;
	}
	p.data[10] = 0;
	p.data[15] = 1;
	mat4 trm = translateMat() * rotateMat();
	vec3 f = trm * vec3(0, 0, 1);
	vec3 u = trm * vec3(0, 1, 0);
	vec3 s = trm * vec3(1, 0, 0);
	mat4 v(1);
	v.data[0] = s.x();
	v.data[4] = s.y();
	v.data[8] = s.z();
	v.data[1] = u.x();
	v.data[5] = u.y();
	v.data[9] = u.z();
	v.data[2] = f.x();
	v.data[6] = f.y();
	v.data[10] = f.z();
	v.data[12] = 0;
	v.data[13] = 0;
	v.data[14] = 0;
	return v*p;
}

void Camera::setFrustum(float left, float right, float bottom, float top, float zNear, float zFar){
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->zNear = zNear;
	this->zFar = zFar;
	isPerspective = false;
}

void Camera::setPerspective(float fov, float aspect, float zNear, float zFar){
	this->fov = fov;
	this->aspect = aspect;
	this->zNear = zNear;
	this->zFar = zFar;
	isPerspective = true;
}
