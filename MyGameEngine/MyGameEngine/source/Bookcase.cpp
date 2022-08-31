#include "Bookcase.h"
#include "OGEngine.h"
#include "ResourceManager.h"

void Bookcase::Start()
{
	std::cout << "Bookcase Render - Start\n";

	res = ResourceManager::Instance()->OBJParser("obj/Bookcase.obj", vertices, uvs, normals);
}

void Bookcase::FixedUpdate()
{
	std::cout << "Bookcase Render - FixedUpdate\n";
}

void Bookcase::Update()
{
	OGENGINE_GET_DRIVER->RenderOBJ(res, vertices, uvs, normals);
}