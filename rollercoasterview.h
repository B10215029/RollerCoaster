#ifndef ROLLERCOASTERVIEW_H
#define ROLLERCOASTERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

class RollerCoasterView : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
public:
	RollerCoasterView(QWidget *parent);
	~RollerCoasterView();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);
	void mousePressEvent(QMouseEvent *event);
private:
	GLuint Buffers[1];
	GLuint program;
	GLfloat v[2];
	int t;
	bool rotate;
	GLuint offsetMatrix;
};

#endif // ROLLERCOASTERVIEW_H
