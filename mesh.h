#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QMap>
#include <QImage>
#include "vec.h"
#include "texturedb.h"

typedef struct{
	int v;
	int vt;
	int vn;
}face;

typedef struct{
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	int Ns;
	int texture;
}material;

class Mesh
{
public:
	Mesh();
	Mesh(const char* filePath);
	~Mesh();
	void loadOBJ(const char* filePath);
	void loadMTL(const QString fileName, const QString filePath);
	void update();
	QVector<vec3> vertices;
	QVector<vec3> uvs;
	QVector<vec3> normals;
	QVector<QVector<QVector<face>>> faces;
	QMap<QString, int> materialName;
	QVector<material> materials;

	QVector<float*> mtlFV;
	QVector<float*> mtlFT;
	QVector<float*> mtlFN;

};

#endif // MESH_H
