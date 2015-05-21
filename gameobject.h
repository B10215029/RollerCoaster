#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector>
#include <QString>
#include "transform.h"
#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include "texturedb.h"

class GameObject : public Transform
{
public:
	GameObject();
	GameObject(const GameObject &a);
	~GameObject();
	GameObject& operator=(const GameObject &a);
	void setParent(GameObject* p);
	void setChild(GameObject* c);
	void deleteParent();
	void deleteChild(GameObject* c);
	void animation(float t);
	static int NumOfID;
	int id;
	QString name;
	Mesh* mesh;
	GameObject* parent;
	QVector<GameObject*> children;
	enum {AnimNone, AnimTrain, AnimCharIdle, AnimCharWalk};
	int animationType;
};

#endif // GAMEOBJECT_H
