#ifndef  _OG_ENGINE_H_
#define _OG_ENGINE_H_

#include "EDriverType.h"
#include "OGEngineDriver.h"

#include "Scene.h"

#define OGENGINE_GET_DRIVER \
	OGEngine::Instance()->GetDriver() \

class OGEngine
{
private:
	OGEngineDriver* driver;
	E_DRIVER_TYPE driverType;

public:
	OGEngine();
	~OGEngine();

private:
	static OGEngine* instance;

public:
	static OGEngine* Instance();
	static void DestoryInst();

public:
	OGEngineDriver* CreateDriver(E_DRIVER_TYPE _driverType, int _width, int _height, const char* _title, Scene* _scene);
	OGEngineDriver* GetDriver();
	E_DRIVER_TYPE GetDriverType();

private:
	void DeleteDriver();

};

#endif