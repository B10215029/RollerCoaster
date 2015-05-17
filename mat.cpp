#include "mat.h"
#include <cmath>

mat4::mat4(){
	zero();
}

mat4::mat4(const float a){
	zero();
	data[0] = data[5] = data[10] = data[15] = a;
}

mat4::mat4(const mat4 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	data[3] = a.data[3];
	data[4] = a.data[4];
	data[5] = a.data[5];
	data[6] = a.data[6];
	data[7] = a.data[7];
	data[8] = a.data[8];
	data[9] = a.data[9];
	data[10] = a.data[10];
	data[11] = a.data[11];
	data[12] = a.data[12];
	data[13] = a.data[13];
	data[14] = a.data[14];
	data[15] = a.data[15];
}

mat4::mat4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33){
	data[0] = m00;
	data[1] = m01;
	data[2] = m02;
	data[3] = m03;
	data[4] = m10;
	data[5] = m11;
	data[6] = m12;
	data[7] = m13;
	data[8] = m20;
	data[9] = m21;
	data[10] = m22;
	data[11] = m23;
	data[12] = m30;
	data[13] = m31;
	data[14] = m32;
	data[15] = m33;
}
mat4::mat4(const vec4 &v1, const vec4 &v2, const vec4 &v3, const vec4 &v4){
	data[0] = v1.data[0];
	data[1] = v1.data[1];
	data[2] = v1.data[2];
	data[3] = v1.data[3];
	data[4] = v2.data[0];
	data[5] = v2.data[1];
	data[6] = v2.data[2];
	data[7] = v2.data[3];
	data[8] = v3.data[0];
	data[9] = v3.data[1];
	data[10] = v3.data[2];
	data[11] = v3.data[3];
	data[12] = v4.data[0];
	data[13] = v4.data[1];
	data[14] = v4.data[2];
	data[15] = v4.data[3];
}

mat4& mat4::operator =(const mat4 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	data[3] = a.data[3];
	data[4] = a.data[4];
	data[5] = a.data[5];
	data[6] = a.data[6];
	data[7] = a.data[7];
	data[8] = a.data[8];
	data[9] = a.data[9];
	data[10] = a.data[10];
	data[11] = a.data[11];
	data[12] = a.data[12];
	data[13] = a.data[13];
	data[14] = a.data[14];
	data[15] = a.data[15];
	return *this;
}

bool mat4::operator==(const mat4 &a) const{
	return data[0] == a.data[0] && data[1] == a.data[1] && data[2] == a.data[2] && data[3] == a.data[3] &&
			data[4] == a.data[4] && data[5] == a.data[5] && data[6] == a.data[6] && data[7] == a.data[7] &&
			data[8] == a.data[8] && data[9] == a.data[9] && data[10] == a.data[10] && data[11] == a.data[11] &&
			data[12] == a.data[12] && data[13] == a.data[13] && data[14] == a.data[14] && data[15] == a.data[15];
}

bool mat4::operator!=(const mat4 &a) const{
	return data[0] != a.data[0] || data[1] != a.data[1] || data[2] != a.data[2] || data[3] != a.data[3] ||
			data[4] != a.data[4] || data[5] != a.data[5] || data[6] != a.data[6] || data[7] != a.data[7] ||
			data[8] != a.data[8] || data[9] != a.data[9] || data[10] != a.data[10] || data[11] != a.data[11] ||
			data[12] != a.data[12] || data[13] != a.data[13] || data[14] != a.data[14] || data[15] != a.data[15];
}

void mat4::zero(){
	data[0] = data[1] = data[2] = data[3] =
	data[4] = data[5] = data[6] = data[7] =
	data[8] = data[9] = data[10] = data[11] =
	data[12] = data[13] = data[14] = data[15] = 0.0;
}

mat4 mat4::operator-() const{
	return mat4(-data[0], -data[1], -data[2], -data[3],
				-data[4], -data[5], -data[6], -data[7],
				-data[8], -data[9], -data[10], -data[11],
				-data[12], -data[13], -data[14], -data[15]);
}

