#include "mesh.h"
#include <QFile>
#include <QTextStream>

Mesh::Mesh(){

}

Mesh::Mesh(const char* filePath){
	loadOBJ(filePath);
}

Mesh::~Mesh(){

}

void Mesh::loadOBJ(const char* filePath){
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream data(&file);
	int usingMTL = 0;
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] == '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() >= 4 && arg[0] == "v"){
			vertices.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
		}
		else if(arg.size() >= 3 && arg[0] == "vt"){
			uvs.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), 0));
		}
		else if(arg.size() >= 4 && arg[0] == "vn"){
			normals.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
		}
		else if(arg.size() >= 4 && arg[0] == "f"){
			QVector<face> f;
			for(int i = 1;i<arg.size();++i){
				face index;
				QStringList info = arg[i].split('/');
				if(info.size() == 1){
					index.v = info[0].toInt() - 1;
				}
				else if(info.size() == 2){
					index.v = info[0].toInt() - 1;
					index.vt = info[1].toInt() - 1;
				}
				else if(info.size() == 3){
					index.v = info[0].toInt() - 1;
					index.vt = info[1].toInt() - 1;
					index.vn = info[2].toInt() - 1;
				}
				f.push_back(index);
			}
			faces[usingMTL].push_back(f);
		}
		else if(arg.size() >= 2 && arg[0] == "mtllib"){
			QString path;
			QStringList pathSplit = QString(filePath).split('/');
			for(int i = 0;i < pathSplit.size()-1;++i)
				path += pathSplit[i] + '/';
			loadMTL(arg[1], path);
		}
		else if(arg.size() >= 2 && arg[0] == "usemtl"){
			usingMTL = materialName[arg[1]];
		}
	}
	file.close();
	update();
}

void Mesh::loadMTL(const QString fileName, const QString filePath){
	QFile file(filePath + fileName);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream data(&file);
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] == '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() >= 2 && arg[0] == "newmtl"){
			materialName.insert(arg[1], materialName.size());
			materials.push_back(material());
			materials[materials.size()-1].texture = -1;
			faces.push_back(QVector<QVector<face>>());
		}
		else if(arg.size() >= 4 && arg[0] == "Kd"){

			materials[materials.size()-1].Kd = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 4 && arg[0] == "Ka"){
			materials[materials.size()-1].Ka = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 4 && arg[0] == "Ks"){
			materials[materials.size()-1].Ks = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 2 && arg[0] == "Ns"){
			materials[materials.size()-1].Ns = arg[1].toFloat();
		}
		else if(arg.size() >= 2 && arg[0] == "map_Kd"){
			materials[materials.size()-1].texture = TextureDB::addTexture(filePath + arg[1]);
		}
	}
	file.close();
}
void Mesh::update(){
	for(int i=0;i<mtlFV.size();++i)
		delete[] mtlFV[i];
	mtlFV.clear();
	for(int i=0;i<mtlFT.size();++i)
		delete[] mtlFT[i];
	mtlFT.clear();
	for(int i=0;i<mtlFN.size();++i)
		delete[] mtlFN[i];
	mtlFN.clear();

	for(int i=0;i<materialName.size();++i){
		float *vertexArray=new float[faces[i].size()*3*3];
		for(int j=0;j<faces[i].size();++j){
			vertexArray[j*9+0] = vertices[faces[i][j][0].v].x();
			vertexArray[j*9+1] = vertices[faces[i][j][0].v].y();
			vertexArray[j*9+2] = vertices[faces[i][j][0].v].z();
			vertexArray[j*9+3] = vertices[faces[i][j][1].v].x();
			vertexArray[j*9+4] = vertices[faces[i][j][1].v].y();
			vertexArray[j*9+5] = vertices[faces[i][j][1].v].z();
			vertexArray[j*9+6] = vertices[faces[i][j][2].v].x();
			vertexArray[j*9+7] = vertices[faces[i][j][2].v].y();
			vertexArray[j*9+8] = vertices[faces[i][j][2].v].z();
		}
		mtlFV.push_back(vertexArray);
		float *uvArray=new float[faces[i].size()*3*2];
		for(int j=0;j<faces[i].size();++j){
			if(faces[i][j][0].vt<0) continue;
			uvArray[j*6+0] = uvs[faces[i][j][0].vt].x();
			uvArray[j*6+1] = uvs[faces[i][j][0].vt].y();
			uvArray[j*6+2] = uvs[faces[i][j][1].vt].x();
			uvArray[j*6+3] = uvs[faces[i][j][1].vt].y();
			uvArray[j*6+4] = uvs[faces[i][j][2].vt].x();
			uvArray[j*6+5] = uvs[faces[i][j][2].vt].y();
		}
		mtlFT.push_back(uvArray);
		float *normalArray=new float[faces[i].size()*3*3];
		for(int j=0;j<faces[i].size();++j){
			normalArray[j*9+0] = normals[faces[i][j][0].vn].x();
			normalArray[j*9+1] = normals[faces[i][j][0].vn].y();
			normalArray[j*9+2] = normals[faces[i][j][0].vn].z();
			normalArray[j*9+3] = normals[faces[i][j][1].vn].x();
			normalArray[j*9+4] = normals[faces[i][j][1].vn].y();
			normalArray[j*9+5] = normals[faces[i][j][1].vn].z();
			normalArray[j*9+6] = normals[faces[i][j][2].vn].x();
			normalArray[j*9+7] = normals[faces[i][j][2].vn].y();
			normalArray[j*9+8] = normals[faces[i][j][2].vn].z();
		}
		mtlFN.push_back(normalArray);
	}

}
