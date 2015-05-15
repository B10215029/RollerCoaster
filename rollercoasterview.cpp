#include "rollercoasterview.h"
#include <QFile>
#include <QString>
#include <iostream>
#include <vector>
#include <string>
#define DEPTH_TEXTURE_SIZE 4096

RollerCoasterView::RollerCoasterView(QWidget *parent) : QOpenGLWidget(parent){
	TextureDB::init();
	worldCamera = Camera();
	worldLight = Camera();
	mainCamera = &worldCamera;
	mainLight = &worldLight;
	a.model = &testm;
	b.model = a.model;
	b.position=vec3(0,300,50);
	//a.setChild(&b);
	//testm.loadOBJ("C:/Users/Delin/Desktop/66899_kirby/kirby/kirby2.obj");
	//testm.loadOBJ("C:/Users/Delin/Desktop/model/Deadpool/DeadPool.obj");
	testm.loadOBJ("C:/Users/Delin/Desktop/67700_renamon_v2_6/Renamon_V2.6.obj");
	//testm.loadOBJ("C:/Users/Delin/Desktop/74796_Jibril_by_jugapugz_zip/jibril_by_jugapugz.obj");
	frameNumber = 0;
}

RollerCoasterView::~RollerCoasterView(){

}

void RollerCoasterView::mousePressEvent(QMouseEvent *event){

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
	//glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.5, 0.5, 1.0, 1.0);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

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
	uMainUseTexture = glGetUniformLocation(mainProgram, "useTexture");
	uMainShadowMatrix = glGetUniformLocation(mainProgram, "shadowMatrix");

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vUV);
	glEnableVertexAttribArray(vNormal);

	for(int i=0;i<TextureDB::ID.size();++i){
		glGenTextures(1, &TextureDB::ID[i]);
		glBindTexture(GL_TEXTURE_2D, TextureDB::ID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureDB::image[i].width(), TextureDB::image[i].height(), 0, GL_RGB, GL_UNSIGNED_BYTE, TextureDB::image[i].bits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glBindTexture(GL_TEXTURE_2D, 0);


	//////////////////////////////////////
	//shaders[0].filename="../shader/shadowmapping-light.vs.glsl";
	//shaders[1].filename="../shader/shadowmapping-light.fs.glsl";
	//shadow_lightProgram = LoadShaders(shaders);
	render_light_prog = loadShaders(":/shaders/rollercoasterview.vert",":/shaders/rollercoasterview.frag");
	//glUseProgram(shadow_lightProgram);
	glUseProgram(render_light_prog);
	//u_shadow_mvp = glGetUniformLocation(shadow_lightProgram, "mvp");
	uMVPMatrix = glGetUniformLocation(render_light_prog, "MVPMatrix");
	//glGenFramebuffers(1, &shadow_fbo);
	glGenFramebuffers(1, &depth_fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
	//glGenTextures(1, &shadow_texture);
	glGenTextures(1, &depth_texture);
	//glBindTexture(GL_TEXTURE_2D, shadow_texture);
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	//glTexStorage2D(GL_TEXTURE_2D, 11, GL_DEPTH_COMPONENT32F, 4096, 4096);
	glTexStorage2D(GL_TEXTURE_2D, 11, GL_DEPTH_COMPONENT32F, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_texture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depth_texture, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create a depth texture


	// Allocate storage for the texture data
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	// Set the default filtering modes


	// Set up depth comparison mode


	// Set up wrapping modes
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glBindTexture(GL_TEXTURE_2D, 0);
	// Create FBO to render depth into


	// Attach the depth texture to it

	// Disable color rendering as there are no color attachments
	//glDrawBuffer(GL_NONE);

//	glEnableVertexAttribArray(vPosition);
//	glEnableVertexAttribArray(vUV);
//	glEnableVertexAttribArray(vNormal);

}

void RollerCoasterView::resizeGL(int w, int h){
	width = w;
	height = h;
	glViewport(0,0,w,h);
//	worldCamera.position = vec3(0, 50, 50);
	worldCamera.rotation = vec3(-45,0,0);
	worldCamera.position = vec3(0, 50, 20);
//	worldCamera.rotation = vec3(0,0,0);
	worldCamera.fov = 80;
	worldCamera.aspect = (float)width/height;
	worldCamera.left=-1;
	worldCamera.right=1;
	worldCamera.bottom=-1;
	worldCamera.top=1;
	worldCamera.znear = 0.1f;
	worldCamera.zfar = 100;
	worldLight.position = vec3(20.0f, 20.0f, 20.0f);
	worldLight.left=-1;
	worldLight.right=1;
	worldLight.bottom=-1;
	worldLight.top=1;
	worldLight.znear=1;
	worldLight.zfar=200;
}

void RollerCoasterView::paintGL(){
	static const GLfloat ones[] = { 1.0f };
	static const GLfloat zero[] = { 0.0f };
	static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
//	static const mat4 scale_bias_matrix = mat4(
//		vec4(0.5f, 0.0f, 0.0f, 0.0f),
//		vec4(0.0f, 0.5f, 0.0f, 0.0f),
//		vec4(0.0f, 0.0f, 0.5f, 0.0f),
//		vec4(0.5f, 0.5f, 0.5f, 1.0f)
//		);
	mat4 scale_bias_matrix = mat4(
	0.5f, 0.0f, 0.0f, 0.5f,
	0.0f, 0.5f, 0.0f, 0.5f,
	0.0f, 0.0f, 0.5f, 0.5f,
	0.0f, 0.0f, 0.0f, 1.0f);
	static const GLenum buffs[] = { GL_COLOR_ATTACHMENT0 };
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//vec3 rot_light_position = vec3(lightPposition.x*sin((eyeAngley+60)*3.1415/180), lightPposition.y, lightPposition.z*cos((eyeAngley+60)*3.1415/180));
	vec3 light_position = mainLight->position;
	//mat4 shadow_light_proj_matrix = frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);
	mat4 light_projection_matrix = mainLight->frustum();
	//mat4 shadow_light_view_matrix = lookAt(rot_light_position, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 light_view_matrix = mainLight->lookAt(vec3(0,0,0), vec3(0,1,0));
//	mat4 light_vp_matrix = shadow_light_proj_matrix * shadow_light_view_matrix;

	//mat4 shadow_sbpv_matrix = scale_bias_matrix * shadow_light_proj_matrix * shadow_light_view_matrix;
	mat4 shadow_matrix = scale_bias_matrix * light_projection_matrix * light_view_matrix;

	//glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
	//glViewport(0, 0, 4096, 4096);
	glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(4.0f, 4.0f);
	glPolygonOffset(4.0f, 4.0f);
	//glUseProgram(shadow_lightProgram);
	glUseProgram(render_light_prog);
	//glBindVertexArray(VAO);
	glBindVertexArray(VAOs[trang]);
	///glDrawBuffers(1, buffs);
	glDrawBuffers(1, buffs);
	///glClearBufferfv(GL_COLOR, 0, zero);
	glClearBufferfv(GL_COLOR, 0, zero);
	///glClearBufferfv(GL_DEPTH, 0, ones);
	glClearBufferfv(GL_DEPTH, 0, ones);
//	for (int i = 0,ofs=0; i < PARTSNUM; i++){
//		if((i==BACK&&(disp&1)==0)||((i==WINGL||i==WINGR)&&(disp&2)==0)||(i==FLOOR&&(disp&4)==0)||(disp&8)==0){
//			ofs += vertices_size[i]*sizeof(vec3);
//			continue;
//		}
//		glUniformMatrix4fv(u_shadow_mvp, 1, GL_FALSE, &(light_vp_matrix * Models[i])[0][0]);
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)ofs);
//		ofs += vertices_size[i]*sizeof(vec3);
//		int vertexIDoffset = 0;
//		for(int j = 0;j <mtls[i].size() ;j++){
//			glDrawArrays(GL_TRIANGLES, vertexIDoffset  , faces[i][j+1]*3);
//			vertexIDoffset += faces[i][j+1]*3;
//		}
//	}
	mat4 scene_model_matrix = a.modelMat();
	glUniformMatrix4fv(uMVPMatrix,1, GL_FALSE, (scene_model_matrix * light_view_matrix * light_projection_matrix).data);
	glEnableVertexAttribArray(vPosition);
	for(int i=0;i<a.model->materials.size();++i){
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*a.model->faces[i].size()*3*3, a.model->mtlFV[i], GL_STATIC_DRAW);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, a.model->faces[i].size()*3);
	}
	//glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_POLYGON_OFFSET_FILL);
	//glBindFramebuffer(GL_FRAMEBUFFER, frame_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

	// Time varying light position

	// Matrices for rendering the scene

	// Matrices used when rendering from the light’s position


