/////////////////////////////////////////////////////////////////////////////
//
// class mat4 -- a simple 3D vector class
//
/////////////////////////////////////////////////////////////////////////////
#include <cmath>
class mat4
{
public:

	// Public representation: Not many options here.
	float data[16];

	// Constructors
	// Default constructor leaves vector in
	// an indeterminate state
	inline mat4() {}

	// Copy constructor
	inline mat4(const mat4 &a)
	{
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

	// Construct given three values
	inline mat4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
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

	// Standard object maintenance
	// Assignment. We adhere to C convention and
	// return reference to the lvalue
	inline mat4 &operator =(const mat4 &a)
	{
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

	// Check for equality
	inline bool operator ==(const mat4 &a) const
	{
		return data[0] == a.data[0] && data[1] == a.data[1] && data[2] == a.data[2] && data[3] == a.data[3] &&
				data[4] == a.data[4] && data[5] == a.data[5] && data[6] == a.data[6] && data[7] == a.data[7] &&
				data[8] == a.data[8] && data[9] == a.data[9] && data[10] == a.data[10] && data[11] == a.data[11] &&
				data[12] == a.data[12] && data[13] == a.data[13] && data[14] == a.data[14] && data[15] == a.data[15];
	}

	inline bool operator !=(const mat4 &a) const
	{
		return data[0] != a.data[0] || data[1] != a.data[1] || data[2] != a.data[2] || data[3] != a.data[3] ||
				data[4] != a.data[4] || data[5] != a.data[5] || data[6] != a.data[6] || data[7] != a.data[7] ||
				data[8] != a.data[8] || data[9] != a.data[9] || data[10] != a.data[10] || data[11] != a.data[11] ||
				data[12] != a.data[12] || data[13] != a.data[13] || data[14] != a.data[14] || data[15] != a.data[15];
	}

	// Vector operations
	// Set the vector to zero
	inline void zero()
	{
		data[0] = data[1] = data[2] = data[3] =
		data[4] = data[5] = data[6] = data[7] =
		data[8] = data[9] = data[10] = data[11] =
		data[12] = data[13] = data[14] = data[15] = 0.0;
	}

	// Unary minus returns the negative of the vector
	inline mat4 operator -() const
	{
		return mat4(-data[0], -data[1], -data[2], -data[3],
					-data[4], -data[5], -data[6], -data[7],
					-data[8], -data[9], -data[10], -data[11],
					-data[12], -data[13], -data[14], -data[15]);
	}

	// Binary + and - add and subtract vectors
	inline mat4 operator +(const mat4 &a) const
	{
		return mat4(data[0] + a.data[0], data[1] + a.data[1], data[2] + a.data[2], data[3] + a.data[3],
					data[4] + a.data[4], data[5] + a.data[5], data[6] + a.data[6], data[7] + a.data[7],
					data[8] + a.data[8], data[9] + a.data[9], data[10] + a.data[10], data[11] + a.data[11],
					data[12] + a.data[12], data[13] + a.data[13], data[14] + a.data[14], data[15] + a.data[15]);
	}

	inline mat4 operator -(const mat4 &a) const
	{
		return mat4(data[0] - a.data[0], data[1] - a.data[1], data[2] - a.data[2], data[3] - a.data[3],
					data[4] - a.data[4], data[5] - a.data[5], data[6] - a.data[6], data[7] - a.data[7],
					data[8] - a.data[8], data[9] - a.data[9], data[10] - a.data[10], data[11] - a.data[11],
					data[12] - a.data[12], data[13] - a.data[13], data[14] - a.data[14], data[15] - a.data[15]);
	}

	// Multiplication and division by scalar
	inline mat4 operator *(float a) const
	{
		return mat4(data[0] * a, data[1] * a, data[2] * a, data[3] * a,
					data[4] * a, data[5] * a, data[6] * a, data[7] * a,
					data[8] * a, data[9] * a, data[10] * a, data[11] * a,
					data[12] * a, data[13] * a, data[14] * a, data[15] * a);
	}

	inline mat4 operator /(float a) const
	{
		float oneOverA = 1.0 / a; // NOTE: no check for divide by zero here
		return mat4(data[0] * oneOverA, data[1] * oneOverA, data[2] * oneOverA, data[3] * oneOverA,
					data[4] * oneOverA, data[5] * oneOverA, data[6] * oneOverA, data[7] * oneOverA,
					data[8] * oneOverA, data[9] * oneOverA, data[10] * oneOverA, data[11] * oneOverA,
					data[12] * oneOverA, data[13] * oneOverA, data[14] * oneOverA, data[15] * oneOverA);
	}

	// Combined assignment operators to conform to
	// C notation convention
	inline mat4 &operator +=(const mat4 &a)
	{
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

	inline mat4 &operator -=(const mat4 &a)
	{
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

	inline mat4 &operator *=(float a)
	{
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

	inline mat4 &operator /=(float a)
	{
		float oneOverA = 1.0 / a;
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

	// Normalize the vector
	inline void normalize()
	{
		float magSq = length();
		if (magSq > 0.0f)
		{ // check for divide-by-zero
			float oneOverMag = 1.0f / magSq;
			data[0] *= oneOverMag;
			data[1] *= oneOverMag;
			data[2] *= oneOverMag;
		}
	}

	// Vector dot product. We overload the standard
	// multiplication symbol to do this
	inline float operator *(const mat4 &a) const
	{
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

	inline float length() const
	{
		return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3] +
				data[4]*data[4] + data[5]*data[5] + data[6]*data[6] + data[7]*data[7] +
				data[8]*data[8] + data[9]*data[9] + data[10]*data[10] + data[11]*data[11] +
				data[12]*data[12] + data[13]*data[13] + data[14]*data[14] + data[15]*data[15]);
	}
};

/////////////////////////////////////////////////////////////////////////////
//
// Nonmember functions
//
/////////////////////////////////////////////////////////////////////////////

// Scalar on the left multiplication, for symmetry
inline mat4 operator *(float k, const mat4 &m)
{
	return m*k;
}

// Compute the distance between two points
inline float distance(const mat4 &a, const mat4 &b)
{
	return (a-b).length();
}
