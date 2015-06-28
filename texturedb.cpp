#include "texturedb.h"

QVector<QString> TextureDB::name;
QVector<unsigned int> TextureDB::ID;
QVector<QImage> TextureDB::image;

void TextureDB::init(){
	name.clear();
	ID.clear();
	image.clear();
}

int TextureDB::addTexture(QString path){
	for(int i=0;i<name.size();++i)
		if(path == name[i])
			return i;
	name.push_back(path);
	ID.push_back(0);
	image.push_back(QImage(path));
	image[image.size()-1] = image[image.size()-1].convertToFormat(QImage::Format_RGBA8888);
	image[image.size()-1] = image[image.size()-1].mirrored();
	return name.size()-1;
}
