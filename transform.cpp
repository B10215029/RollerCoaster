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
	position = vec3(0);
	rotation = vec3(0);
	scale = vec3(1);
}
Transform::Transform(const vec3& p){
	position = p;
	rotation = vec3(0);
	scale = vec3(1);
}

Transform::Transform(const vec3& p, const vec3& r){
	position = p;
	rotation = r;
	scale = vec3(1);
}

Transform::Transform(const vec3& p, const vec3& r, const vec3& s){
	position = p;
	rotation = r;
	scale = s;
}

Transform::~Transform()
{

}

Transform Transform::operator+(Transform &a){
	Transform r;
	r.position = position + a.position;
//	mat4 rm = rotateMat();
//	r.rotation = rotation + rm*vec3(a.rotation.x(),0,0) + rm*vec3(0,a.rotation.y(),0) + rm*vec3(0,0,a.rotation.z());
	r.rotation = rotation + a.rotation;
	r.scale.data[0] = scale.data[0] * a.scale.data[0];
	r.scale.data[1] = scale.data[1] * a.scale.data[1];
	r.scale.data[2] = scale.data[2] * a.scale.data[2];
	return r;
}

Transform Transform::operator-(const Transform &a){
	Transform r;
	r.position = position - a.position;
	//r.rotation = rotation - a.rotation;
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
//	float x = RADIAN(rotation.x());
//	float y = RADIAN(rotation.y());
//	float z = RADIAN(rotation.z());
//	mat4 r(cos(x)*cos(z)-cos(y)*sin(x)*sin(z), -cos(y)*cos(z)*sin(x)-cos(x)*sin(z), sin(x)*sin(y), 0,
//		   cos(z)*sin(x)+cos(x)*cos(y)*sin(z), cos(x)*cos(y)*cos(z)-sin(x)*sin(z), -cos(x)*sin(y), 0,
//		   sin(y)*sin(z), cos(z)*sin(y), cos(y), 0,
//		   0, 0, 0, 1
//		   );
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
//	mat4 rx(1, 0, 0, 0,
//			0, cos(RADIAN(rotation.x())), sin(RADIAN(rotation.x())), 0,
//			0, -sin(RADIAN(rotation.x())), cos(RADIAN(rotation.x())), 0,
//			0, 0, 0, 1);
//	mat4 ry(cos(RADIAN(rotation.y())), 0, -sin(RADIAN(rotation.y())), 0,
//			0, 1, 0, 0,
//			sin(RADIAN(rotation.y())), 0, cos(RADIAN(rotation.y())), 0,
//			0, 0, 0, 1);
//	mat4 rz(cos(RADIAN(rotation.z())), sin(RADIAN(rotation.z())), 0, 0,
//			-sin(RADIAN(rotation.z())), cos(RADIAN(rotation.z())), 0, 0,
//			0, 0, 1, 0,
//			0, 0, 0, 1);
//	mat4 xyz = rx * ry * rz;
//	mat4 yzx = ry * rz * rx;
//	mat4 zxy = rz * rx * ry;
//	mat4 zyx = rz * ry * rx;
//	mat4 yxz = ry * rx * rz;
//	mat4 xzy = rx * rz * ry;
	return rz*ry*rx;
//	return rx*ry*rz;
//	return ry*rx*rz;
//	return r;
}

mat4 Transform::modelMat(){
//	return translateMat() * scaleMat() * rotateMat();
	return rotateMat() * scaleMat() * translateMat();
}
