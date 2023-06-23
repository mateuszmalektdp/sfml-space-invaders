#pragma once
#ifndef BulletClass
#define BulletClass

#include "DynamicObject.h"

class Bullet : public DynamicObject {
    int mode = 0;
    int moving = 400;
    bool friendly;
    bool dead = false;
    bool tagged = false;
    sf::RectangleShape object;
    sf::Vector2f currentPosition;
public:
    Bullet(sf::Vector2f position, bool isPlayer);
    ~Bullet();

    virtual bool IsDead();
    virtual void ObjectTagged();
    virtual sf::Vector2f GetPosition();
    virtual sf::FloatRect GetObjectBounds();
    virtual void UpdateObject(sf::RenderWindow* window);
    virtual void DrawObject(sf::RenderWindow* window);
    void CheckCollision(vector<unique_ptr<GraphicObject>>& objectsCreated);

};



#endif