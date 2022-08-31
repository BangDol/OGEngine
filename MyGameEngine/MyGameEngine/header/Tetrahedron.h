#ifndef _TETRAHEDRON_H_
#define _TETRAHEDRON_H_

#include "Component.h"

//사면체
class Tetrahedron : public Component
{
protected:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

};

#endif