//	light_view_matrix = mainCamera->view();
//	light_projection_matrix = mainCamera->perspective();
	// Now we render from the light’s position into the depth buffer.
	// Select the appropriate program

//	glUniformMatrix4fv(uMVPMatrix,1, GL_FALSE, (light_projection_matrix * light_view_matrix * scene_model_matrix).data);

	// Bind the "depth only" FBO and set the viewport to the size
	// of the depth texture

//	glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

	// Clear
//	glClearDepth(1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable polygon offset to resolve depth-fighting isuses


	// Draw from the light’s point of view

//	for(int i=0;i<a.model->materials.size();++i){
//		glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*a.model->faces[i].size()*3*3, a.model->mtlFV[i], GL_STATIC_DRAW);
//		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
////		glBindBuffer(GL_ARRAY_BUFFER, Buffers[UVBuffer]);
////		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*a.model->faces[i].size()*3*2, a.model->mtlFT[i], GL_STATIC_DRAW);
////		glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
////		glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
////		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*a.model->faces[i].size()*3*3, a.model->mtlFN[i], GL_STATIC_DRAW);
////		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glDrawArrays(GL_TRIANGLES, 0, a.model->faces[i].size()*3);
//		//glPointSize(100);
//		//glDrawArrays(GL_POINTS, 0, a.model->faces[i].size()*3);
//	}



//	glBindFramebuffer(GL_FRAMEBUFFER, 0);

