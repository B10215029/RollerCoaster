#ifndef TEXTUREDB_H
#define TEXTUREDB_H

#include <QImage>
#include <QVector>
#include <QString>

class TextureDB
{
public:
	static void init();
	static int addTexture(QString path);

	static QVector<QString> name;
	static QVector<unsigned int> ID;
	static QVector<QImage> image;
};

#endif // TEXTUREDB_H

