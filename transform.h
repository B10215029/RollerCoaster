#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec.h"
#include "mat.h"

class Transform
{
public:
	Transform();
	~Transform();
	Transform operator+(const Transform &a) const;
	Transform operator-(const Transform &a) const;
	mat4 translateMat();
	mat4 scaleMat();
	mat4 rotateMat();
	mat4 modelMat();
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

#endif // TRANSFORM_H
