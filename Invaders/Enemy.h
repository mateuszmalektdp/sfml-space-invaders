#pragma once
#ifndef EnemyClass
#define EnemyClass

#include "ShootingObject.h"
#include "Bullet.h"

class Enemy : public ShootingObject
{
	int mode = 0;
	int moving = 400;
	bool sidewaysTrajectory = true;
	bool dead = false;
	bool atTheBottom = false;
	sf::Sprite object;
	sf::Vector2f currentPosition;
public:
	Enemy(int pos, sf::Texture* texture);
	~Enemy();

	void BottomSet(bool setter);
	bool IsAtTheBottom();
	virtual bool IsDead();

	virtual void ObjectTagged();
	virtual sf::Vector2f GetPosition();
	virtual sf::FloatRect GetObjectBounds();

	virtual void DrawObject(sf::RenderWindow* window);
	virtual void UpdateObject(sf::RenderWindow* window);
	virtual bool ShootTheBullet(vector<unique_ptr<GraphicObject>>& objectsCreated);
	virtual bool FriendlyBullet();
};

#endif