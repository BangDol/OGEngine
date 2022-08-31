#ifndef _SAMPLE_SCENE_H_
#define _SAMPLE_SCENE_H_

#include "Scene.h"

class SampleScene : public Scene
{
public:
	SampleScene(std::string _name) : Scene(_name) {}
	~SampleScene() {}

public:
	void CreateScene();
};

#endif