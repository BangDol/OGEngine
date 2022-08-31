#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>
#include <vector>

#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objectList;

	std::string sceneName;

public:
	Scene(std::string _name);
	~Scene();

	void InitScene();
	void LoopScene();

	void SetSceneName(std::string _name);
	std::string GetSceneName();

	void AddGameObject(GameObject* _src);
	void RemoveGameObject(GameObject* _src);
};

#endif