mat4 mat4::operator+(const mat4 &a) const{
	return mat4(data[0] + a.data[0], data[1] + a.data[1], data[2] + a.data[2], data[3] + a.data[3],
				data[4] + a.data[4], data[5] + a.data[5], data[6] + a.data[6], data[7] + a.data[7],
				data[8] + a.data[8], data[9] + a.data[9], data[10] + a.data[10], data[11] + a.data[11],
				data[12] + a.data[12], data[13] + a.data[13], data[14] + a.data[14], data[15] + a.data[15]);
}

mat4 mat4::operator-(const mat4 &a) const{
	return mat4(data[0] - a.data[0], data[1] - a.data[1], data[2] - a.data[2], data[3] - a.data[3],
				data[4] - a.data[4], data[5] - a.data[5], data[6] - a.data[6], data[7] - a.data[7],
				data[8] - a.data[8], data[9] - a.data[9], data[10] - a.data[10], data[11] - a.data[11],
				data[12] - a.data[12], data[13] - a.data[13], data[14] - a.data[14], data[15] - a.data[15]);
}

mat4 mat4::operator*(float a) const{
	return mat4(data[0] * a, data[1] * a, data[2] * a, data[3] * a,
				data[4] * a, data[5] * a, data[6] * a, data[7] * a,
				data[8] * a, data[9] * a, data[10] * a, data[11] * a,
				data[12] * a, data[13] * a, data[14] * a, data[15] * a);
}

mat4 mat4::operator/(float a) const{
	float oneOverA = 1.0f / a; // NOTE: no check for divide by zero here
	return mat4(data[0] * oneOverA, data[1] * oneOverA, data[2] * oneOverA, data[3] * oneOverA,
				data[4] * oneOverA, data[5] * oneOverA, data[6] * oneOverA, data[7] * oneOverA,
				data[8] * oneOverA, data[9] * oneOverA, data[10] * oneOverA, data[11] * oneOverA,
				data[12] * oneOverA, data[13] * oneOverA, data[14] * oneOverA, data[15] * oneOverA);
}

mat4& mat4::operator+=(const mat4 &a){
	data[0] += a.data[0];
	data[1] += a.data[1];
	data[2] += a.data[2];
	data[3] += a.data[3];
	data[4] += a.data[4];
	data[5] += a.data[5];
	data[6] += a.data[6];
	data[7] += a.data[7];
	data[8] += a.data[8];
	data[9] += a.data[9];
	data[10] += a.data[10];
	data[11] += a.data[11];
	data[12] += a.data[12];
	data[13] += a.data[13];
	data[14] += a.data[14];
	data[15] += a.data[15];
	return *this;
}
mat4& mat4::operator-=(const mat4 &a){
	data[0] -= a.data[0];
	data[1] -= a.data[1];
	data[2] -= a.data[2];
	data[3] -= a.data[3];
	data[4] -= a.data[4];
	data[5] -= a.data[5];
	data[6] -= a.data[6];
	data[7] -= a.data[7];
	data[8] -= a.data[8];
	data[9] -= a.data[9];
	data[10] -= a.data[10];
	data[11] -= a.data[11];
	data[12] -= a.data[12];
	data[13] -= a.data[13];
	data[14] -= a.data[14];
	data[15] -= a.data[15];
	return *this;
}

mat4& mat4::operator*=(float a){
	data[0] *= a;
	data[1] *= a;
	data[2] *= a;
	data[3] *= a;
	data[4] *= a;
	data[5] *= a;
	data[6] *= a;
	data[7] *= a;
	data[8] *= a;
	data[9] *= a;
	data[10] *= a;
	data[11] *= a;
	data[12] *= a;
	data[13] *= a;
	data[14] *= a;
	data[15] *= a;
	return *this;
}

