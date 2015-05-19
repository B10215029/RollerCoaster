#ifndef MAT_H
#define MAT_H

#include "vec.h"
class mat4
{
public:

	float data[16];

	mat4();
	mat4(const float a);
	mat4(const mat4 &a);
	mat4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	mat4(const vec4 &v1, const vec4 &v2, const vec4 &v3, const vec4 &v4);

	mat4 &operator=(const mat4 &a);
	bool operator==(const mat4 &a) const;
	bool operator!=(const mat4 &a) const;

	mat4 operator-() const;
	mat4 operator+(const mat4 &a) const;
	mat4 operator-(const mat4 &a) const;
	mat4 operator*(float a) const;
	mat4 operator/(float a) const;

	mat4 &operator+=(const mat4 &a);
	mat4 &operator-=(const mat4 &a);
	mat4 &operator*=(float a);
	mat4 &operator/=(float a);
	mat4 operator*(const mat4 &a) const;
	vec3 operator*(const vec3 &a) const;
	vec4 operator*(const vec4 &a) const;

	void zero();
	mat4 transpose() const;

};
mat4 operator *(float k, const mat4 &m);
vec3 operator*(const vec3 &v, const mat4 &m);

#endif // MAT_H
