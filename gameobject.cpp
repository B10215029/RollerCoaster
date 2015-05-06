#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#ifndef RADIAN
#define RADIAN(x) (x*(PI/180.0))
#endif
#ifndef DEGREE
#define DEGREE(x) (x*(180.0/PI))
#endif

#include "gameobject.h"
#include <cmath>

GameObject::GameObject()
{
	name = "GameObject";
	position = vec3(0, 0, 0);
	rotation = vec3(0, 0, 0);
	scale = vec3(1, 1, 1);
	model = NULL;
	parent = NULL;
	children.clear();
}

GameObject::~GameObject()
{

}

void GameObject::setParent(GameObject* p){
	parent = p;
	p->children.push_back(this);
}

void GameObject::setChild(GameObject* c){
	children.push_back(c);
	c->parent = this;
}

mat4 GameObject::translateMat(){
	return mat4(1, 0, 0, position.x(),
				0, 1, 0, position.y(),
				0, 0, 1, position.z(),
				0, 0, 0, 1);
}

mat4 GameObject::scaleMat(){
	return mat4(scale.x(), 0, 0, 0,
				0, scale.y(), 0, 0,
				0, 0, scale.z(), 0,
				0, 0, 0, 1);
}

mat4 GameObject::rotateMat(){
	mat4 rx(1, 0, 0, 0,
			0, cos(RADIAN(rotation.x())), -sin(RADIAN(rotation.x())), 0,
			0, sin(RADIAN(rotation.x())), cos(RADIAN(rotation.x())), 0,
			0, 0, 0, 1);
	mat4 ry(cos(RADIAN(rotation.x())), 0, sin(RADIAN(rotation.x())), 0,
			0, 1, 0, 0,
			-sin(RADIAN(rotation.x())), 0, cos(RADIAN(rotation.x())), 0,
			0, 0, 0, 1);
	mat4 rz(cos(RADIAN(rotation.x())), -sin(RADIAN(rotation.x())), 0, 0,
			sin(RADIAN(rotation.x())), cos(RADIAN(rotation.x())), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	return rx*ry*rz;
}

mat4 GameObject::modelMat(){
	return translateMat() * scaleMat() * rotateMat();
}
