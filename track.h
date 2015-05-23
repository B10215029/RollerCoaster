#ifndef TRACK_H
#define TRACK_H

#include "gameobject.h"
#include "camera.h"
#include "mesh.h"
#include <QVector>

class Track : public GameObject
{
public:
	Track();
	~Track();

	void update();
	Transform getCurvePosition(float t, int sp);
	void getTrackLength();
	void loadFile(QString filePath);
	void saveFile(QString filePath);
	void addPoint();
	void addPoint(vec3 pos, vec3 rot = vec3(0, 0, 0));
	void removePoint(int pointID);
	void addTrain();
	void removeTrain();
	void setTrainModel(int modelID);
	void animation(float t);

	enum {LineType, TrackType, RoadType};
	enum {LinearType, CardinalType, CubicType};
	unsigned int trackType;
	unsigned int curveType;
	QVector<GameObject*> controlPoints;
	QVector<GameObject*> trains;
	QVector<float> trainPos;
	Camera trainCamera;
	Mesh controlPointMesh;
	Mesh selectControlPointMesh;
	QVector<Mesh*> trainModel;
	QVector<float> trackLength;
	bool driving;
};

#endif // TRACK_H
