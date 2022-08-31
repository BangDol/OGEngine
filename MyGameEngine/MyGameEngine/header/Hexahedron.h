#ifndef _HEXAHEDRON_H_
#define _HEXAHEDRON_H_

#include "Component.h"

//육면체
class Hexahedron : public Component
{
protected:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

};

#endif