#ifndef _OPEN_GL_DEVICE_H_
#define _OPEN_GL_DEVICE_H_

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GL/GLU.h"
#include "GLM/glm.hpp"
#include "glut.h"

#include "OGEngineDriver.h"

#include "Scene.h"

class OpenGLDriver : public OGEngineDriver
{
private:
	//window 생성 시 필요
	GLFWwindow* window;
	int width, height;
	const char* title;
	Scene* sceneToDraw;

private:
	float camX = 0.0, camY = 0.0, camZ = 0.0;
	float pitch = 0.0, yaw = 0.0;

public:
	OpenGLDriver(int _width, int _height, const char* _title, Scene* _scene);
	~OpenGLDriver();

public:
	virtual void Init() override;
	virtual bool Run() override;
	virtual void CloseDriver() override;
	virtual void Loop() override;

	virtual void BeginScene() override;
	virtual void LoopScene() override;

	virtual void Input() override;
	virtual void Camera() override;

public:
	//Polyhedren
	virtual void RenderTetrahedron() override;
	virtual void RenderHexahedron() override;

	//Render .obj File
	virtual void RenderOBJ(
		bool _res,
		std::vector<glm::vec3> _vertices,
		std::vector<glm::vec3> _uvs,
		std::vector<glm::vec3> _normals) override;

};

#endif