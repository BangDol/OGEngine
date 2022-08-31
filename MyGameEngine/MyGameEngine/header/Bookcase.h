#ifndef _BOOKCASE_H_
#define _BOOKCASE_H_

#include <iostream>
#include <vector>

#include "GLM/glm.hpp"

#include "Component.h"

class Bookcase : public Component
{
private:
	bool res;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> uvs;
	std::vector<glm::vec3> normals;

protected:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
};

#endif