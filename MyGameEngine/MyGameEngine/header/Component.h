#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <Windows.h>
#include <iostream>

#include "GLFW/glfw3.h"

#define FPS 60.0

class Component
{
private:
	const double fpsLimit = 1.0 / FPS;
	double lastFrameTime = 0;
	double nowFrameTime = 0;

private:
	friend class GameObject;

	//현재 이 컴포넌트가 첨부된 오브젝트의 이름
	//추후에 클래스 자체를 받을 수 있도록
	std::string gameObjectName;	

public:
	Component();
	~Component();

private:
	void Init();
	void Run();

	void SetGameObjectName(std::string _name);
	std::string GetGameObjectName();

protected:
	virtual void Start() {}
	virtual void FixedUpdate() {}
	virtual void Update() {}

};

#endif