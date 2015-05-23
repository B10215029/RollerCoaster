#include "rollercoasterview.h"
#include <QFile>
#include <QString>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <string>
#define DEPTH_TEXTURE_SIZE 4096

RollerCoasterView::RollerCoasterView(QWidget *parent) : QOpenGLWidget(parent){
	TextureDB::init();
	worldCamera = Camera();
	worldLight = Light();
	mainCamera = &worldCamera;
	mainLight = &worldLight;
//	mainCamera = &worldLight;
	a.mesh = &testm;
	//a.scale=vec3(10,10,10);
	//root.scale=vec3(10,10,10);
	b.mesh = NULL;
	b.position=vec3(0,300,50);
	root.mesh = new Mesh(":/models/floor.obj");
//	root.animationType = GameObject::AnimRotateY;
//	root.mesh = new Mesh("C:/Users/Delin/Desktop/car.obj");
//	a.setParent(&root);


	root.setChild(&track);
	track.name = "Track";

	track.addTrain();
	track.setTrainModel(0);
	track.trains[0]->setChild(&a);
	a.position = vec3(0, 1, -1);
	a.rotation = vec3(0, 180, 0);

//	mainCamera = &track.trainCamera;
	//a.setChild(&b);
	//testm.loadOBJ("C:/Users/Delin/Desktop/66899_kirby/kirby/kirby2.obj");
	//testm.loadOBJ("C:/Users/Delin/Desktop/model/Deadpool/DeadPool.obj");
	testm.loadOBJ("C:/Users/Delin/Desktop/67700_renamon_v2_6/Renamon_V2.6.obj");
	//testm.loadOBJ("C:/Users/Delin/Desktop/74796_Jibril_by_jugapugz_zip/jibril_by_jugapugz.obj");

	worldCamera.position = vec3(0, 50, 20);
	worldCamera.rotation = vec3(-45,0,0);
	worldCamera.setFrustum(-10, 10 ,-10, 10, -1000, 1000);

	worldLight.position = vec3(0.0f, 100.0f, 100.0f);
	worldLight.rotation = vec3(-45.0f, 45.0f, 0.0f);
	worldLight.setFrustum(-500, 500, -500, 500, -1000, 1000);

	isLine = false;
	frameNumber = 0;
}

RollerCoasterView::~RollerCoasterView(){

}

void RollerCoasterView::mousePressEvent(QMouseEvent *event){
	mPPX=event->x();
	mPPY=event->y();
	mPCP=worldCamera.position;
	mPCR=worldCamera.rotation;
}

void RollerCoasterView::mouseReleaseEvent(QMouseEvent *event){

}

void RollerCoasterView::mouseMoveEvent(QMouseEvent *event){
	if(event->buttons().testFlag(Qt::MiddleButton)){
		worldCamera.position=mPCP+worldCamera.rotateMat()*vec3((mPPX-event->x())*worldCamera.top/300.0f,-(mPPY-event->y())*worldCamera.top/300.0f,0);
	}
	if(event->buttons().testFlag(Qt::LeftButton)){
		worldCamera.rotation.x()=mPCR.x()+(mPPY-event->y())/5.0f;
		worldCamera.rotation.y()=mPCR.y()+(mPPX-event->x())/5.0f;
	}

}

void RollerCoasterView::mouseDoubleClickEvent(QMouseEvent *event){

}

void RollerCoasterView::wheelEvent(QWheelEvent *event){
	worldCamera.top-=event->delta()*worldCamera.top/1000.;
//	if(worldCamera.top<0.001 || worldCamera.top>1000)
//		worldCamera.top=worldCamera.top<0.001?0.001:1000;
	worldCamera.left=-worldCamera.top*width/height;
	worldCamera.right=worldCamera.top*width/height;
	worldCamera.bottom=-worldCamera.top;

}

