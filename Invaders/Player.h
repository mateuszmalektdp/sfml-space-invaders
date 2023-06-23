#pragma once
#ifndef PlayerClass
#define PlayerClass

#include "ShootingObject.h"

class Player : public ShootingObject
{
    sf::Sprite object;
    sf::Vector2f currentPosition;
    int health = 3;
    int score = 0;
    int level = 0;

public:
    Player(sf::Texture* texture);
    ~Player();

    virtual bool IsDead();
    virtual void ObjectTagged();
    virtual sf::Vector2f GetPosition();
    virtual sf::FloatRect GetObjectBounds();
    virtual void UpdateObject(sf::RenderWindow* window);
    virtual void DrawObject(sf::RenderWindow* window);
    virtual bool ShootTheBullet(vector<unique_ptr<GraphicObject>>& objectsCreated);
    bool FriendlyBullet();
    void IncreaseScore(int add);
    void DisplayStatistics(sf::RenderWindow* window);
    int GetPlayerScore();
    void IncreaseLevel();
};

#endif