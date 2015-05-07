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
	mainLight = &worldLight;
	testm.loadOBJ("C:/Users/Delin/Desktop/model/Deadpool/DeadPool.obj");

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
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[trang]);

	glGenBuffers(NumBuffers, Buffers);

	mainProgram = loadShaders(":/shaders/main.vert",":/shaders/main.frag");
	glUseProgram(mainProgram);
	uMainModelMatrix = glGetUniformLocation(mainProgram, "modelMatrix");
	uMainViewMatrix = glGetUniformLocation(mainProgram, "viewMatrix");
	uMainProjectionMatrix = glGetUniformLocation(mainProgram, "projectionMatrix");
	uMainLightPosition = glGetUniformLocation(mainProgram, "lightPosition");
	uMainEyePosition = glGetUniformLocation(mainProgram, "eyePosition");
	uMainKa = glGetUniformLocation(mainProgram, "Ka");
	uMainKd = glGetUniformLocation(mainProgram, "Kd");
	uMainKs = glGetUniformLocation(mainProgram, "Ks");
	uMainNs = glGetUniformLocation(mainProgram, "Ns");

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vUV);
	glEnableVertexAttribArray(vNormal);

}

void RollerCoasterView::resizeGL(int w, int h){
	width = w;
	height = h;
	glViewport(0,0,w,h);
	worldCamera.position = vec3(0, 50, 50);
	worldCamera.fov = 80;
	worldCamera.aspect = (float)width/height;
	worldCamera.znear = 0.1f;
	worldCamera.zfar = 100;
	worldLight.position = vec3(40.0f, 40.0f, 40.0f);
}

void RollerCoasterView::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUniformMatrix4fv(uMainModelMatrix, 1, GL_FALSE, mat4(1).data);
	glUniformMatrix4fv(uMainViewMatrix, 1, GL_FALSE, mainCamera->lookAt(vec3(0,50,0),vec3(0,1,0)).data);
	glUniformMatrix4fv(uMainProjectionMatrix, 1, GL_FALSE, mainCamera->perspective().data);
	glUniform3fv(uMainLightPosition, 1 , mainLight->position.data);
	glUniform3fv(uMainEyePosition, 1 , mainCamera->position.data);


	for(int i=0;i<testm.materials.size();++i){
		glUniform3fv(uMainKa, 1 , testm.materials[i].Ka.data);
		glUniform3fv(uMainKd, 1 , testm.materials[i].Kd.data);
		glUniform3fv(uMainKs, 1 , testm.materials[i].Ks.data);
		glUniform1f(uMainNs, testm.materials[i].Ns);

//		glVertexAttribPointer自動偵測陣列大小錯誤(sizeof(float*)=4)
//		不知如何直接指定glVertexAttribPointer大小只好先丟到VBO指定大小
//		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)testm.mtlFV[i]);
//		glVertexAttribPointer(vUV, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)testm.mtlFT[i]);
//		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)testm.mtlFN[i]);

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*testm.faces[i].size()*3*3, testm.mtlFV[i], GL_STATIC_DRAW);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*testm.faces[i].size()*3*2, testm.mtlFT[i], GL_STATIC_DRAW);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*testm.faces[i].size()*3*3, testm.mtlFN[i], GL_STATIC_DRAW);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, testm.faces[i].size()*3);

	}




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
