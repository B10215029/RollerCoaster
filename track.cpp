#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#ifndef RADIAN
#define RADIAN(x) (x*(PI/180.0))
#endif
#ifndef DEGREE
#define DEGREE(x) (x*(180.0/PI))
#endif

#include "track.h"
#include <cmath>
#include <QFile>
#include <QTextStream>

Track::Track():GameObject(){
	mesh = new Mesh();
	controlPointMesh.loadOBJ(":/models/controlPoint.obj");
	controlPoints.clear();
	trains.clear();
	trackType = TrackType;
	curveType = CardinalType;
	driving = false;
	addPoint(vec3(50, 10, 0));
	addPoint(vec3(0, 10, 50));
	addPoint(vec3(-50, 10, 0));
	addPoint(vec3(0, 10, -50));
	trackType = LineType;
	curveType = LinearType;
	trackType = RoadType;
	loadFile(QString("C:/Users/Delin/Desktop/Train2008/TrackFiles/spiral.txt"));
}

Track::~Track(){
	delete mesh;
}

void Track::update(){
	mesh->clear();
	mesh->materialName.insert(QString("steel"), mesh->materialName.size());
	mesh->materialName.insert(QString("woold"), mesh->materialName.size());
	mesh->materials.push_back(material());
	mesh->materials.push_back(material());
	mesh->faces.push_back(QVector<QVector<VerticesData>>());
	mesh->faces.push_back(QVector<QVector<VerticesData>>());
	mesh->materials[0].Kd = vec3(0.8, 0.8, 0.8);
	mesh->materials[0].Ka = vec3(0.2, 0.2, 0.2);
	mesh->materials[0].Ks = vec3(0.9, 0.9, 0.9);
	mesh->materials[0].Ns = 50;
	mesh->materials[0].texture = -1;
	mesh->materials[1].Kd = vec3(1, 0.75, 0.5);
	mesh->materials[1].Ka = vec3(0, 0, 0);
	mesh->materials[1].Ks = vec3(0, 0, 0);
	mesh->materials[1].Ns = 50;
	mesh->materials[1].texture = -1;
	mesh->normals.push_back(vec3( 1, 0, 0));
	mesh->normals.push_back(vec3( 0, 1, 0));
	mesh->normals.push_back(vec3(-1, 0, 0));
	mesh->normals.push_back(vec3( 0,-1, 0));
	switch(trackType){
	case LineType:
		for(int i=0;i<controlPoints.size();i++){
			Transform sp = getCurvePosition(0, i);
			Transform ep;
			mat4 rm = sp.rotateMat();
			mesh->vertices.push_back(sp.position+vec3( 0.1, 0.1, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3(-0.1, 0.1, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3(-0.1,-0.1, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3( 0.1,-0.1, 0)*rm);
			for(int j=0;j<10;++j){
				ep = getCurvePosition(0.1*(j+1), i);
				mat4 rm = ep.rotateMat();
				mesh->vertices.push_back(ep.position+vec3( 0.1, 0.1, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-0.1, 0.1, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-0.1,-0.1, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 0.1,-0.1, 0)*rm);
				QVector<VerticesData> face0;
				VerticesData v00 = {mesh->vertices.size() -4, -1, 0};
				VerticesData v01 = {mesh->vertices.size() -5, -1, 0};
				VerticesData v02 = {mesh->vertices.size() -8, -1, 0};
				face0.push_back(v00);
				face0.push_back(v02);
				face0.push_back(v01);
				mesh->faces[0].push_back(face0);
				QVector<VerticesData> face1;
				VerticesData v10 = {mesh->vertices.size() -4, -1, 1};
				VerticesData v11 = {mesh->vertices.size() -8, -1, 1};
				VerticesData v12 = {mesh->vertices.size() -3, -1, 1};
				face1.push_back(v10);
				face1.push_back(v12);
				face1.push_back(v11);
				mesh->faces[0].push_back(face1);
				QVector<VerticesData> face2;
				VerticesData v20 = {mesh->vertices.size() -3, -1, 1};
				VerticesData v21 = {mesh->vertices.size() -8, -1, 1};
				VerticesData v22 = {mesh->vertices.size() -7, -1, 1};
				face2.push_back(v20);
				face2.push_back(v22);
				face2.push_back(v21);
				mesh->faces[0].push_back(face2);
				QVector<VerticesData> face3;
				VerticesData v30 = {mesh->vertices.size() -3, -1, 2};
				VerticesData v31 = {mesh->vertices.size() -7, -1, 2};
				VerticesData v32 = {mesh->vertices.size() -2, -1, 2};
				face3.push_back(v30);
				face3.push_back(v32);
				face3.push_back(v31);
				mesh->faces[0].push_back(face3);
				QVector<VerticesData> face4;
				VerticesData v40 = {mesh->vertices.size() -2, -1, 2};
				VerticesData v41 = {mesh->vertices.size() -7, -1, 2};
				VerticesData v42 = {mesh->vertices.size() -6, -1, 2};
				face4.push_back(v40);
				face4.push_back(v42);
				face4.push_back(v41);
				mesh->faces[0].push_back(face4);
				QVector<VerticesData> face5;
				VerticesData v50 = {mesh->vertices.size() -2, -1, 3};
				VerticesData v51 = {mesh->vertices.size() -6, -1, 3};
				VerticesData v52 = {mesh->vertices.size() -1, -1, 3};
				face5.push_back(v50);
				face5.push_back(v52);
				face5.push_back(v51);
				mesh->faces[0].push_back(face5);
				QVector<VerticesData> face6;
				VerticesData v60 = {mesh->vertices.size() -1, -1, 3};
				VerticesData v61 = {mesh->vertices.size() -6, -1, 3};
				VerticesData v62 = {mesh->vertices.size() -5, -1, 3};
				face6.push_back(v60);
				face6.push_back(v62);
				face6.push_back(v61);
				mesh->faces[0].push_back(face6);
				QVector<VerticesData> face7;
				VerticesData v70 = {mesh->vertices.size() -1, -1, 0};
				VerticesData v71 = {mesh->vertices.size() -5, -1, 0};
				VerticesData v72 = {mesh->vertices.size() -4, -1, 0};
				face7.push_back(v70);
				face7.push_back(v72);
				face7.push_back(v71);
				mesh->faces[0].push_back(face7);

				sp = ep;
			}
		}
		mesh->update();
		break;
	case TrackType:

		break;
	case RoadType:
		for(int i=0;i<controlPoints.size();i++){
			Transform sp = getCurvePosition(0, i);
			Transform ep;
			mat4 rm = sp.rotateMat();
			mesh->vertices.push_back(sp.position+vec3( 5, 0.5, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3(-5, 0.5, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3(-5,-0.5, 0)*rm);
			mesh->vertices.push_back(sp.position+vec3( 5,-0.5, 0)*rm);
			for(int j=0;j<10;++j){
				ep = getCurvePosition(0.1*(j+1), i);
				mat4 rm = ep.rotateMat();
				mesh->vertices.push_back(ep.position+vec3( 5, 0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-5, 0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-5,-0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 5,-0.5, 0)*rm);
				QVector<VerticesData> face0;
				VerticesData v00 = {mesh->vertices.size() -4, -1, 0};
				VerticesData v01 = {mesh->vertices.size() -5, -1, 0};
				VerticesData v02 = {mesh->vertices.size() -8, -1, 0};
				face0.push_back(v00);
				face0.push_back(v02);
				face0.push_back(v01);
				mesh->faces[1].push_back(face0);
				QVector<VerticesData> face1;
				VerticesData v10 = {mesh->vertices.size() -4, -1, 1};
				VerticesData v11 = {mesh->vertices.size() -8, -1, 1};
				VerticesData v12 = {mesh->vertices.size() -3, -1, 1};
				face1.push_back(v10);
				face1.push_back(v12);
				face1.push_back(v11);
				mesh->faces[1].push_back(face1);
				QVector<VerticesData> face2;
				VerticesData v20 = {mesh->vertices.size() -3, -1, 1};
				VerticesData v21 = {mesh->vertices.size() -8, -1, 1};
				VerticesData v22 = {mesh->vertices.size() -7, -1, 1};
				face2.push_back(v20);
				face2.push_back(v22);
				face2.push_back(v21);
				mesh->faces[1].push_back(face2);
				QVector<VerticesData> face3;
				VerticesData v30 = {mesh->vertices.size() -3, -1, 2};
				VerticesData v31 = {mesh->vertices.size() -7, -1, 2};
				VerticesData v32 = {mesh->vertices.size() -2, -1, 2};
				face3.push_back(v30);
				face3.push_back(v32);
				face3.push_back(v31);
				mesh->faces[1].push_back(face3);
				QVector<VerticesData> face4;
				VerticesData v40 = {mesh->vertices.size() -2, -1, 2};
				VerticesData v41 = {mesh->vertices.size() -7, -1, 2};
				VerticesData v42 = {mesh->vertices.size() -6, -1, 2};
				face4.push_back(v40);
				face4.push_back(v42);
				face4.push_back(v41);
				mesh->faces[1].push_back(face4);
				QVector<VerticesData> face5;
				VerticesData v50 = {mesh->vertices.size() -2, -1, 3};
				VerticesData v51 = {mesh->vertices.size() -6, -1, 3};
				VerticesData v52 = {mesh->vertices.size() -1, -1, 3};
				face5.push_back(v50);
				face5.push_back(v52);
				face5.push_back(v51);
				mesh->faces[1].push_back(face5);
				QVector<VerticesData> face6;
				VerticesData v60 = {mesh->vertices.size() -1, -1, 3};
				VerticesData v61 = {mesh->vertices.size() -6, -1, 3};
				VerticesData v62 = {mesh->vertices.size() -5, -1, 3};
				face6.push_back(v60);
				face6.push_back(v62);
				face6.push_back(v61);
				mesh->faces[1].push_back(face6);
				QVector<VerticesData> face7;
				VerticesData v70 = {mesh->vertices.size() -1, -1, 0};
				VerticesData v71 = {mesh->vertices.size() -5, -1, 0};
				VerticesData v72 = {mesh->vertices.size() -4, -1, 0};
				face7.push_back(v70);
				face7.push_back(v72);
				face7.push_back(v71);
				mesh->faces[1].push_back(face7);

				sp = ep;
			}
		}
		mesh->update();
		break;
	}

}

Transform Track::getCurvePosition(float t, int sp){
	Transform r;
	int p1 = (sp+controlPoints.size())%controlPoints.size();
	int p2 = (sp+controlPoints.size()+1)%controlPoints.size();
	vec3 v = controlPoints[p2]->position - controlPoints[p1]->position;
	switch(curveType){
	case LinearType:
		r.position = controlPoints[p1]->position + v*t;
		r.rotation.x() = DEGREE(atan(-v.y()/fabs(v.z())))*-1;
		r.rotation.y() = (DEGREE(atan(-v.x()/(-v.z())))+(v.z()>0?180:0))*-1;
		r.rotation.z() = 0;
		return r;
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
		QStringList words = data.readLine().split(QRegExp("\\s+"));
		if(words[0][0]=='#'||words.size()<3)
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

void Track::animation(float t){
	update();
	if(!driving) return;

}
