#ifndef ROLLERCOASTERVIEW_H
#define ROLLERCOASTERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include "Track.h"

class RollerCoasterView : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
public:
	RollerCoasterView(QWidget *parent);
	~RollerCoasterView();

	void initialize();
	void drawTrack();
	void planTrack();

	void updateTrain(float deltatime);

	float getLastFPS();

protected:
	//initialize
	void initSceneManager();
	void initCamera();
	void initTrack();
	void initTrain();
	void initLight();
	void initTerrain();

	void drawSimpleTrack();
	void drawRoadRails();
	void drawParallelRails();

	void planLinear();
	void planCardinal();
	void planCubic();

	//Event
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	//OpenGL
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);
private:

//variable
public:
	//enum
	enum {eWorld, eTop, eTrain};
	enum {eLinear, eCardinal, eCubic};
	enum {eLine, eTrack ,eRoad};

	//Flag
	bool playFlag;
	bool arcLengthFlag;
	bool shadowFlag;
	bool lightingFlag;
	bool driverFlag;
	bool peopleFlag;
	int cameraType;
	int curveType;
	int trainType;


	//argument
	float speed;

	//Data
	vec3 trainPosition;
	vec3 cameraPosition;

protected:

private:

	//OpenGL
	GLuint Buffers[1];
	GLuint program;
	GLfloat v[2];
	int t;
	bool rotate;
	GLuint offsetMatrix;
};

#endif // ROLLERCOASTERVIEW_H
