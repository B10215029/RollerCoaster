#ifndef ROLLERCOASTERVIEW_H
#define ROLLERCOASTERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include "gameobject.h"
#include "camera.h"
#include "Track.h"
#include "vec3.h"

class RollerCoasterView : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
public:
	RollerCoasterView(QWidget *parent);
	~RollerCoasterView();

//	void initialize();
//	void drawTrack();
//	void planTrack();

//	void updateTrain(float deltatime);

	float getLastFPS();

protected:
//	//initialize
//	void initSceneManager();
//	void initCamera();
//	void initTrack();
//	void initTrain();
//	void initLight();
//	void initTerrain();

//	void drawSimpleTrack();
//	void drawRoadRails();
//	void drawParallelRails();

//	void planLinear();
//	void planCardinal();
//	void planCubic();
	void drawGameObject(GameObject& o, vec3 worldPos = vec3(), vec3 worldRot = vec3(), vec3 worldSca = vec3());

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
//	//enum
//	enum {eWorld, eTop, eTrain};
//	enum {eLinear, eCardinal, eCubic};
//	enum {eLine, eTrack ,eRoad};

//	//Flag
//	bool playFlag;
//	bool arcLengthFlag;
//	bool shadowFlag;
//	bool lightingFlag;
//	bool driverFlag;
//	bool peopleFlag;
//	int cameraType;
//	int curveType;
//	int trainType;


//	//argument
//	float speed;

//	//Data
//	vec3 trainPosition;
//	vec3 cameraPosition;

	Camera* mainCamera;
	Camera* mainLight;
	Camera worldCamera;
	Camera worldLight;
	Model testm;

protected:

private:

	//OpenGL
	int width;
	int height;

	enum {trang, NumVAOs};
	enum {PositionBuffer, UVBuffer, NormalBuffer, NumBuffers};
	enum {vPosition, vUV, vNormal};

	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];

	GLuint mainProgram;
	GLuint uMainModelMatrix;
	GLuint uMainViewMatrix;
	GLuint uMainProjectionMatrix;
	GLuint uMainLightPosition;
	GLuint uMainEyePosition;
	GLuint uMainKa;
	GLuint uMainKd;
	GLuint uMainKs;
	GLuint uMainNs;


	GLuint program;
	GLfloat v[2];
	int t;
	bool rotate;
	GLuint offsetMatrix;
};

#endif // ROLLERCOASTERVIEW_H
