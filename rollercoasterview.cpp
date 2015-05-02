#include "rollercoasterview.h"
#include <QFile>
#include <QString>
#include <iostream>
#include <vector>
#include <string>

RollerCoasterView::RollerCoasterView(QWidget *parent) : QOpenGLWidget(parent){
	t=0;
	rotate=true;
}

RollerCoasterView::~RollerCoasterView(){

}
void RollerCoasterView::initialize(){
	initSceneManager();
	initCamera();
	initTrack();
	initTrain();
	initLight();
	initTerrain();
}

void RollerCoasterView::initSceneManager(){

}

void RollerCoasterView::initCamera(){

}

void RollerCoasterView::initTrack(){

}

void RollerCoasterView::initTrain(){

}

void RollerCoasterView::initLight(){

}

void RollerCoasterView::initTerrain(){

}

void RollerCoasterView::drawTrack(){

}

void RollerCoasterView::drawSimpleTrack(){

}

void RollerCoasterView::drawRoadRails(){

}

void RollerCoasterView::drawParallelRails(){

}

void RollerCoasterView::planTrack(){

}

void RollerCoasterView::planLinear(){

}

void RollerCoasterView::planCardinal(){

}

void RollerCoasterView::planCubic(){

}

void RollerCoasterView::updateTrain(float deltatime){

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
	v[0] = 0;
	v[1] = 0.866;
	//v[1] = 1;
	GLubyte vertex_indices[]={0,1,2,3,4,5};
	program = loadShaders(":/shaders/rollercoasterview.vert",":/shaders/rollercoasterview.frag");
	glUseProgram(program);
	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);
	offsetMatrix=glGetUniformLocation(program,"offsetMat");
}

void RollerCoasterView::resizeGL(int w, int h){
	glViewport(0,0,w,h);
}

void RollerCoasterView::paintGL(){
	GLfloat Black[] = {0,0,0,1};
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glClearBufferfv(GL_COLOR,0,Black);
	if(rotate){
		GLfloat temp=v[0];
		v[0] = v[0]*cosf(0.01)+v[1]*sinf(0.01);
		v[1] = temp*-sinf(0.01)+v[1]*cosf(0.01);
	}
	if(t%33==0){
		GLfloat temp=v[0];
		v[0] = v[0]*cosf(3.1415926/3)+v[1]*sinf(3.1415926/3);
		v[1] = temp*-sinf(3.1415926/3)+v[1]*cosf(3.1415926/3);
	}
	float matr[16]={v[0],-v[1],0,0,v[1],v[0],0,0,0,0,1,0,0,0,0,1};
	glUniformMatrix4fv(offsetMatrix, 1, GL_FALSE, matr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[0]);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL, 6);
	t++;
	this->update();
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
