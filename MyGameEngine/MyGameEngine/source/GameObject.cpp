#include "GameObject.h"

GameObject::GameObject(std::string _objectName) : objectName(_objectName)
{

}

GameObject::~GameObject()
{
	//for문 돌려서 내용물 일일이 지워줘야 함
	for (auto& comps : compList)
	{
		delete comps;
	}
	for (auto& comps : childList)
	{
		delete comps;
	}
}

void GameObject::Init()
{
	InitComponents();

	InitAllChildren();
}

void GameObject::Run()
{
	RunComponents();

	RunAllChildren();
}

#pragma region 이름 관리

void GameObject::SetName(std::string _name)
{
	this->objectName = _name;
}

std::string GameObject::GetName()
{
	return this->objectName;
}

#pragma endregion

#pragma region Component 관리

//AddComponent 파리미터 넘길때 반드시 new 컴포넌트()로 생성
void GameObject::AddComponent(Component* _src)
{
	compList.push_back(_src);
	_src->SetGameObjectName(this->GetName());
}

void GameObject::RemoveComponent(Component* _src)
{
	//컴포넌트 삭제 기능
}

void GameObject::InitComponents()
{
	for (auto& comps : compList)
	{
		comps->Init();
	}
}

void GameObject::RunComponents()
{
	for (auto& comps : compList)
	{
		comps->Run();
	}
}

#pragma endregion

#pragma region Child 관리

void GameObject::AddChild(GameObject* _go)
{
	//하위 게임오브젝트 추가
	childList.push_back(_go);
}

void GameObject::RemoveChild(GameObject* _go)
{

}

//현재 게임오브젝트의 하위에 붙어있는 모든 게임오브젝트에 대해서도 동일하게 Init() 처리
void GameObject::InitAllChildren()
{
	for (auto& children : childList)
	{
		children->Init();
	}
}

//현재 게임오브젝트의 하위에 붙어있는 모든 게임오브젝트에 대해서도 동일하게 Run() 처리
void GameObject::RunAllChildren()
{
	for (auto& children : childList)
	{
		children->Run();
	}
}

#pragma endregion