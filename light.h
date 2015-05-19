#ifndef LIGHT_H
#define LIGHT_H

#include "camera.h"

class Light : public Camera
{
public:
	Light();
	~Light();
	vec3 direction();
};

#endif // LIGHT_H
