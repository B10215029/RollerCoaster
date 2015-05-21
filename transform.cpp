#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#ifndef RADIAN
#define RADIAN(x) (x*(PI/180.0))
#endif
#ifndef DEGREE
#define DEGREE(x) (x*(180.0/PI))
#endif

#include "transform.h"
#include <cmath>

Transform::Transform()
{
	position = vec3();
	rotation = vec3();
	scale = vec3(1);
}

Transform::~Transform()
{

}

Transform Transform::operator+(const Transform &a) const{
	Transform r;
	r.position = position + a.position;
	r.rotation = rotation + a.rotation;
	r.scale.data[0] = scale.data[0] * a.scale.data[0];
	r.scale.data[1] = scale.data[1] * a.scale.data[1];
	r.scale.data[2] = scale.data[2] * a.scale.data[2];
	return r;
}

Transform Transform::operator-(const Transform &a) const{
	Transform r;
	r.position = position - a.position;
	r.rotation = rotation - a.rotation;
	r.scale.data[0] = scale.data[0] / a.scale.data[0];
	r.scale.data[1] = scale.data[1] / a.scale.data[1];
	r.scale.data[2] = scale.data[2] / a.scale.data[2];
	return r;
}

mat4 Transform::translateMat(){
	return mat4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				position.x(), position.y(), position.z(), 1);
}

mat4 Transform::scaleMat(){
	return mat4(scale.x(), 0, 0, 0,
				0, scale.y(), 0, 0,
				0, 0, scale.z(), 0,
				0, 0, 0, 1);
}

mat4 Transform::rotateMat(){
	mat4 rx(1, 0, 0, 0,
			0, cos(RADIAN(rotation.x())), -sin(RADIAN(rotation.x())), 0,
			0, sin(RADIAN(rotation.x())), cos(RADIAN(rotation.x())), 0,
			0, 0, 0, 1);
	mat4 ry(cos(RADIAN(rotation.y())), 0, sin(RADIAN(rotation.y())), 0,
			0, 1, 0, 0,
			-sin(RADIAN(rotation.y())), 0, cos(RADIAN(rotation.y())), 0,
			0, 0, 0, 1);
	mat4 rz(cos(RADIAN(rotation.z())), -sin(RADIAN(rotation.z())), 0, 0,
			sin(RADIAN(rotation.z())), cos(RADIAN(rotation.z())), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	return rz*ry*rx;
}

mat4 Transform::modelMat(){
	return translateMat() * scaleMat() * rotateMat();
}
