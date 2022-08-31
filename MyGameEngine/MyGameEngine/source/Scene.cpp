#include "Scene.h"

Scene::Scene(std::string name)
{
	this->sceneName = name;
}

Scene::~Scene()
{
	for (auto& object : objectList)
	{
		delete object;
	}
}

//모든 GameObject의 Init()
//각 Driver 내의 BeginScene() 함수에서 호출
void Scene::InitScene()
{
	std::cout << this->GetSceneName() << " 시작" << std::endl;

	for (auto& objects : objectList)
	{
		objects->Init();
	}
}

//모든 GameObject의 루프 처리
//각 Driver 내의 LoopScene() 함수에서 호출
void Scene::LoopScene()
{
	for (auto& objects : objectList)
	{
		objects->Run();
	}
}

void Scene::SetSceneName(std::string _name)
{
	this->sceneName = _name;
}

std::string Scene::GetSceneName()
{
	return this->sceneName;
}

void Scene::AddGameObject(GameObject* _src)
{
	objectList.push_back(_src);
}

void Scene::RemoveGameObject(GameObject* _src)
{
	//오브젝트 삭제 기능
}