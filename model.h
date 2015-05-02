#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QMap>
#include <QImage>
#include "vec3.h"

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
	QVector<QVector<int[3]>> faces;
	QVector<int> faceMaterial;
	QMap<QString, int> materialName;
	QVector<float[3]> Kds;
	QVector<float[3]> Kas;
	QVector<float[3]> Kss;
	QVector<float> Nss;
	QVector<QImage> textures;
};

#endif // MODEL_H
