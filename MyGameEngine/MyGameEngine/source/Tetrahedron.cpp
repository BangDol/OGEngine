#include "OGEngine.h"
#include "Tetrahedron.h"

void Tetrahedron::Start()
{
	std::cout << "Tetrahedron Render - Start\n";
}

void Tetrahedron::FixedUpdate()
{
	std::cout << "Tetrahedron Render - FixedUpdate\n";
}

void Tetrahedron::Update()
{
	OGENGINE_GET_DRIVER->RenderTetrahedron();
}