#include "OGEngine.h"
#include "Hexahedron.h"

void Hexahedron::Start()
{
	std::cout << "Hexahedren Render - Start\n";
}

void Hexahedron::FixedUpdate()
{
	std::cout << "Hexahedren Render - FixedUpdate\n";
}

void Hexahedron::Update()
{
	OGENGINE_GET_DRIVER->RenderHexahedron();
}