#include "rollercoasterview.h"
#include <QFile>
#include <QString>
#include <iostream>
#include <vector>
#include <string>

RollerCoasterView::RollerCoasterView(QWidget *parent) : QOpenGLWidget(parent){
	worldCamera = Camera();
	worldLight = Camera();
	mainCamera = &worldCamera;
	testm.loadOBJ("C:/Users/Delin/Desktop/model/Deadpool/DeadPool.obj");

	t=0;
	rotate=true;
}

RollerCoasterView::~RollerCoasterView(){

}

void drawGameObject(GameObject& o, vec3 worldPos, vec3 worldRot, vec3 worldSca){

}

float RollerCoasterView::getLastFPS(){
	return 0;
}

void RollerCoasterView::mousePressEvent(QMouseEvent *event){
	rotate=!rotate;
}

void RollerCoasterView::mouseReleaseEvent(QMouseEvent *event){

}

void RollerCoasterView::mouseMoveEvent(QMouseEvent *event){

}

void RollerCoasterView::mouseDoubleClickEvent(QMouseEvent *event){

}

void RollerCoasterView::wheelEvent(QWheelEvent *event){

}

void RollerCoasterView::keyPressEvent(QKeyEvent *event){

}

void RollerCoasterView::keyReleaseEvent(QKeyEvent *event){

}

void RollerCoasterView::initializeGL(){
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[trang]);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
	float *vertArray=new float[testm.faces.size()*3*3];
	for(int i=0;i<testm.faces.size();++i){
		vertArray[i*9+0] = testm.vertices[testm.faces[i][0].v].x();
		vertArray[i*9+1] = testm.vertices[testm.faces[i][0].v].y();
		vertArray[i*9+2] = testm.vertices[testm.faces[i][0].v].z();
		vertArray[i*9+3] = testm.vertices[testm.faces[i][1].v].x();
		vertArray[i*9+4] = testm.vertices[testm.faces[i][1].v].y();
		vertArray[i*9+5] = testm.vertices[testm.faces[i][1].v].z();
		vertArray[i*9+6] = testm.vertices[testm.faces[i][2].v].x();
		vertArray[i*9+7] = testm.vertices[testm.faces[i][2].v].y();
		vertArray[i*9+8] = testm.vertices[testm.faces[i][2].v].z();
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertArray), vertArray, GL_STATIC_DRAW);
	delete[] vertArray;
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
	float *normArray=new float[testm.faces.size()*3*3];
	for(int i=0;i<testm.faces.size();++i){
		normArray[i*9+0] = testm.normals[testm.faces[i][0].vn].x();
		normArray[i*9+1] = testm.normals[testm.faces[i][0].vn].y();
		normArray[i*9+2] = testm.normals[testm.faces[i][0].vn].z();
		normArray[i*9+3] = testm.normals[testm.faces[i][1].vn].x();
		normArray[i*9+4] = testm.normals[testm.faces[i][1].vn].y();
		normArray[i*9+5] = testm.normals[testm.faces[i][1].vn].z();
		normArray[i*9+6] = testm.normals[testm.faces[i][2].vn].x();
		normArray[i*9+7] = testm.normals[testm.faces[i][2].vn].y();
		normArray[i*9+8] = testm.normals[testm.faces[i][2].vn].z();
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(normArray), normArray, GL_STATIC_DRAW);
	delete[] normArray;
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mainProgram = loadShaders(":/shaders/main.vert",":/shaders/main.frag");
	glUseProgram(mainProgram);
	glGetUniformLocation(uMainModelMatrix, "modelMatrix");
	glGetUniformLocation(uMainViewMatrix, "viewMatrix");
	glGetUniformLocation(uMainProjectionMatrix, "projectionMatrix");
	glGetUniformLocation(uMainLightPosition, "lightPosition");
	glGetUniformLocation(uMainEyePosition, "eyePosition");
	glGetUniformLocation(uMainKa, "Ka");
	glGetUniformLocation(uMainKd, "Kd");
	glGetUniformLocation(uMainKs, "Ks");
	glGetUniformLocation(uMainNs, "Ns");

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vPosition);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vNormal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

void RollerCoasterView::resizeGL(int w, int h){
	width = w;
	height = h;
	glViewport(0,0,w,h);
}

void RollerCoasterView::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUniformMatrix4fv(uMainModelMatrix, 1, GL_FALSE, NULL);
	glUniformMatrix4fv(uMainViewMatrix, 1, GL_FALSE, NULL);
	glUniformMatrix4fv(uMainProjectionMatrix, 1, GL_FALSE, NULL);
	glUniform3fv(uMainLightPosition, 1 , NULL);
	glUniform3fv(uMainEyePosition, 1 , NULL);
	glUniform3fv(uMainKa, 1 , testm.Kas[0].data);
	glUniform3fv(uMainKd, 1 , testm.Kds[0].data);
	glUniform3fv(uMainKs, 1 , testm.Kss[0].data);
	glUniform1f(uMainNs, testm.Nss[0]);

	glDrawArrays(GL_TRIANGLES, 0, testm.faces.size());
	//this->update();
}

GLuint RollerCoasterView::loadShaders(const char* vertexFilePath, const char* fragmentFilePath){
	GLuint program;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	const char* vs_source;
	const char* fs_source;

	// Read the Vertex Shader code from the file
	QFile VertexShaderFile(vertexFilePath);
	if(VertexShaderFile.open(QIODevice::ReadOnly)){
		VertexShaderCode=QString(VertexShaderFile.readAll()).toStdString();
		VertexShaderFile.close();
		vs_source = VertexShaderCode.c_str();
#ifdef _DEBUG
		printf("%s\n",vs_source);
#endif /* DEBUG */
	}
	else{
#ifdef _DEBUG
		printf("Impossible to open %s. Are you in the right directory ?"
			   "Don't forget to read the FAQ !\n", vertexFilePath);
#endif /* DEBUG */
		return 0;
	}

	// Read the Fragment Shader code from the file
	QFile FragmentShaderFile(fragmentFilePath);
	if(FragmentShaderFile.open(QIODevice::ReadOnly)){
		FragmentShaderCode=QString(FragmentShaderFile.readAll()).toStdString();
		FragmentShaderFile.close();
		fs_source = FragmentShaderCode.c_str();
#ifdef _DEBUG
		printf("%s\n",fs_source);
#endif /* DEBUG */
	}
	else{
#ifdef _DEBUG
		printf("Impossible to open %s. Are you in the right directory ?"
			"Don't forget to read the FAQ !\n", fragmentFilePath);
#endif /* DEBUG */
		return 0;
	}

	//compile vertex shader
#ifdef _DEBUG
	printf("Compiling shader : %s\n", vertexFilePath);
#endif /* DEBUG */
	glShaderSource(vs,1,&vs_source,NULL);
	glCompileShader(vs);
	// Compile Fragment Shader
#ifdef _DEBUG
	printf("Compiling shader : %s\n", fragmentFilePath);
#endif /* DEBUG */
	glShaderSource(fs, 1, &fs_source , NULL);
	glCompileShader(fs);

#ifdef _DEBUG
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("in %s:\n%s\n", vertexFilePath, &VertexShaderErrorMessage[0]);
	}

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("in %s:\n%s\n", fragmentFilePath, &FragmentShaderErrorMessage[0]);
	}
#endif /* DEBUG */

	// Link the program
#ifdef _DEBUG
	printf("Linking program\n");
#endif /* DEBUG */
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

#ifdef _DEBUG
	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
#endif /* DEBUG */

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
