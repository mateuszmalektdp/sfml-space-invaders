#pragma once
#ifndef ShootingObjectClass
#define ShootingObjectClass

#include "DynamicObject.h"

class ShootingObject : public DynamicObject
{
public:
	virtual bool ShootTheBullet(vector<unique_ptr<GraphicObject>>& objectsCreated) = 0;
	virtual bool FriendlyBullet() = 0;
};

#endif