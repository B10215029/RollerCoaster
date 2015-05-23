#ifndef VEC_H
#define VEC_H

class vec3
{
public:

	float data[3];

	inline float& x(){return data[0];}
	inline float& y(){return data[1];}
	inline float& z(){return data[2];}

	vec3();
	vec3(const vec3 &a);
	vec3(float a);
	vec3(float nx, float ny, float nz);

	vec3& operator=(const vec3 &a);
	bool operator==(const vec3 &a) const;
	bool operator!=(const vec3 &a) const;

	vec3 operator-() const;
	vec3 operator+(const vec3 &a) const;
	vec3 operator-(const vec3 &a) const;
	vec3 operator*(float a) const;
	vec3 operator/(float a) const;

	vec3& operator+=(const vec3 &a);
	vec3& operator-=(const vec3 &a);
	vec3& operator*=(float a);
	vec3& operator/=(float a);

	float operator*(const vec3 &a) const;

	void zero();
	vec3 normalize();
	float length() const;
};

class vec4
{
public:

	float data[4];

	inline float& x();
	inline float& y();
	inline float& z();
	inline float& w();

	vec4();
	vec4(const vec4 &a);
	vec4(const vec3 &a);
	vec4(float nx, float ny, float nz, float nw);
	vec4(float nx, float ny, float nz);

	vec4& operator=(const vec4 &a);
	bool operator==(const vec4 &a) const;
	bool operator!=(const vec4 &a) const;

	vec4 operator-() const;
	vec4 operator+(const vec4 &a) const;
	vec4 operator-(const vec4 &a) const;
	vec4 operator*(float a) const;
	vec4 operator/(float a) const;

	vec4& operator+=(const vec4 &a);
	vec4& operator-=(const vec4 &a);
	vec4& operator*=(float a);
	vec4& operator/=(float a);

	float operator*(const vec4 &a) const;

	vec3 xyz();
	void zero();
	vec4 normalize();
	float length() const;
};

float vectorMag(const vec3 &a);
float vectorMag(const vec4 &a);
vec3 crossProduct(const vec3 &a, const vec3 &b);
vec3 crossProduct(const vec4 &a, const vec4 &b);
vec3 operator*(float k, const vec3 &v);
vec4 operator*(float k, const vec4 &v);
float distance(const vec3 &a, const vec3 &b);
float distance(const vec4 &a, const vec4 &b);

#endif // VEC_H