//	glDrawBuffer(GL_BACK);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glViewport(0,0,w,h);
	glViewport(0,0,width,height);
	//glUseProgram(program);
	glUseProgram(mainProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadow_texture);
	glDrawBuffer(GL_BACK);
	glClearBufferfv(GL_DEPTH, 0, ones);
	float eyey = DOR(eyeAngley);
	View = lookAt(vec3(eyedistance*sin(eyey),2,eyedistance*cos(eyey))+eyePosition, eyePosition, vec3(0,1,0));
	View = lookAt(vec3(0,10,25),vec3(0,0,0),vec3(0,1,0));
	Projection = glm::perspective(80.0f,4.0f/3.0f,0.1f,100.0f);
	glUniformMatrix4fv(u_view, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, &Projection[0][0]);
	glUniform3fv(u_lightPosition, 1, &lightPposition[0]);

//	mat4 scale_bias_matrix = mat4(
//	0.5f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.5f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f);
//	mat4 scale_bias_matrix = mat4(
//	0.5f, 0.0f, 0.0f, 0.5f,
//	0.0f, 0.5f, 0.0f, 0.5f,
//	0.0f, 0.0f, 0.5f, 0.5f,
//	0.0f, 0.0f, 0.0f, 1.0f);
//	mat4 shadow_matrix = scale_bias_matrix * light_projection_matrix * light_view_matrix;
//	mat4 shadow_matrix = light_view_matrix * light_projection_matrix * scale_bias_matrix;
//	mat4 shadow_matrix = scale_bias_matrix * light_view_matrix * light_projection_matrix;



	//////////////////////////////////////////////
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//a.scale=vec3(5.5,5.5,5.5);
	a.scale=vec3(10,10,10);
	//a.scale=vec3(20,20,20);
	//a.scale=vec3(0.5,0.5,0.5);
//	glUniformMatrix4fv(uMainViewMatrix, 1, GL_FALSE, mainLight->lookAt(vec3(0,0,0), vec3(0,1,0)).data);
	glUniformMatrix4fv(uMainViewMatrix, 1, GL_FALSE, mainCamera->view().data);
	glUniformMatrix4fv(uMainProjectionMatrix, 1, GL_FALSE, mainCamera->perspective().data);
//	glUniformMatrix4fv(uMainProjectionMatrix, 1, GL_FALSE, mainLight->frustum().data);
	glUniform3fv(uMainLightPosition, 1 , mainLight->position.data);
//	glUniform3fv(uMainEyePosition, 1 , mainLight->position.data);
	glUniform3fv(uMainEyePosition, 1 , mainCamera->position.data);
	glUniformMatrix4fv(uMainShadowMatrix, 1, GL_FALSE, shadow_matrix.data);

	glBindTexture(GL_TEXTURE_2D, depth_texture);


	drawGameObject(a);


	frameNumber++;

	emit getLastFPS(QString("FPS:%1 --FN:%2").arg(int(1000./(elapsedTime.elapsed()))).arg(frameNumber));
	elapsedTime.restart();
	this->update();
}

void RollerCoasterView::drawGameObject(GameObject& o, GameObject& p){
	if(o.model){
		glUniformMatrix4fv(uMainModelMatrix, 1, GL_FALSE, (o.modelMat()*p.modelMat()).data);

		for(int i=0;i<o.model->materials.size();++i){
			glUniform3fv(uMainKa, 1 , o.model->materials[i].Ka.data);
			glUniform3fv(uMainKd, 1 , o.model->materials[i].Kd.data);
			glUniform3fv(uMainKs, 1 , o.model->materials[i].Ks.data);
			glUniform1f(uMainNs, o.model->materials[i].Ns);
			glUniform1i(uMainUseTexture, o.model->materials[i].texture);
//			glUniform1i(uMainUseTexture, -1);
			if(o.model->materials[i].texture != -1){
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, TextureDB::ID[o.model->materials[i].texture]);
			}

//			glVertexAttribPointer自動偵測陣列大小錯誤(sizeof(float*)=4)
//			不知如何直接指定glVertexAttribPointer大小只好先丟到VBO指定大小
//			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFV[i]);
//			glVertexAttribPointer(vUV, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFT[i]);
//			glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFN[i]);

			glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.model->faces[i].size()*3*3, o.model->mtlFV[i], GL_STATIC_DRAW);
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, Buffers[UVBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.model->faces[i].size()*3*2, o.model->mtlFT[i], GL_STATIC_DRAW);
			glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.model->faces[i].size()*3*3, o.model->mtlFN[i], GL_STATIC_DRAW);
			glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArrays(GL_TRIANGLES, 0, o.model->faces[i].size()*3);
			//glPointSize(2000);
			//glDrawArrays(GL_POINTS, 0, 10);
			//glBindTexture(GL_TEXTURE_2D, 0);

		}
	}
	for(int i=0;i<o.children.size();++i)
		drawGameObject(*o.children[i], p+o);
	o.animation(frameNumber);
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
//		printf("%s\n",vs_source);
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
//		printf("%s\n",fs_source);
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
