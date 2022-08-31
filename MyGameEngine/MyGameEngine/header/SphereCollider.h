#ifndef _SPHERE_COLLIDER_H_
#define _SPHERE_COLLIDER_H_

#include <iostream>

#include "Component.h"

class SphereCollider : public Component
{
protected:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

};

#endif