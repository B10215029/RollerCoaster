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
	virtual void animation(float t);
	static int NumOfID;
	int id;
	QString name;
	Mesh* mesh;
	GameObject* parent;
	QVector<GameObject*> children;
	int animationType;
	enum {
		AnimNone		= 0x000,
		AnimRotateX		= 0x001,
		AnimRotateXB	= 0x002,
		AnimRotateY		= 0x004,
		AnimRotateYB	= 0x008,
		AnimRotateZ		= 0x010,
		AnimRotateZB	= 0x020,
		AnimCharIdle	= 0x040,
		AnimCharWalk	= 0x080,
		AnimRobot		= 0x100,
		AnimJump1		= 0x200,
		AnimJump2		= 0x400,
		AnimJump3		= 0x800,
		AnimJump4		= 0x1000
	};
	enum {BODY,HEAD,HANDUL,HANDUR,HANDDL,HANDDR,FOOTUL,FOOTUR,FOOTDL,FOOTDR,PARTNUM};
};

#endif // GAMEOBJECT_H
