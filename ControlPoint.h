#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "vec3.h"

class ControlPoint {
	public:
		// constructors
		// need a default constructor for making arrays
		ControlPoint();					

		// create by name
		ControlPoint(const int tIndex);								

		// create in a position
		ControlPoint(const vec3& pos);

		// Create in a position and orientation
		ControlPoint(const vec3& pos, const vec3& orient);

	public:
		int index;		   // Name of this control point
		vec3 pos;         // Position of this control point
		vec3 orient;	   // Orientation of this control point
		//Vector3 tangen;
};

#endif // CONTROLPOINT_H
