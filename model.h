#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QMap>
#include <QImage>
#include "vec3.h"

typedef struct{
	int v;
	int vt;
	int vn;
}faceData;

class Model
{
public:
	Model();
	Model(const char* filePath);
	~Model();
	void loadOBJ(const char* filePath);
	void loadMTL(const QString name, const QString filePath);
	QVector<vec3> vertices;
	QVector<vec3> uvs;
	QVector<vec3> normals;
	QVector<QVector<faceData>> faces;
	QVector<int> faceMaterial;
	QMap<QString, int> materialName;
	QVector<vec3> Kds;
	QVector<vec3> Kas;
	QVector<vec3> Kss;
	QVector<float> Nss;
	QVector<QImage> textures;
	//QVector<QVector<int>> materialFace;

};

#endif // MODEL_H
