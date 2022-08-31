#include "Component.h"

Component::Component()
{
	//필요한 초기화 수행
	gameObjectName = "null";
}

Component::~Component()
{

}

void Component::SetGameObjectName(std::string _name)
{
	this->gameObjectName = _name;
}

std::string Component::GetGameObjectName()
{
	return this->gameObjectName;
}

void Component::Init()
{
	this->Start();
}

void Component::Run()
{
	nowFrameTime = glfwGetTime();
	double deltaTime = nowFrameTime - lastFrameTime;

	if ((deltaTime) >= fpsLimit)
	{
		this->FixedUpdate();

		lastFrameTime = nowFrameTime;
	}

	this->Update();
}