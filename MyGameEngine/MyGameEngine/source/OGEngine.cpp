#include "OpenGLDriver.h"
#include "OGEngine.h"

OGEngine* OGEngine::instance = nullptr;

OGEngine::OGEngine()
{

}

OGEngine::~OGEngine()
{

}

OGEngine* OGEngine::Instance()
{
	if (!instance)
	{
		instance = new OGEngine;
	}
	return instance;
}

void OGEngine::DestoryInst()
{
	if (!instance)
	{
		return;
	}
	delete instance;
	instance = nullptr;
}

OGEngineDriver* OGEngine::CreateDriver(E_DRIVER_TYPE _driverType, int _width, int _height, const char* _title, Scene* _scene)
{
	switch (_driverType)
	{
	case E_DRIVER_TYPE::EDT_NULL:
		return NULL;

	case E_DRIVER_TYPE::EDT_OPENGL:
		driver = new OpenGLDriver(_width, _height, _title, _scene);
		OpenGLDriver* driver_gl;
		driver_gl = dynamic_cast<OpenGLDriver*>(driver);
		driverType = _driverType;

		return driver;
	}
}

OGEngineDriver* OGEngine::GetDriver()
{
	return driver;
}

E_DRIVER_TYPE OGEngine::GetDriverType()
{
	return driverType;
}

void OGEngine::DeleteDriver()
{
	delete driver;
}