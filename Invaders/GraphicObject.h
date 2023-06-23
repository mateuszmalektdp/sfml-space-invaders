#pragma once

#ifndef GraphicObjectClass
#define GraphicObjectClass

#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <future>
#include <chrono>
#include <unordered_map>

using namespace std;

class GraphicObject
{
public:

	virtual bool IsDead() = 0;
	virtual void ObjectTagged() = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual sf::FloatRect GetObjectBounds() = 0;
	virtual void DrawObject(sf::RenderWindow* window) = 0;
};

#endif