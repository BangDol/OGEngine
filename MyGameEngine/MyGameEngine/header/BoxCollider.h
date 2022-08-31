#ifndef _BOX_COLLIDER_H_
#define _BOX_COLLIDER_H_

#include <iostream>

#include "Component.h"

class BoxCollider : public Component
{
protected:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

};

#endif