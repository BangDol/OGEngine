#ifndef _OG_ENGINE_DEVICE_H_
#define _OG_ENGINE_DEVICE_H_

#include <vector>

#include "GLM/glm.hpp"

class OGEngineDriver
{
public:
	virtual void Init() = 0;
	virtual bool Run() = 0;
	virtual void CloseDriver() = 0;
	virtual void Loop() = 0;

	virtual void BeginScene() = 0;
	virtual void LoopScene() = 0;

	virtual void Input() = 0;
	virtual void Camera() = 0;

public:
	//Polyhedron
	virtual void RenderTetrahedron() = 0;
	virtual void RenderHexahedron() = 0;

	//Render .obj File
	virtual void RenderOBJ(
		bool _res,
		std::vector<glm::vec3> _vertices,
		std::vector<glm::vec3> _uvs,
		std::vector<glm::vec3> _normals) = 0;

};

#endif