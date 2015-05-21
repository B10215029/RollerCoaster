#include "vec.h"
#include <cmath>

/////vec3/////
vec3::vec3(){
	data[0] = data[1] = data[2] = 0.0;
}

vec3::vec3(const vec3 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
}

vec3::vec3(float a){
	data[0] = data[1] = data[2] = a;
}

vec3::vec3(float nx, float ny, float nz){
	data[0] = nx;
	data[1] = ny;
	data[2] = nz;
}

vec3& vec3::operator=(const vec3 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	return *this;
}

bool vec3::operator==(const vec3 &a) const{
	return data[0]==a.data[0] && data[1]==a.data[1] && data[2]==a.data[2];
}

bool vec3::operator!=(const vec3 &a) const{
	return data[0]!=a.data[0] || data[1]!=a.data[1] || data[2]!=a.data[2];
}

vec3 vec3::operator-() const{
	return vec3(-data[0],-data[1],-data[2]);
}

vec3 vec3::operator+(const vec3 &a) const{
	return vec3(data[0] + a.data[0], data[1] + a.data[1], data[2] + a.data[2]);
}

vec3 vec3::operator-(const vec3 &a) const{
	return vec3(data[0] - a.data[0], data[1] - a.data[1], data[2] - a.data[2]);
}

vec3 vec3::operator*(float a) const{
	return vec3(data[0]*a, data[1]*a, data[2]*a);
}

vec3 vec3::operator/(float a) const{
	float oneOverA = 1.0f / a; // NOTE: no check for divide by zero here
	return vec3(data[0]*oneOverA, data[1]*oneOverA, data[2]*oneOverA);
}

vec3& vec3::operator+=(const vec3 &a){
	data[0] += a.data[0];
	data[1] += a.data[1];
	data[2] += a.data[2];
	return *this;
}

vec3& vec3::operator-=(const vec3 &a){
	data[0] -= a.data[0];
	data[1] -= a.data[1];
	data[2] -= a.data[2];
	return *this;
}

vec3& vec3::operator*=(float a){
	data[0] *= a;
	data[1] *= a;
	data[2] *= a;
	return *this;
}

vec3& vec3::operator/=(float a){
	float oneOverA = 1.0f / a;
	data[0] *= oneOverA;
	data[1] *= oneOverA;
	data[2] *= oneOverA;
	return *this;
}

float vec3::operator*(const vec3 &a) const{
	return data[0]*a.data[0] + data[1]*a.data[1] + data[2]*a.data[2];
}

void vec3::zero(){
	data[0] = data[1] = data[2] = 0.0;
}

vec3 vec3::normalize(){
	float magSq = data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
	if (magSq > 0.0f)
	{ // check for divide-by-zero
		float oneOverMag = 1.0f / sqrt(magSq);
		data[0] *= oneOverMag;
		data[1] *= oneOverMag;
		data[2] *= oneOverMag;
	}
	return *this;
}

float vec3::length() const{
	return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}

/////vec4/////
float& vec4::x(){
	return data[0];
}

float& vec4::y(){
	return data[1];
}

float& vec4::z(){
	return data[2];
}

float& vec4::w(){
	return data[3];
}

vec4::vec4(){
	data[0] = data[1] = data[2] = data[3] = 0.0;
}

vec4::vec4(const vec4 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	data[3] = a.data[3];
}

vec4::vec4(const vec3 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	data[3] = 1.0;
}

vec4::vec4(float nx, float ny, float nz, float nw){
	data[0] = nx;
	data[1] = ny;
	data[2] = nz;
	data[2] = nw;
}

vec4::vec4(float nx, float ny, float nz){
	data[0] = nx;
	data[1] = ny;
	data[2] = nz;
	data[2] = 1.0;
}

vec4& vec4::operator=(const vec4 &a){
	data[0] = a.data[0];
	data[1] = a.data[1];
	data[2] = a.data[2];
	data[3] = a.data[3];
	return *this;
}

bool vec4::operator==(const vec4 &a) const{
	return data[0]==a.data[0] && data[1]==a.data[1] && data[2]==a.data[2] && data[3]==a.data[3];
}

bool vec4::operator!=(const vec4 &a) const{
	return data[0]!=a.data[0] || data[1]!=a.data[1] || data[2]!=a.data[2] || data[3]!=a.data[3];
}

