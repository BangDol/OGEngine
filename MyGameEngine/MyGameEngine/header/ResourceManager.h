#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "GLM/glm.hpp"
#include "glaux.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")

class ResourceManager
{
public:
	ResourceManager() {}
	~ResourceManager() {}

private:
	static ResourceManager* instance;

public:
	static ResourceManager* Instance();
	static void DestoryInst();

public:
	bool OBJParser(
		const char* _path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec3>& out_uvs,
		std::vector<glm::vec3>& out_normals);

	AUX_RGBImageRec* LoadBMP(const char* szFilename);
	int LoadGLTextures(const char* szFilePath, unsigned int MyTextureObject[]);

};

#endif