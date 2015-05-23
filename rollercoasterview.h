#ifndef ROLLERCOASTERVIEW_H
#define ROLLERCOASTERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QTime>
#include <QStatusBar>
#include "transform.h"
#include "gameobject.h"
#include "camera.h"
#include "light.h"
#include "track.h"
#include "vec.h"
#include "mat.h"

typedef struct{
	GLuint Kd;
	GLuint Ka;
	GLuint Ks;
	GLuint Ns;
	GLuint UseTexture;
}uniformMtl;

class RollerCoasterView : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT

public:
	RollerCoasterView(QWidget *parent);
	~RollerCoasterView();

signals:
	void getLastFPS(QString);

protected:
	void initProgram(int program);
	void drawProgram(int program);
	void drawGameObject(GameObject &o, GLuint uMM, uniformMtl* uMtl=NULL, Transform p=Transform());


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



	Camera* mainCamera;
	Light* mainLight;
	Camera worldCamera;
	Light worldLight;
	Mesh testm;
	GameObject a;
	GameObject b;
	Track track;
	GameObject root;
	bool isLine;

protected:

private:

	QTime elapsedTime;
	unsigned int frameNumber;

	int mPPX;//mouse press position X
	int mPPY;//mouse press position Y
	vec3 mPCP;//mouse press camera position
	vec3 mPCR;//mouse press camera rotation


	//OpenGL
	int width;
	int height;

	enum {modelVAO, NumVAOs};
	enum {PositionBuffer, UVBuffer, NormalBuffer, NumBuffers};
	enum {vPosition, vUV, vNormal};
//	enum {uModelMatrix, uViewMatrix, uProjectionMatrix, uLightPosition, uEyePosition, uKa, uKd, uKs, uNs, uTex, uUseTexture, NumUniforms};
	enum {progMain, progShadow, progToon};

	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];

	GLuint mainProgram;
	GLuint uMainModelMatrix;
	GLuint uMainViewMatrix;
	GLuint uMainProjectionMatrix;
	GLuint uMainLightDirection;
	GLuint uMainEyePosition;
	uniformMtl uMainMtl;

	GLuint ShadowMainProgram;
	GLuint uShadowMainModelMatrix;
	GLuint uShadowMainViewMatrix;
	GLuint uShadowMainProjectionMatrix;
	GLuint uShadowMainShadowMatrix;
	GLuint uShadowMainLightDirection;
	GLuint uShadowMainEyePosition;
	uniformMtl uShadowMainMtl;

	GLuint shadowMapProgram;
	GLuint uShadowMapMMatrix;
	GLuint uShadowMapVPMatrix;
	GLuint shadowMapTexture;
	GLuint shadowMapFBO;
};

#endif // ROLLERCOASTERVIEW_H