vec4 vec4::operator-() const{
	return vec4(-data[0],-data[1],-data[2],-data[3]);
}

vec4 vec4::operator+(const vec4 &a) const{
	return vec4(data[0] + a.data[0], data[1] + a.data[1], data[2] + a.data[2], data[3] + a.data[3]);
}

vec4 vec4::operator-(const vec4 &a) const{
	return vec4(data[0] - a.data[0], data[1] - a.data[1], data[2] - a.data[2], data[3] - a.data[3]);
}

vec4 vec4::operator*(float a) const{
	return vec4(data[0]*a, data[1]*a, data[2]*a, data[3]*a);
}

vec4 vec4::operator/(float a) const{
	float oneOverA = 1.0f / a; // NOTE: no check for divide by zero here
	return vec4(data[0]*oneOverA, data[1]*oneOverA, data[2]*oneOverA, data[3]*oneOverA);
}

vec4& vec4::operator+=(const vec4 &a){
	data[0] += a.data[0];
	data[1] += a.data[1];
	data[2] += a.data[2];
	data[3] += a.data[3];
	return *this;
}

vec4& vec4::operator-=(const vec4 &a){
	data[0] -= a.data[0];
	data[1] -= a.data[1];
	data[2] -= a.data[2];
	data[3] -= a.data[3];
	return *this;
}

vec4& vec4::operator*=(float a){
	data[0] *= a;
	data[1] *= a;
	data[2] *= a;
	data[3] *= a;
	return *this;
}

vec4& vec4::operator/=(float a){
	float oneOverA = 1.0f / a;
	data[0] *= oneOverA;
	data[1] *= oneOverA;
	data[2] *= oneOverA;
	data[3] *= oneOverA;
	return *this;
}

float vec4::operator*(const vec4 &a) const{
	return data[0]*a.data[0] + data[1]*a.data[1] + data[2]*a.data[2] + data[3]*a.data[3];
}

void vec4::zero(){
	data[0] = data[1] = data[2] = data[3] = 0.0;
}

vec4 vec4::normalize(){
	float magSq = data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3];
	if (magSq > 0.0f)
	{ // check for divide-by-zero
		float oneOverMag = 1.0f / sqrt(magSq);
		data[0] *= oneOverMag;
		data[1] *= oneOverMag;
		data[2] *= oneOverMag;
		data[3] *= oneOverMag;
	}
	return *this;
}

float vec4::length() const{
	return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3]);
}

//Nonmember functions

float vectorMag(const vec3 &a){
	return sqrt(a.data[0]*a.data[0] + a.data[1]*a.data[1] + a.data[2]*a.data[2]);
}

float vectorMag(const vec4 &a){
	return sqrt(a.data[0]*a.data[0] + a.data[1]*a.data[1] + a.data[2]*a.data[2] + a.data[3]*a.data[3]);
}

vec3 crossProduct(const vec3 &a, const vec3 &b){
	return vec3(
	a.data[1]*b.data[2] - a.data[2]*b.data[1],
	a.data[2]*b.data[0] - a.data[0]*b.data[2],
	a.data[0]*b.data[1] - a.data[1]*b.data[0]);
}

vec3 crossProduct(const vec4 &a, const vec4 &b){
	return vec3(
	a.data[1]*b.data[2] - a.data[2]*b.data[1],
	a.data[2]*b.data[0] - a.data[0]*b.data[2],
	a.data[0]*b.data[1] - a.data[1]*b.data[0]);
}

vec3 operator *(float k, const vec3 &v){
	return vec3(k*v.data[0], k*v.data[1], k*v.data[2]);
}

vec4 operator *(float k, const vec4 &v){
	return vec4(k*v.data[0], k*v.data[1], k*v.data[2], k*v.data[3]);
}

float distance(const vec3 &a, const vec3 &b){
	float dx = a.data[0] - b.data[0];
	float dy = a.data[1] - b.data[1];
	float dz = a.data[2] - b.data[2];
	return sqrt(dx*dx + dy*dy + dz*dz);
}

float distance(const vec4 &a, const vec4 &b){
	float dx = a.data[0] - b.data[0];
	float dy = a.data[1] - b.data[1];
	float dz = a.data[2] - b.data[2];
	float dw = a.data[3] - b.data[3];
	return sqrt(dx*dx + dy*dy + dz*dz + dw*dw);
}
