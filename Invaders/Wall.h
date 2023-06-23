#pragma once
#ifndef WallClass
#define WallClass

#include "GraphicObject.h"

class Wall : public GraphicObject
{
    sf::Sprite object;
    sf::Vector2f currentPosition;
    sf::Texture* state[4];
    int health = 4;

public:
    Wall(int pos, sf::Texture* texture, sf::Texture* texture2, sf::Texture* texture3, sf::Texture* texture4);
    ~Wall();

    virtual bool IsDead();
    virtual void ObjectTagged();
    virtual sf::Vector2f GetPosition();
    virtual sf::FloatRect GetObjectBounds();
    virtual void DrawObject(sf::RenderWindow* window);
};

#endif