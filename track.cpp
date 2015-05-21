#include "track.h"
#include <QFile>
#include <QTextStream>

Track::Track():GameObject(){
	controlPointMesh.loadOBJ(":/models/controlPoint.obj");
	controlPoints.clear();
	trains.clear();
	trackType = TrackType;
	curveType = CardinalType;
	addPoint(vec3(50, 10, 0));
	addPoint(vec3(0, 10, 50));
	addPoint(vec3(-50, 10, 0));
	addPoint(vec3(0, 10, -50));
	trackType = LineType;
	curveType = LinearType;
}

Track::~Track(){

}

void Track::update(){
	switch(curveType){
	case LineType:
		mesh = new Mesh();
		mesh->materialName.insert(QString("woold"), mesh->materialName.size());
		mesh->materialName.insert(QString("steel"), mesh->materialName.size());
		mesh->materials.push_back(material());
		mesh->materials.push_back(material());
		mesh->faces.push_back(QVector<QVector<VerticesData>>());
		mesh->faces.push_back(QVector<QVector<VerticesData>>());
		mesh->materials[0].Kd = vec3(0, 0, 0);
		mesh->materials[0].Ka = vec3(0, 0, 0);
		mesh->materials[0].Ks = vec3(0, 0, 0);
		mesh->materials[0].Ns = 0;
		mesh->materials[0].texture = -1;
		mesh->materials[1].Kd = vec3(0, 0, 0);
		mesh->materials[1].Ka = vec3(0, 0, 0);
		mesh->materials[1].Ks = vec3(0, 0, 0);
		mesh->materials[1].Ns = 0;
		mesh->materials[1].texture = -1;
		for(int i=0;i<controlPoints.size();++i){

		}
		mesh->update();
		break;
	case TrackType:

		break;
	case RoadType:

		break;
	}

}

vec3 Track::getCurvePosition(float t, int sp){
	switch(curveType){
	case LinearType:
		return controlPoints[(sp+controlPoints.size())%controlPoints.size()]->position +
				(controlPoints[(sp+controlPoints.size()+1)%controlPoints.size()]->position -
				controlPoints[(sp+controlPoints.size())%controlPoints.size()]->position)*t;
		break;
	case CardinalType:

		break;
	case CubicType:

		break;
	}
	return vec3();
}

void Track::loadFile(QString filePath){
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream data(&file);
	int npts;
	data >> npts;
	if(npts<4 || npts>65535) {
		printf("Illegal Number of Points Specified in File");
		return;
	}
	for(int i=0;i<controlPoints.size();++i){
		deleteChild(controlPoints[i]);
		delete controlPoints[i];
	}
	controlPoints.clear();
	while(!data.atEnd()){
		vec3 pos,rot;
		QStringList words = data.readLine().split(' ');
		if(words[0][0]=='#')
			continue;
		if (words.size() >= 3) {
			pos.x() = words[0].toDouble();
			pos.y() = words[1].toDouble();
			pos.z() = words[2].toDouble();
		} else {
			pos.x() = 0;
			pos.y() = 0;
			pos.z() = 0;
		}
		if (words.size() >= 6) {
			rot.x() = words[3].toDouble();
			rot.y() = words[4].toDouble();
			rot.z() = words[5].toDouble();
		} else {
			rot.x() = 0;
			rot.y() = 1;
			rot.z() = 0;
		}
		rot.normalize();
		addPoint(pos, rot);
	}
	file.close();
	update();
}

void Track::saveFile(QString filePath){
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly)) {
		printf("Can't open file for writing");
		return;
	}
	QTextStream data(&file);
	data << controlPoints.size() << "\n";
	for(int i=0; i<controlPoints.size(); ++i)
		data << controlPoints[i]->position.x()
			 << controlPoints[i]->position.y()
			 << controlPoints[i]->position.z()
			 << controlPoints[i]->rotation.x()
			 << controlPoints[i]->rotation.y()
			 << controlPoints[i]->rotation.z()
			 <<"\n";
	file.close();
}

void Track::addPoint(){
	addPoint((controlPoints[0]->position+controlPoints.last()->position)/2);
}

void Track::addPoint(vec3 pos, vec3 rot){
	controlPoints.push_back(new GameObject());
	controlPoints.last()->position = pos;
	controlPoints.last()->rotation = rot;
	controlPoints.last()->mesh = &controlPointMesh;
	setChild(controlPoints.last());
}

void Track::removePoint(int pointID){
	for(int i=0;i<controlPoints.size();++i){
		if(controlPoints[i]->id == pointID){
			deleteChild(controlPoints[i]);
			delete controlPoints[i];
			controlPoints.remove(i);
			return;
		}
	}
	deleteChild(controlPoints.last());
	delete controlPoints.last();
	controlPoints.pop_back();
}

void Track::addTrain(){

}

void Track::removeTrain(){

}
