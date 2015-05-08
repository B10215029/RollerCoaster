#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QMap>
#include <QImage>
#include "vec3.h"
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

class Model
{
public:
	Model();
	Model(const char* filePath);
	~Model();
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

#endif // MODEL_H
