#include "gameobject.h"

int GameObject::NumOfID = 0;

GameObject::GameObject()
{
	id = ++NumOfID;
	name = "GameObject";
	position = vec3(0, 0, 0);
	rotation = vec3(0, 0, 0);
	scale = vec3(1, 1, 1);
	mesh = NULL;
	parent = NULL;
	children.clear();
}

GameObject::GameObject(const GameObject& a){
	id = ++NumOfID;
	name = a.name;
	position = a.position;
	rotation = a.rotation;
	scale = a.scale;
	mesh = a.mesh;
	animationType = a.animationType;
	parent = a.parent;
	children = a.children;
}

GameObject::~GameObject()
{

}

GameObject& GameObject::operator=(const GameObject &a){
	id = ++NumOfID;
	name = a.name;
	position = a.position;
	rotation = a.rotation;
	scale = a.scale;
	mesh = a.mesh;
	animationType = a.animationType;
	parent = a.parent;
	children = a.children;
	return *this;
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

void GameObject::animation(float t){
	if(animationType & AnimRotateX){

	}
	if(animationType & AnimRotateXB){

	}
	if(animationType & AnimRotateY){
		rotation.y()+=0.5;
	}
	if(animationType & AnimRotateYB){
		rotation.y()-=0.5;
	}
	if(animationType & AnimRotateZ){

	}
	if(animationType & AnimRotateZB){

	}
	if(animationType & AnimTrain){

	}
	if(animationType & AnimCharIdle){

	}
	if(animationType & AnimCharWalk){

	}
	//rotation.y()+=0.5;
	//rotation.data[1]=t;
	//rotation=vec3(0,0,t);
}