void RollerCoasterView::keyPressEvent(QKeyEvent *event){
	switch(event->key()){
	case Qt::Key_1:
		worldCamera.rotation=vec3(0,0,0);
		break;
	case Qt::Key_2:
		worldCamera.rotation.x()+=5.0f;
		break;
	case Qt::Key_3:
		worldCamera.rotation=vec3(0,90,0);
		break;
	case Qt::Key_4:
		worldCamera.rotation.y()-=5.0f;
		break;
	case Qt::Key_5:
		worldCamera.isPerspective=!worldCamera.isPerspective;
		break;
	case Qt::Key_6:
		worldCamera.rotation.y()+=5.0f;
		break;
	case Qt::Key_7:
		worldCamera.rotation=vec3(-90,0,0);
		break;
	case Qt::Key_8:
		worldCamera.rotation.x()-=5.0f;
		break;
	case Qt::Key_9:
		worldCamera.rotation.z()+=5.0f;
		break;
	default:
		if(event->key()==Qt::Key_Q)
			worldLight.rotation.x()++;
		if(event->key()==Qt::Key_A)
			worldLight.rotation.x()--;
		if(event->key()==Qt::Key_W)
			worldLight.rotation.y()++;
		if(event->key()==Qt::Key_S)
			worldLight.rotation.y()--;
		if(event->key()==Qt::Key_E)
			worldLight.rotation.z()++;
		if(event->key()==Qt::Key_D)
			worldLight.rotation.z()--;
	}
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
	glBindVertexArray(VAOs[modelVAO]);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vUV);
	glEnableVertexAttribArray(vNormal);
	glBindVertexArray(0);
	glGenBuffers(NumBuffers, Buffers);

	initProgram(progMain);
	initProgram(progShadow);

	for(int i=0;i<TextureDB::ID.size();++i){
		glGenTextures(1, &TextureDB::ID[i]);
		glBindTexture(GL_TEXTURE_2D, TextureDB::ID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureDB::image[i].width(), TextureDB::image[i].height(), 0, GL_RGB, GL_UNSIGNED_BYTE, TextureDB::image[i].bits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RollerCoasterView::resizeGL(int w, int h){
	width = w;
	height = h;
	glViewport(0,0,w,h);
	worldCamera.aspect = (float)width/height;
	worldCamera.left=-worldCamera.top*width/height;
	worldCamera.right=worldCamera.top*width/height;
}

void RollerCoasterView::paintGL(){
	if(isLine)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	mainCamera->position=track.trains[0]->position;
//	mainCamera->rotation=track.trains[0]->rotation;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAOs[modelVAO]);
	drawProgram(progMain);
//	drawProgram(progShadow);
	glBindVertexArray(0);


	frameNumber++;
	emit getLastFPS(QString("FPS:%1 --FN:%2").arg(int(1000./(elapsedTime.elapsed()))).arg(frameNumber));
	elapsedTime.restart();
	this->update();
}

void RollerCoasterView::initProgram(int program){
	switch(program){
	case progMain:
		mainProgram = loadShaders(":/shaders/main.vert",":/shaders/main.frag");
		glUseProgram(mainProgram);
		uMainModelMatrix		 = glGetUniformLocation(mainProgram, "modelMatrix");
		uMainViewMatrix			 = glGetUniformLocation(mainProgram, "viewMatrix");
		uMainProjectionMatrix	 = glGetUniformLocation(mainProgram, "projectionMatrix");
		uMainLightDirection		 = glGetUniformLocation(mainProgram, "lightDirection");
		uMainEyePosition		 = glGetUniformLocation(mainProgram, "eyePosition");
		uMainMtl.Ka				 = glGetUniformLocation(mainProgram, "Ka");
		uMainMtl.Kd				 = glGetUniformLocation(mainProgram, "Kd");
		uMainMtl.Ks				 = glGetUniformLocation(mainProgram, "Ks");
		uMainMtl.Ns				 = glGetUniformLocation(mainProgram, "Ns");
		uMainMtl.UseTexture		 = glGetUniformLocation(mainProgram, "useTexture");

		break;
	case progShadow:
		ShadowMainProgram = loadShaders(":/shaders/shadowMain.vert",":/shaders/shadowMain.frag");
		glUseProgram(ShadowMainProgram);
		uShadowMainModelMatrix		 = glGetUniformLocation(ShadowMainProgram, "modelMatrix");
		uShadowMainViewMatrix		 = glGetUniformLocation(ShadowMainProgram, "viewMatrix");
		uShadowMainProjectionMatrix	 = glGetUniformLocation(ShadowMainProgram, "projectionMatrix");
		uShadowMainLightDirection	 = glGetUniformLocation(ShadowMainProgram, "lightDirection");
		uShadowMainEyePosition		 = glGetUniformLocation(ShadowMainProgram, "eyePosition");
		uShadowMainMtl.Ka			 = glGetUniformLocation(ShadowMainProgram, "Ka");
		uShadowMainMtl.Kd			 = glGetUniformLocation(ShadowMainProgram, "Kd");
		uShadowMainMtl.Ks			 = glGetUniformLocation(ShadowMainProgram, "Ks");
		uShadowMainMtl.Ns			 = glGetUniformLocation(ShadowMainProgram, "Ns");
		uShadowMainMtl.UseTexture	 = glGetUniformLocation(ShadowMainProgram, "useTexture");
		uShadowMainShadowMatrix		 = glGetUniformLocation(ShadowMainProgram, "shadowMatrix");

		shadowMapProgram = loadShaders(":/shaders/shadowMap.vert",":/shaders/shadowMap.frag");
		glUseProgram(shadowMapProgram);
		uShadowMapMMatrix	 = glGetUniformLocation(shadowMapProgram, "MMatrix");
		uShadowMapVPMatrix	 = glGetUniformLocation(shadowMapProgram, "VPMatrix");

		// Create a depth texture
		glGenTextures(1, &shadowMapTexture);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		// Allocate storage for the texture data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//		glTexStorage2D(GL_TEXTURE_2D, 11, GL_DEPTH_COMPONENT32F, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
		// Set the default filtering modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Set up depth comparison mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		// Set up wrapping modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Create FBO to render depth into
		glGenFramebuffers(1, &shadowMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
		// Attach the depth texture to it
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, shadowMapTexture, 0);
		// Disable color rendering as there are no color attachments
//		glDrawBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		break;
	}
}

void RollerCoasterView::drawProgram(int program){
	switch(program){
	case progMain:
		glUseProgram(mainProgram);
		glUniformMatrix4fv(uMainViewMatrix, 1, GL_FALSE, mainCamera->view().data);
		glUniformMatrix4fv(uMainProjectionMatrix, 1, GL_FALSE, mainCamera->projectionMat().data);
		glUniform3fv(uMainLightDirection, 1 , mainLight->direction().data);
		glUniform3fv(uMainEyePosition, 1 , mainCamera->position.data);
		drawGameObject(root, uMainModelMatrix, &uMainMtl);
		break;
	case progShadow:
		// Time varying light position
//		vec3 light_position = mainLight->position;
		// Matrices for rendering the scene
//		mat4 scene_model_matrix = a.modelMat();
		// Matrices used when rendering from the light’s position
//		mat4 light_view_matrix = mainLight->lookAt(vec3(0,0,0), vec3(0,1,0));
		mat4 light_view_matrix = mainLight->view();
		mat4 light_projection_matrix = mainLight->projectionMat();
//		mat4 scale_bias_matrix = mat4(
//		0.5f, 0.0f, 0.0f, 0.0f,
//		0.0f, 0.5f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.5f, 0.0f,
//		0.5f, 0.5f, 0.5f, 1.0f);
		mat4 scale_bias_matrix = mat4(
		0.5f, 0.0f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
		mat4 shadow_matrix = scale_bias_matrix * light_projection_matrix * light_view_matrix;
///		mat4 shadow_matrix = scale_bias_matrix * light_view_matrix * light_projection_matrix;
///		mat4 shadow_matrix = light_view_matrix * light_projection_matrix * scale_bias_matrix;
///		mat4 shadow_matrix = light_view_matrix * scale_bias_matrix * light_projection_matrix;
//		mat4 shadow_matrix = light_projection_matrix * scale_bias_matrix * light_view_matrix;
//		mat4 shadow_matrix = light_projection_matrix * light_view_matrix * scale_bias_matrix;

		// Now we render from the light’s position into the depth buffer.
		// Select the appropriate program
		glUseProgram(shadowMapProgram);
//		glUniformMatrix4fv(uShadowMapVPMatrix,1, GL_FALSE, (light_projection_matrix * light_view_matrix).data);
		glUniformMatrix4fv(uShadowMapVPMatrix,1, GL_FALSE, (light_view_matrix * light_projection_matrix).data);
		// Bind the "depth only" FBO and set the viewport to the size of the depth texture
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
//		glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
		glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
		// Clear
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		// Enable polygon offset to resolve depth-fighting isuses
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(2.0f, 4.0f);
		// Draw from the light’s point of view
		drawGameObject(root, uShadowMapMMatrix);
		glDisable(GL_POLYGON_OFFSET_FILL);
		glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0,0,width,height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShadowMainProgram);
		glUniformMatrix4fv(uShadowMainViewMatrix, 1, GL_FALSE, mainCamera->view().data);
		glUniformMatrix4fv(uShadowMainProjectionMatrix, 1, GL_FALSE, mainCamera->projectionMat().data);
		glUniform3fv(uShadowMainLightDirection, 1 , mainLight->direction().data);
		glUniform3fv(uShadowMainEyePosition, 1 , mainCamera->position.data);
		glUniformMatrix4fv(uShadowMainShadowMatrix, 1, GL_FALSE, shadow_matrix.data);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
		drawGameObject(root, uShadowMainModelMatrix, &uShadowMainMtl);
		break;
	}
}

void RollerCoasterView::drawGameObject(GameObject &o, GLuint uMM, uniformMtl* uMtl, Transform p){
	if(o.mesh){
		glUniformMatrix4fv(uMM, 1, GL_FALSE, (o.modelMat()*p.modelMat()).data);
		for(int i=0;i<o.mesh->materials.size();++i){
//			glVertexAttribPointer自動偵測陣列大小錯誤(sizeof(float*)=4)
//			不知如何直接指定glVertexAttribPointer大小只好先丟到VBO指定大小
//			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFV[i]);
//			glVertexAttribPointer(vUV, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFT[i]);
//			glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, o.model->mtlFN[i]);

			glBindBuffer(GL_ARRAY_BUFFER, Buffers[PositionBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.mesh->faces[i].size()*3*3, o.mesh->mtlFV[i], GL_STATIC_DRAW);
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			if(uMtl){
				glBindBuffer(GL_ARRAY_BUFFER, Buffers[UVBuffer]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.mesh->faces[i].size()*3*2, o.mesh->mtlFT[i], GL_STATIC_DRAW);
				glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glBindBuffer(GL_ARRAY_BUFFER, Buffers[NormalBuffer]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*o.mesh->faces[i].size()*3*3, o.mesh->mtlFN[i], GL_STATIC_DRAW);
				glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glUniform3fv(uMtl->Ka, 1 , o.mesh->materials[i].Ka.data);
				glUniform3fv(uMtl->Kd, 1 , o.mesh->materials[i].Kd.data);
				glUniform3fv(uMtl->Ks, 1 , o.mesh->materials[i].Ks.data);
				glUniform1f(uMtl->Ns, o.mesh->materials[i].Ns);
				glUniform1i(uMtl->UseTexture, o.mesh->materials[i].texture);
				if(o.mesh->materials[i].texture != -1){
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, TextureDB::ID[o.mesh->materials[i].texture]);
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, o.mesh->faces[i].size()*3);
		}
	}
	for(int i=0;i<o.children.size();++i)
		drawGameObject(*o.children[i], uMM, uMtl, p+o);
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
//#ifdef _DEBUG
////		printf("%s\n",vs_source);
//#endif /* DEBUG */
	}
	else{
//#ifdef _DEBUG
//		printf("Impossible to open %s. Are you in the right directory ?"
//			   "Don't forget to read the FAQ !\n", vertexFilePath);
//#endif /* DEBUG */
		return 0;
	}

	// Read the Fragment Shader code from the file
	QFile FragmentShaderFile(fragmentFilePath);
	if(FragmentShaderFile.open(QIODevice::ReadOnly)){
		FragmentShaderCode=QString(FragmentShaderFile.readAll()).toStdString();
		FragmentShaderFile.close();
		fs_source = FragmentShaderCode.c_str();
//#ifdef _DEBUG
////		printf("%s\n",fs_source);
//#endif /* DEBUG */
	}
	else{
//#ifdef _DEBUG
//		printf("Impossible to open %s. Are you in the right directory ?"
//			"Don't forget to read the FAQ !\n", fragmentFilePath);
//#endif /* DEBUG */
		return 0;
	}

	//compile vertex shader
//#ifdef _DEBUG
//	printf("Compiling shader : %s\n", vertexFilePath);
//#endif /* DEBUG */
	glShaderSource(vs,1,&vs_source,NULL);
	glCompileShader(vs);
	// Compile Fragment Shader
//#ifdef _DEBUG
//	printf("Compiling shader : %s\n", fragmentFilePath);
//#endif /* DEBUG */
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
//#ifdef _DEBUG
//	printf("Linking program\n");
//#endif /* DEBUG */
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

//#ifdef _DEBUG
//	// Check the program
//	glGetProgramiv(program, GL_LINK_STATUS, &Result);
//	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if ( InfoLogLength > 0 ){
//		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
//		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//		printf("%s\n", &ProgramErrorMessage[0]);
//	}
//#endif /* DEBUG */

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
