#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

#include "Component.h"

class GameObject
{
private:
	std::vector <Component*> compList;	//컴포넌트
	std::vector<GameObject*> childList;		//하위 게임오브젝트
	std::string objectName;	//오브젝트 이름

public:
	GameObject(std::string _objectName);
	~GameObject();

	void Init();
	void Run();

	//오브젝트 이름 Set/Get
	void SetName(std::string _name);
	std::string GetName();

	//컴포넌트
		//고려사항
			//해당 게임오브젝트의 컴포넌트 리스트를 매니저에게 넘기고
			//매니저에서 리스트 내 모든 컴포넌트 기능을 실행?
	void AddComponent(Component* _src);
	void RemoveComponent(Component* _src);
	void InitComponents();
	void RunComponents();
	//Component GetComponent();

	//하위 게임오브젝트
		//고려사항
			//위의 컴포넌트와 동일
	void AddChild(GameObject* _go);
	void RemoveChild(GameObject* _go);
	void InitAllChildren();
	void RunAllChildren();
	//void GetAllChildren();
	//void GetChild(GameObject*);

};

#endif