#pragma once
#ifndef DynamicObjectClass
#define DynamicObjectClass
#include "GraphicObject.h"

class DynamicObject : public GraphicObject
{
public:
	virtual void UpdateObject(sf::RenderWindow* window) = 0;
};

#endif