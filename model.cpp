#include "model.h"
#include <QFile>
#include <QTextStream>

Model::Model(){

}

Model::Model(const char* filePath){
	loadOBJ(filePath);
}

Model::~Model(){

}

void Model::loadOBJ(const char* filePath){
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream data(&file);
	int usingMTL = 0;
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] = '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() > 4 && arg[0] == "v"){
			vertices.push_back(vec(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
		}
		else if(arg.size() > 3 && arg[0] == "vt"){
			uvs.push_back(vec(arg[1].toFloat(), arg[2].toFloat(), 0));
		}
		else if(arg.size() > 4 && arg[0] == "vn"){
			normals.push_back(vec(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
		}
		else if(arg.size() > 4 && arg[0].toFloat() == "f"){
			QVector<int[3]> f;
			for(int i = 1;i<arg.size();++i){
				int index[3]={};
				QStringList info = arg[i].split('/');
				if(info.size == 1){
					index[0] = info[0].toInt() - 1;
				}
				else if(info.size == 2){
					index[0] = info[0].toInt() - 1;
					index[1] = info[1].toInt() - 1;
				}
				else if(info.size == 3){
					index[0] = info[0].toInt() - 1;
					index[1] = info[1].toInt() - 1;
					index[2] = info[2].toInt() - 1;
				}
				f.push_back(index);
			}
			faces.push_back(f);
			faceMaterial.push_back(usingMTL);
		}
		else if(arg.size() > 2 && arg[0] == "mtllib"){
			QString path;
			QStringList pathSplit = QString(filePath).split('/');
			for(int i = 0;i < pathSplit.size()-1;++i)
				path += pathSplit[i] + '/';
			loadMTL(arg[1], path);
		}
		else if(arg.size() > 2 && arg[0] == "usemtl"){
			usingMTL = materialName[arg[2]];
		}
	}
	file.close();
}

void Model::loadMTL(const QString name, const QString filePath){
	QFile file(filePath + name);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream data(&file);
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] = '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() > 2 && arg[0] == "newmtl"){
			float def[3]={};
			Kds.push_back(def);
			Kas.push_back(def);
			Kss.push_back(def);
			Nss.push_back(0);
			textures.push_back(QImage());
			materialName.insert(name, materialName.size());
		}
		else if(arg.size() > 4 && arg[0] == "Kd"){
			Kds[Kds.size()-1][0] = arg[1].toFloat();
			Kds[Kds.size()-1][1] = arg[2].toFloat();
			Kds[Kds.size()-1][2] = arg[3].toFloat();
		}
		else if(arg.size() > 4 && arg[0] == "Ka"){
			Kas[Kas.size()-1][0] = arg[1].toFloat();
			Kas[Kas.size()-1][1] = arg[2].toFloat();
			Kas[Kas.size()-1][2] = arg[3].toFloat();
		}
		else if(arg.size() > 4 && arg[0] == "Ks"){
			Kss[Kss.size()-1][0] = arg[1].toFloat();
			Kss[Kss.size()-1][1] = arg[2].toFloat();
			Kss[Kss.size()-1][2] = arg[3].toFloat();
		}
		else if(arg.size() > 2 && arg[0] == "Ns"){
			Nss[Nss.size()-1][0] = arg[1].toFloat();
		}
		else if(arg.size() > 2 && arg[0] == "map_Kd"){
			textures[textures.size()-1][0] = QImage(filePath + arg[1]);
		}
	}
	file.close();
}
