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

GameObject GameObject::operator+(const GameObject &a) const{
	GameObject r;
	r.position = position + a.position;
	r.rotation = rotation + a.rotation;
	r.scale.data[0] = scale.data[0] * a.scale.data[0];
	r.scale.data[1] = scale.data[1] * a.scale.data[1];
	r.scale.data[2] = scale.data[2] * a.scale.data[2];
	return r;
}

void GameObject::setParent(GameObject* p){
	deleteParent();
	parent = p;
	p->children.push_back(this);
}

void GameObject::setChild(GameObject* c){
	c->deleteParent();
	children.push_back(c);
	c->parent = this;
}

void GameObject::deleteParent(){
	if(parent){
		for(int i=0;i<parent->children.size();++i){
			if(this == parent->children[i]){
				parent->children.remove(i);
				break;
			}
		}
		parent = NULL;
	}
}

void GameObject::deleteChild(GameObject* c){
	for(int i=0;i<children.size();++i){
		if(c == children[i]){
			children[i]->parent = NULL;
			children.remove(i);
			break;
		}
	}
}

mat4 GameObject::translateMat(){
	return mat4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				position.x(), position.y(), position.z(), 1);
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
	mat4 ry(cos(RADIAN(rotation.y())), 0, sin(RADIAN(rotation.y())), 0,
			0, 1, 0, 0,
			-sin(RADIAN(rotation.y())), 0, cos(RADIAN(rotation.y())), 0,
			0, 0, 0, 1);
	mat4 rz(cos(RADIAN(rotation.z())), -sin(RADIAN(rotation.z())), 0, 0,
			sin(RADIAN(rotation.z())), cos(RADIAN(rotation.z())), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	return rx*ry*rz;
}

mat4 GameObject::modelMat(){
	return translateMat() * scaleMat() * rotateMat();
}

void GameObject::animation(float t){
	rotation.y()++;
	//rotation.data[1]=t;
	//rotation=vec3(0,0,t);
}
