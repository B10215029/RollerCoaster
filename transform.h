#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec.h"
#include "mat.h"

class Transform
{
public:
	Transform();
	Transform(const vec3& p);
	Transform(const vec3& p, const vec3& r);
	Transform(const vec3& p, const vec3& r, const vec3& s);
	~Transform();
	Transform operator+(Transform &a);
	Transform operator-(const Transform &a);
	mat4 translateMat();
	mat4 scaleMat();
	mat4 rotateMat();
	mat4 modelMat();
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

#endif // TRANSFORM_H
