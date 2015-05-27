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
	selectControlPointMesh.loadOBJ(":/models/controlPoint2.obj");
	controlPoints.clear();
	trains.clear();
	trackType = TrackType;
	curveType = CardinalType;
	driving = true;
	trainSpeed = 100;
	addPoint(vec3(50, 10, 0));
	addPoint(vec3(0, 10, 50));
	addPoint(vec3(-50, 10, 0));
	addPoint(vec3(0, 10, -50));
//	trainCamera.setFrustum(-10, 10 ,-10, 10, -1000, 1000);
	update();
}

Track::~Track(){
	delete mesh;
	for(int i=0;i<controlPoints.size();++i)
		delete controlPoints[i];
	for(int i=0;i<trains.size();++i)
		delete trains[i];
	for(int i=0;i<trainModel.size();++i)
		delete trainModel[i];
}

void Track::update(){
	getTrackLength();
	mesh->clear();
	mesh->materialName.insert(QString("steel"), mesh->materialName.size());
	mesh->materialName.insert(QString("woold"), mesh->materialName.size());
	mesh->materials.push_back(material());
	mesh->materials.push_back(material());
	mesh->faces.push_back(QVector<QVector<VerticesData> >());
	mesh->faces.push_back(QVector<QVector<VerticesData> >());
	mesh->materials[0].Kd = vec3(0.8f, 0.8f, 0.8f);
	mesh->materials[0].Ka = vec3(0.2f, 0.2f, 0.2f);
	mesh->materials[0].Ks = vec3(0.9f, 0.9f, 0.9f);
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
	Transform fsp = getCurvePosition(1, controlPoints.size()-1);
	mat4 fsprm = fsp.rotateMat();
	switch(trackType){
	case LineType:
		mesh->vertices.push_back(fsp.position+vec3( 0.1f, 0.1f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-0.1f, 0.1f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-0.1f,-0.1f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3( 0.1f,-0.1f, 0)*fsprm);
		for(int i=0;i<controlPoints.size();i++){
			Transform sp = getCurvePosition(0, i);
			Transform ep;
			float currentTrackLength = trackLength[i]-(i==0?0:trackLength[i-1]);
			for(int j=0;j<currentTrackLength;++j){
				ep = getCurvePosition(1/currentTrackLength*(j+1), i);
				mat4 rm = ep.rotateMat();
				mesh->vertices.push_back(ep.position+vec3( 0.1f, 0.1f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-0.1f, 0.1f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-0.1f,-0.1f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 0.1f,-0.1f, 0)*rm);
				int v0a[] = {-4, -4, -3, -3, -2, -2, -1, -1};
				int v1a[] = {-8, -3, -7, -2, -6, -1, -5, -4};
				int v2a[] = {-5, -8, -8, -7, -7, -6, -6, -5};
				int na[] = {0, 1, 1, 2, 2, 3, 3, 0};
				for(int k=0;k<8;++k){
					QVector<VerticesData> face;
					VerticesData v0 = {mesh->vertices.size() + v0a[k], -1, na[k]};
					VerticesData v1 = {mesh->vertices.size() + v1a[k], -1, na[k]};
					VerticesData v2 = {mesh->vertices.size() + v2a[k], -1, na[k]};
					face.push_back(v0);
					face.push_back(v1);
					face.push_back(v2);
					mesh->faces[0].push_back(face);
				}
				sp = ep;
			}
		}
		mesh->update();
		break;
	case TrackType:
		mesh->vertices.push_back(fsp.position+vec3( 3.5f, 0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3( 2.5f, 0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3( 2.5f,-0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3( 3.5f,-0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-2.5f, 0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-3.5f, 0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-3.5f,-0.5f, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-2.5f,-0.5f, 0)*fsprm);
		for(int i=0;i<controlPoints.size();i++){
			Transform sp = getCurvePosition(0, i);
			Transform ep;
			float currentTrackLength = trackLength[i]-(i==0?0:trackLength[i-1]);
			for(int j=0;j<currentTrackLength;++j){
				ep = getCurvePosition(1/currentTrackLength*(j+1), i);
				mat4 rm = ep.rotateMat();
				mesh->vertices.push_back(ep.position+vec3( 3.5f, 0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 2.5f, 0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 2.5f,-0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 3.5f,-0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-2.5f, 0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-3.5f, 0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-3.5f,-0.5f, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-2.5f,-0.5f, 0)*rm);
				int v0a[] = {- 4, - 4, - 3, - 3, - 2, - 2, - 1, - 1};
				int v1a[] = {-12, - 3, -11, - 2, -10, - 1, - 9, - 4};
				int v2a[] = {- 9, -12, -12, -11, -11, -10, -10, - 9};
				int v3a[] = {- 8, - 8, - 7, - 7, - 6, - 6, - 5, - 5};
				int v4a[] = {-16, - 7, -15, - 6, -14, - 5, - 13, - 8};
				int v5a[] = {- 13, -16, -16, -15, -15, -14, -14, - 13};
				int na[] = {0, 1, 1, 2, 2, 3, 3, 0};
				for(int k=0;k<8;++k){
					QVector<VerticesData> face1,face2;
					VerticesData v0 = {mesh->vertices.size() + v0a[k], -1, na[k]};
					VerticesData v1 = {mesh->vertices.size() + v1a[k], -1, na[k]};
					VerticesData v2 = {mesh->vertices.size() + v2a[k], -1, na[k]};
					VerticesData v3 = {mesh->vertices.size() + v3a[k], -1, na[k]};
					VerticesData v4 = {mesh->vertices.size() + v4a[k], -1, na[k]};
					VerticesData v5 = {mesh->vertices.size() + v5a[k], -1, na[k]};
					face1.push_back(v0);
					face1.push_back(v1);
					face1.push_back(v2);
					face2.push_back(v3);
					face2.push_back(v4);
					face2.push_back(v5);
					mesh->faces[0].push_back(face1);
					mesh->faces[0].push_back(face2);
				}
				sp = ep;
			}
		}
		for(int i=0;i<controlPoints.size();i++){
			float currentTrackLength = trackLength[i]-(i==0?0:trackLength[i-1]);
			for(int j=1;j<currentTrackLength/10;++j){
				Transform sp = getCurvePosition(10/currentTrackLength*j, i);
				mat4 rm = sp.rotateMat();
				mesh->vertices.push_back(sp.position+vec3( 5, 0, 1)*rm);
				mesh->vertices.push_back(sp.position+vec3(-5, 0, 1)*rm);
				mesh->vertices.push_back(sp.position+vec3(-5, 0,-1)*rm);
				mesh->vertices.push_back(sp.position+vec3( 5, 0,-1)*rm);
				for(int k=0;k<8;++k){
					QVector<VerticesData> face1,face2;
					VerticesData v0 = {mesh->vertices.size() -4, -1, 1};
					VerticesData v1 = {mesh->vertices.size() -3, -1, 1};
					VerticesData v2 = {mesh->vertices.size() -2, -1, 1};
					VerticesData v3 = {mesh->vertices.size() -1, -1, 1};
					face1.push_back(v0);
					face1.push_back(v2);
					face1.push_back(v1);
					face2.push_back(v0);
					face2.push_back(v3);
					face2.push_back(v2);
					mesh->faces[1].push_back(face1);
					mesh->faces[1].push_back(face2);
				}
			}
		}
		mesh->update();
		break;
	case RoadType:
		mesh->vertices.push_back(fsp.position+vec3( 5, 0.5, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-5, 0.5, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3(-5,-0.5, 0)*fsprm);
		mesh->vertices.push_back(fsp.position+vec3( 5,-0.5, 0)*fsprm);
		for(int i=0;i<controlPoints.size();i++){
			Transform sp = getCurvePosition(0, i);
			Transform ep;
			float currentTrackLength = trackLength[i]-(i==0?0:trackLength[i-1]);
			for(int j=0;j<currentTrackLength;++j){
				ep = getCurvePosition(1/currentTrackLength*(j+1), i);
				mat4 rm = ep.rotateMat();
				mesh->vertices.push_back(ep.position+vec3( 5, 0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-5, 0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3(-5,-0.5, 0)*rm);
				mesh->vertices.push_back(ep.position+vec3( 5,-0.5, 0)*rm);
				int v0a[] = {-4, -4, -3, -3, -2, -2, -1, -1};
				int v1a[] = {-8, -3, -7, -2, -6, -1, -5, -4};
				int v2a[] = {-5, -8, -8, -7, -7, -6, -6, -5};
				int na[] = {0, 1, 1, 2, 2, 3, 3, 0};
				for(int k=0;k<8;++k){
					QVector<VerticesData> face;
					VerticesData v0 = {mesh->vertices.size() + v0a[k], -1, na[k]};
					VerticesData v1 = {mesh->vertices.size() + v1a[k], -1, na[k]};
					VerticesData v2 = {mesh->vertices.size() + v2a[k], -1, na[k]};
					face.push_back(v0);
					face.push_back(v1);
					face.push_back(v2);
					mesh->faces[1].push_back(face);
				}
				sp = ep;
			}
		}
		mesh->update();
		break;
	}

}

Transform Track::getCurvePosition(float t, int sp){
	Transform r;
	int p1 = (sp+controlPoints.size()-1)%controlPoints.size();
	int p2 = (sp+controlPoints.size()+0)%controlPoints.size();
	int p3 = (sp+controlPoints.size()+1)%controlPoints.size();
	int p4 = (sp+controlPoints.size()+2)%controlPoints.size();
	vec3 v;
	mat4 g,m;
	vec4 tv(t*t*t, t*t, t, 1);
	vec4 dtv(3*t*t, 2*t, 1, 0);
	switch(curveType){
	case LinearType:
		v = controlPoints[p3]->position - controlPoints[p2]->position;
		r.position = controlPoints[p2]->position + v*t;
		break;
	case CardinalType:
		g.data[0] = controlPoints[p1]->position.x();
		g.data[1] = controlPoints[p2]->position.x();
		g.data[2] = controlPoints[p3]->position.x();
		g.data[3] = controlPoints[p4]->position.x();
		g.data[4] = controlPoints[p1]->position.y();
		g.data[5] = controlPoints[p2]->position.y();
		g.data[6] = controlPoints[p3]->position.y();
		g.data[7] = controlPoints[p4]->position.y();
		g.data[8] = controlPoints[p1]->position.z();
		g.data[9] = controlPoints[p2]->position.z();
		g.data[10] = controlPoints[p3]->position.z();
		g.data[11] = controlPoints[p4]->position.z();
		m = mat4(-0.5, 1.0,-0.5, 0.0,
				  1.5,-2.5, 0.0, 1.0,
				 -1.5, 2.0, 0.5, 0.0,
				  0.5,-0.5, 0.0, 0.0);
		r.position = ((g*m)*tv).xyz();
		v = ((g*m)*dtv).xyz();
		break;
	case CubicType:
		g.data[0] = controlPoints[p1]->position.x();
		g.data[1] = controlPoints[p2]->position.x();
		g.data[2] = controlPoints[p3]->position.x();
		g.data[3] = controlPoints[p4]->position.x();
		g.data[4] = controlPoints[p1]->position.y();
		g.data[5] = controlPoints[p2]->position.y();
		g.data[6] = controlPoints[p3]->position.y();
		g.data[7] = controlPoints[p4]->position.y();
		g.data[8] = controlPoints[p1]->position.z();
		g.data[9] = controlPoints[p2]->position.z();
		g.data[10] = controlPoints[p3]->position.z();
		g.data[11] = controlPoints[p4]->position.z();
		m = mat4(-1/6.0, 3/6.0,-3/6.0, 1/6.0,
				  3/6.0,-6/6.0, 0/6.0, 4/6.0,
				 -3/6.0, 3/6.0, 3/6.0, 1/6.0,
				  1/6.0, 0/6.0, 0/6.0, 0/6.0);
		r.position = ((g*m)*tv).xyz();
		v = ((g*m)*dtv).xyz();
		break;
	}
	r.rotation.x() = DEGREE(asin(v.y()/v.length()))*(v.z()<0?-1:1);
	r.rotation.y() = (DEGREE(atan(-v.x()/(-v.z())))+(v.z()>0?180:0))*-1;
	r.rotation.z() = 0;
	return r;
}

void Track::getTrackLength(){
	trackLength.clear();
	switch(curveType){
	case LinearType:
		for(int i=0;i<controlPoints.size();++i)
			trackLength.append((i==0?0:trackLength.last())+distance(controlPoints[i]->position, controlPoints[(i+1)%controlPoints.size()]->position));
		break;
	case CardinalType:
		for(int i=0;i<controlPoints.size();++i)
			trackLength.append((i==0?0:trackLength.last())+distance(controlPoints[i]->position, controlPoints[(i+1)%controlPoints.size()]->position));
		break;
	case CubicType:
		for(int i=0;i<controlPoints.size();++i)
			trackLength.append((i==0?0:trackLength.last())+distance(controlPoints[i]->position, controlPoints[(i+1)%controlPoints.size()]->position));
		break;
	}
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
//		QStringList words = data.readLine().split(QRegExp("\\s+"));
		QStringList words = data.readLine().split(' ');
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
	data << controlPoints.size() << "\r\n";
	for(int i=0; i<controlPoints.size(); ++i)
		data << controlPoints[i]->position.x() << " "
			 << controlPoints[i]->position.y() << " "
			 << controlPoints[i]->position.z() << " "
			 << controlPoints[i]->rotation.x() << " "
			 << controlPoints[i]->rotation.y() << " "
			 << controlPoints[i]->rotation.z() << "\r\n";
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
//	for(int i=0;i<controlPoints.size();++i){
//		if(controlPoints[i]->id == pointID){
//			deleteChild(controlPoints[i]);
//			delete controlPoints[i];
//			controlPoints.remove(i);
//			return;
//		}
//	}
	if(controlPoints.size()<=4) return;
	if(pointID>=0 && pointID<controlPoints.size()){
		deleteChild(controlPoints[pointID]);
		delete controlPoints[pointID];
		controlPoints.remove(pointID);
	}
	else{
		deleteChild(controlPoints.last());
		delete controlPoints.last();
		controlPoints.pop_back();
	}
}

void Track::addTrain(){
	trains.append(new GameObject());
	setChild(trains.last());
	trainPos.append(0);
//	trains.last()->scale = vec3(10,10,10);
}

void Track::removeTrain(){

}

void Track::setTrain(int trainID, int modelID, float pos){
	if(modelID == 100){
		trains[trainID]->mesh = NULL;
		trains[trainID]->setChild(new GameObject());
		trains[trainID]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->children[1]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->children[2]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->children[3]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->children[4]->setChild(new GameObject());
		trains[trainID]->children[0]->children[0]->mesh = new Mesh(":/models/model/robot/body.obj");
		trains[trainID]->children[0]->children[0]->children[0]->mesh = new Mesh(":/models/model/robot/head.obj");
		trains[trainID]->children[0]->children[0]->children[1]->mesh = new Mesh(":/models/model/robot/handUL.obj");
		trains[trainID]->children[0]->children[0]->children[2]->mesh = new Mesh(":/models/model/robot/handUR.obj");
		trains[trainID]->children[0]->children[0]->children[1]->children[0]->mesh = new Mesh(":/models/model/robot/handDL.obj");
		trains[trainID]->children[0]->children[0]->children[2]->children[0]->mesh = new Mesh(":/models/model/robot/handDR.obj");
		trains[trainID]->children[0]->children[0]->children[3]->mesh = new Mesh(":/models/model/robot/footUL.obj");
		trains[trainID]->children[0]->children[0]->children[4]->mesh = new Mesh(":/models/model/robot/footUR.obj");
		trains[trainID]->children[0]->children[0]->children[3]->children[0]->mesh = new Mesh(":/models/model/robot/footDL.obj");
		trains[trainID]->children[0]->children[0]->children[4]->children[0]->mesh = new Mesh(":/models/model/robot/footDR.obj");
		trains[trainID]->children[0]->children[0]->position = vec3(0,0,0);
		trains[trainID]->children[0]->children[0]->children[0]->position = vec3(0,3.122,-0.809);
		trains[trainID]->children[0]->children[0]->children[1]->position = vec3(3.093,1.496,0.316);
		trains[trainID]->children[0]->children[0]->children[2]->position = vec3(-3.057,1.511,0.308);
		trains[trainID]->children[0]->children[0]->children[1]->children[0]->position = vec3(1.541,-3.31,0);
		trains[trainID]->children[0]->children[0]->children[2]->children[0]->position = vec3(-1.58,-3.341,0);
		trains[trainID]->children[0]->children[0]->children[3]->position = vec3(1.954,-3.699,-0.124);
		trains[trainID]->children[0]->children[0]->children[4]->position = vec3(-1.954,-3.699,-0.124);
		trains[trainID]->children[0]->children[0]->children[3]->children[0]->position = vec3(0.428,-4.586,0.118);
		trains[trainID]->children[0]->children[0]->children[4]->children[0]->position = vec3(-0.428,-4.586,0.118);
		trains[trainID]->children[0]->position = vec3(0,12,0);
		trains[trainID]->children[0]->rotation = vec3(0,180,0);
		trains[trainID]->children[0]->animationType = GameObject::AnimRobot;
		trains[trainID]->children[0]->name = QString("robot");
		trainPos[trainID] = pos;
		return;
	}
	trains[trainID]->mesh = trainModel[modelID];
	trainPos[trainID] = pos;
}

void Track::animation(float t){
	if(!driving) return;
	for(int i=0;i<trains.size();++i){
		int p;
		float lot=t*trainSpeed+trainPos[i];
		while(lot>trackLength.last())
			lot-=trackLength.last();
		for(p=0;p<trackLength.size();++p)
			if(trackLength[p]>lot)
				break;
		float pt=lot-(p==0?0:trackLength[p-1]);
		pt/=trackLength[p]-(p==0?0:trackLength[p-1]);
		trains[i]->position = getCurvePosition(pt, p).position;
		trains[i]->rotation = getCurvePosition(pt, p).rotation;
//		trainCamera.position = trains[i]->position;
//		trainCamera.rotation = trains[i]->rotation;// + vec3(0, 90, 0);
//		trainPos[i]=t*100+i*100;
//		while(trainPos[i]>trackLength.last())
//			trainPos[i]-=trackLength.last();
	}

}
