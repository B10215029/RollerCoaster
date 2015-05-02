#include "ControlPoint.h"

//Default contructor
ControlPoint::ControlPoint() : pos(0,0,0), orient(0,1,0){

}

//Set up the position and set orientation to default (0, 1, 0)
ControlPoint::ControlPoint(const vec3 &_pos) : pos(_pos), orient(0,1,0){

}

//Set up the position and orientation
ControlPoint::ControlPoint(const vec3 &_pos, const vec3 &_orient) : pos(_pos), orient(_orient){
	orient.normalize();
}

ControlPoint::ControlPoint(const int tIndex) : index(tIndex), pos(0,0,0), orient(0,1,0){

}
