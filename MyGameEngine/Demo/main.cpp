//EngineCore
#include "OGEngine.h"

//그리고자 하는 씬 헤더파일은 여기
#include "SampleScene.h"

int main()
{
	SampleScene* scene1 = new SampleScene("SampleScene");
	scene1->CreateScene();

	OGEngineDriver* driver =
		OGEngine::Instance()->CreateDriver(
			E_DRIVER_TYPE::EDT_OPENGL,
			1600,
			900,
			"Demo",
			scene1);

	driver->Init();

	while (driver->Run())
	{
		driver->Loop();
	}
	driver->CloseDriver();

	OGEngine::DestoryInst();

	return 0;
}