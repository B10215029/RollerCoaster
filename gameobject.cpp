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
	animationType = AnimNone;
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

float linerFunc(float t,float s1,float e1,float t1,float s2=0,float e2=0,float t2=0,float s3=0,float e3=0,float t3=0,float s4=0,float e4=0,float t4=0,float s5=0,float e5=0,float t5=0,float s6=0,float e6=0,float t6=0){
	t-=((int)(t/(t1+t2+t3+t4+t5+t6)))*(t1+t2+t3+t4+t5+t6);
	if(t<t1)
		return (e1-s1)*(t/t1)+s1;
	else if(t<t1+t2)
		return (e2-s2)*((t-t1)/t2)+s2;
	else if(t<t1+t2+t3)
		return (e3-s3)*((t-t1-t2)/t3)+s3;
	else if(t<t1+t2+t3+t4)
		return (e4-s4)*((t-t1-t2-t3)/t4)+s4;
	else if(t<t1+t2+t3+t4+t5)
		return (e5-s5)*((t-t1-t2-t3-t4)/t5)+s5;
	else
		return (e6-s6)*((t-t1-t2-t3-t4-t5)/t6)+s6;
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
	if(animationType & AnimRobot){
		float rt=0.005;
		float angles[PARTNUM];
		angles[BODY]=-linerFunc(t,32,30,10*rt,30,25,10*rt,25,18,20*rt,18,18,10*rt,18,33,20*rt);
		angles[HEAD]=40;
		angles[FOOTUL]=-linerFunc(t,20,-36,40*rt,-36,-115,30*rt,-115,-105,10*rt,-105,20,60*rt);
		angles[FOOTDL]=-linerFunc(t,35,80,15*rt, 80,120,15*rt, 120,115,30*rt, 115,47,25*rt, 47,44,45*rt, 44,35,10*rt);
		angles[FOOTUR]=-linerFunc(t+70*rt,20,-36,40*rt,-36,-115,30*rt,-115,-105,10*rt,-105,20,60*rt);
		angles[FOOTDR]=-linerFunc(t+70*rt,35,80,15*rt,80,120,15*rt,120,115,30*rt,115,47,25*rt,47,44,45*rt,44,35,10*rt);
		angles[HANDUL]=-linerFunc(t+70*rt,45,0,40*rt, 0,-90,30*rt, -90,0,30*rt, 0,45,40*rt);
		angles[HANDDL]=-linerFunc(t+70*rt,-56,-103,70*rt, -103,-16,40*rt, -16,-56,30*rt);
		angles[HANDUR]=-linerFunc(t,45,0,40*rt, 0,-90,30*rt, -90,0,30*rt, 0,45,40*rt);
		angles[HANDDR]=-linerFunc(t,-56,-103,70*rt, -103,-16,40*rt, -16,-56,30*rt);

		children[0]->rotation = vec3(angles[BODY],0,0);
		children[0]->children[0]->rotation = vec3(angles[HEAD],0,0);
		children[0]->children[1]->rotation = vec3(angles[HANDUL],0,-10);
		children[0]->children[2]->rotation = vec3(angles[HANDUR],0,10);
		children[0]->children[1]->children[0]->rotation = vec3(angles[HANDDL],0,0);
		children[0]->children[2]->children[0]->rotation = vec3(angles[HANDDR],0,0);
		children[0]->children[3]->rotation = vec3(angles[FOOTUL],0,0);
		children[0]->children[4]->rotation = vec3(angles[FOOTUR],0,0);
		children[0]->children[3]->children[0]->rotation = vec3(angles[FOOTDL],30,0);
		children[0]->children[4]->children[0]->rotation = vec3(angles[FOOTDR],-30,0);
	}
	if(animationType & AnimJump1){
		position.y() = linerFunc(t, 0,0,0.0 ,0,4,0.1, 4,0,0.1, 0,0,0.6);
	}
	if(animationType & AnimJump2){
		position.y() = linerFunc(t, 0,0,0.2 ,0,4,0.1, 4,0,0.1, 0,0,0.4);
	}
	if(animationType & AnimJump3){
		position.y() = linerFunc(t, 0,0,0.4 ,0,4,0.1, 4,0,0.1, 0,0,0.2);
	}
	if(animationType & AnimJump4){
		position.y() = linerFunc(t, 0,0,0.6 ,0,4,0.1, 4,0,0.1, 0,0,0.0);
	}
}
