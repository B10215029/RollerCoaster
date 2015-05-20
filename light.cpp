#include "light.h"

Light::Light()
{

}

Light::~Light()
{

}

vec3 Light::direction(){
	return rotateMat() * vec3(0, 0, 1);
}
