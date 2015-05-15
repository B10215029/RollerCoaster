#ifndef ROLLERCOASTERVIEW_H
#define ROLLERCOASTERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QTime>
#include <QStatusBar>
#include "gameobject.h"
#include "camera.h"
#include "Track.h"
#include "vec3.h"

class RollerCoasterView : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT

public:
	RollerCoasterView(QWidget *parent);
	~RollerCoasterView();

signals:
	void getLastFPS(QString);

protected:
	void drawGameObject(GameObject &o, GameObject &p=GameObject());

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
	GLuint depth_texture;
	GLuint depth_fbo;
	GLuint render_light_prog;
	GLuint uMVPMatrix;



	Camera* mainCamera;
	Camera* mainLight;
	Camera worldCamera;
	Camera worldLight;
	Model testm;
	GameObject a;
	GameObject b;
	GameObject root;

protected:

private:
	QTime elapsedTime;
	unsigned int frameNumber;


	//OpenGL
	int width;
	int height;

	enum {trang, NumVAOs};
	enum {PositionBuffer, UVBuffer, NormalBuffer, NumBuffers};
	enum {vPosition, vUV, vNormal};
	enum {uModelMatrix, uViewMatrix, uProjectionMatrix, uLightPosition, uEyePosition, uKa, uKd, uKs, uNs, uTex, uUseTexture, NumUniforms};

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
	GLuint uMainTex;
	GLuint uMainUseTexture;
	GLuint uMainShadowMatrix;





};

#endif // ROLLERCOASTERVIEW_H
