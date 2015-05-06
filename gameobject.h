#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector>
#include <QString>
#include "vec3.h"
#include "mat4.h"
#include "model.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void setParent(GameObject* p);
	void setChild(GameObject* c);
	mat4 translateMat();
	mat4 scaleMat();
	mat4 rotateMat();
	mat4 modelMat();
	QString name;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	Model* model;
	GameObject* parent;
	QVector<GameObject*> children;
};

#endif // GAMEOBJECT_H
