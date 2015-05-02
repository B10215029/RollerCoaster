/////////////////////////////////////////////////////////////////////////////
//
// class vec3 -- a simple 3D vector class
//
/////////////////////////////////////////////////////////////////////////////
#include <cmath>
class vec3
{
public:

	// Public representation: Not many options here.
	float data[3];

	float& x(){
		return data[0];
	}

	float& y(){
		return data[1];
	}

	float& z(){
		return data[2];
	}

	// Constructors
	// Default constructor leaves vector in
	// an indeterminate state
	vec3() {}

	// Copy constructor
	vec3(const vec3 &a)
	{
		data[0] = a.data[0];
		data[1] = a.data[1];
		data[2] = a.data[2];
	}

	// Construct given three values
	vec3(float nx, float ny, float nz)
	{
		data[0] = nx;
		data[1] = ny;
		data[2] = nz;
	}

	// Standard object maintenance
	// Assignment. We adhere to C convention and
	// return reference to the lvalue
	vec3 &operator =(const vec3 &a)
	{
		data[0] = a.data[0];
		data[1] = a.data[1];
		data[2] = a.data[2];
		return *this;
	}

	// Check for equality
	bool operator ==(const vec3 &a) const
	{
		return data[0]==a.data[0] && data[1]==a.data[1] && data[2]==a.data[2];
	}

	bool operator !=(const vec3 &a) const
	{
		return data[0]!=a.data[0] || data[1]!=a.data[1] || data[2]!=a.data[2];
	}

	// Vector operations
	// Set the vector to zero
	void zero()
	{
		data[0] = data[1] = data[2] = 0.0;
	}

	// Unary minus returns the negative of the vector
	vec3 operator -() const
	{
		return vec3(-data[0],-data[1],-data[2]);
	}

	// Binary + and - add and subtract vectors
	vec3 operator +(const vec3 &a) const
	{
		return vec3(data[0] + a.data[0], data[1] + a.data[1], data[2] + a.data[2]);
	}

	vec3 operator -(const vec3 &a) const
	{
		return vec3(data[0] - a.data[0], data[1] - a.data[1], data[2] - a.data[2]);
	}

	// Multiplication and division by scalar
	vec3 operator *(float a) const
	{
		return vec3(data[0]*a, data[1]*a, data[2]*a);
	}

	vec3 operator /(float a) const
	{
		float oneOverA = 1.0 / a; // NOTE: no check for divide by zero here
		return vec3(data[0]*oneOverA, data[1]*oneOverA, data[2]*oneOverA);
	}

	// Combined assignment operators to conform to
	// C notation convention
	vec3 &operator +=(const vec3 &a)
	{
		data[0] += a.data[0];
		data[1] += a.data[1];
		data[2] += a.data[2];
		return *this;
	}

	vec3 &operator -=(const vec3 &a)
	{
		data[0] -= a.data[0];
		data[1] -= a.data[1];
		data[2] -= a.data[2];
		return *this;
	}

	vec3 &operator *=(float a)
	{
		data[0] *= a;
		data[1] *= a;
		data[2] *= a;
		return *this;
	}

	vec3 &operator /=(float a)
	{
		float oneOverA = 1.0 / a;
		data[0] *= oneOverA;
		data[1] *= oneOverA;
		data[2] *= oneOverA;
		return *this;
	}

	// Normalize the vector
	void normalize()
	{
		float magSq = data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
		if (magSq > 0.0f)
		{ // check for divide-by-zero
			float oneOverMag = 1.0f / sqrt(magSq);
			data[0] *= oneOverMag;
			data[1] *= oneOverMag;
			data[2] *= oneOverMag;
		}
	}

	// Vector dot product. We overload the standard
	// multiplication symbol to do this
	float operator *(const vec3 &a) const
	{
		return data[0]*a.data[0] + data[1]*a.data[1] + data[2]*a.data[2];
	}

	float length() const
	{
		return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
	}
};

/////////////////////////////////////////////////////////////////////////////
//
// Nonmember functions
//
/////////////////////////////////////////////////////////////////////////////

// Compute the magnitude of a vector
inline float vectorMag(const vec3 &a)
{
	return sqrt(a.data[0]*a.data[0] + a.data[1]*a.data[1] + a.data[2]*a.data[2]);
}

// Compute the cross product of two vectors
inline vec3 crossProduct(const vec3 &a, const vec3 &b)
{
	return vec3(
	a.data[1]*b.data[2] - a.data[2]*b.data[1],
	a.data[2]*b.data[0] - a.data[0]*b.data[2],
	a.data[0]*b.data[1] - a.data[1]*b.data[0]
	);
}

// Scalar on the left multiplication, for symmetry
inline vec3 operator *(float k, const vec3 &v)
{
	return vec3(k*v.data[0], k*v.data[1], k*v.data[2]);
}

// Compute the distance between two points
inline float distance(const vec3 &a, const vec3 &b)
{
	float dx = a.data[0] - b.data[0];
	float dy = a.data[1] - b.data[1];
	float dz = a.data[2] - b.data[2];
	return sqrt(dx*dx + dy*dy + dz*dz);
}