mat4& mat4::operator/=(float a){
	float oneOverA = 1.0f / a;
	data[0] *= oneOverA;
	data[1] *= oneOverA;
	data[2] *= oneOverA;
	data[3] *= oneOverA;
	data[4] *= oneOverA;
	data[5] *= oneOverA;
	data[6] *= oneOverA;
	data[7] *= oneOverA;
	data[8] *= oneOverA;
	data[9] *= oneOverA;
	data[10] *= oneOverA;
	data[11] *= oneOverA;
	data[12] *= oneOverA;
	data[13] *= oneOverA;
	data[14] *= oneOverA;
	data[15] *= oneOverA;
	return *this;
}

mat4 mat4::operator*(const mat4 &a) const{
	return mat4(data[0]*a.data[0] + data[1]*a.data[4] + data[2]*a.data[8] + data[3]*a.data[12],
				data[0]*a.data[1] + data[1]*a.data[5] + data[2]*a.data[9] + data[3]*a.data[13],
				data[0]*a.data[2] + data[1]*a.data[6] + data[2]*a.data[10] + data[3]*a.data[14],
				data[0]*a.data[3] + data[1]*a.data[7] + data[2]*a.data[11] + data[3]*a.data[15],
				data[4]*a.data[0] + data[5]*a.data[4] + data[6]*a.data[8] + data[7]*a.data[12],
				data[4]*a.data[1] + data[5]*a.data[5] + data[6]*a.data[9] + data[7]*a.data[13],
				data[4]*a.data[2] + data[5]*a.data[6] + data[6]*a.data[10] + data[7]*a.data[14],
				data[4]*a.data[3] + data[5]*a.data[7] + data[6]*a.data[11] + data[7]*a.data[15],
				data[8]*a.data[0] + data[9]*a.data[4] + data[10]*a.data[8] + data[11]*a.data[12],
				data[8]*a.data[1] + data[9]*a.data[5] + data[10]*a.data[9] + data[11]*a.data[13],
				data[8]*a.data[2] + data[9]*a.data[6] + data[10]*a.data[10] + data[11]*a.data[14],
				data[8]*a.data[3] + data[9]*a.data[7] + data[10]*a.data[11] + data[11]*a.data[15],
				data[12]*a.data[0] + data[13]*a.data[4] + data[14]*a.data[8] + data[15]*a.data[12],
				data[12]*a.data[1] + data[13]*a.data[5] + data[14]*a.data[9] + data[15]*a.data[13],
				data[12]*a.data[2] + data[13]*a.data[6] + data[14]*a.data[10] + data[15]*a.data[14],
				data[12]*a.data[3] + data[13]*a.data[7] + data[14]*a.data[11] + data[15]*a.data[15]);
}

vec3 mat4::operator*(const vec3 &a) const{
	return vec3(data[0]*a.data[0] + data[1]*a.data[1] + data[2]*a.data[2] + data[3],
				data[4]*a.data[0] + data[5]*a.data[1] + data[6]*a.data[2] + data[7],
				data[8]*a.data[0] + data[9]*a.data[1] + data[10]*a.data[2] + data[11]);
}

vec4 mat4::operator*(const vec4 &a) const{
	return vec4(data[0]*a.data[0] + data[1]*a.data[1] + data[2]*a.data[2] + data[3]*a.data[3],
				data[4]*a.data[0] + data[5]*a.data[1] + data[6]*a.data[2] + data[7]*a.data[3],
				data[8]*a.data[0] + data[9]*a.data[1] + data[10]*a.data[2] + data[11]*a.data[3],
				data[12]*a.data[0] + data[13]*a.data[1] + data[14]*a.data[2] + data[15]*a.data[3]);
}

mat4 mat4::transpose() const{
	return mat4(data[0], data[4], data[8], data[12],
				data[1], data[5], data[9], data[13],
				data[2], data[6], data[10], data[14],
				data[3], data[7], data[11], data[15]);
}

// Nonmember functions
mat4 operator *(float k, const mat4 &m){
	return m*k;
}
