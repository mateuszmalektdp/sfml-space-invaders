#include "Enemy.h"

Enemy::Enemy(int pos, sf::Texture* texture)
{
	int x = pos % 10;
	int y = pos / 10;
	object.setPosition((120 * x) + 230.f, (80 * y) + 100.f);
	currentPosition.x = (120 * x) + 260.f;
	currentPosition.y = (80 * y) + 130.f;
	object.setTexture(*texture);
}
Enemy::~Enemy()
{

}
void Enemy::DrawObject(sf::RenderWindow* window)
{
	window->draw(object);
}
bool Enemy::IsAtTheBottom()
{
	if (currentPosition.y == 540.f)
		return true;
	else return false;
}
void Enemy::BottomSet(bool setter)
{
	atTheBottom = setter;
}
void Enemy::UpdateObject(sf::RenderWindow* window)
{

	if (mode == 0) {
		object.move(0.25f, 0.f);
		currentPosition.x += 0.25f;
		moving++;
		if (moving == 800)
		{
			mode = 1;
			moving = 0;
		}
	}
	if (mode == 1)
	{

		if (atTheBottom == true)
		{
			moving = 200;
		}
		else
		{
			object.move(0.f, 0.25f);
			currentPosition.y += 0.25f;
			moving++;

		}
		if (moving == 200)
		{
			if (sidewaysTrajectory == true)
			{
				mode = 2;
				sidewaysTrajectory = false;
			}
			else
			{
				mode = 0;
				sidewaysTrajectory = true;
			}
			moving = 0;
		}
	}
	if (mode == 2)
	{
		object.move(-0.25f, 0.f);
		currentPosition.x -= 0.25f;
		moving++;
		if (moving == 800)
		{
			mode = 1;
			moving = 0;
		}
	}
}
void Enemy::ObjectTagged()
{
	dead = true;
}
sf::FloatRect Enemy::GetObjectBounds()
{
	return object.getGlobalBounds();
}

bool Enemy::ShootTheBullet(vector<unique_ptr<GraphicObject>>& objectsCreated)
{
	static std::future<void> cooldown;
	sf::FloatRect playerBounds = objectsCreated[0]->GetObjectBounds();

	if (cooldown.valid() && cooldown.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
	{
		return false;
	}
	for (const auto& object : objectsCreated)
	{
		if (object.get() != this && dynamic_cast<Enemy*>(object.get()))
		{
			sf::FloatRect enemyBounds = GetObjectBounds();
			sf::FloatRect otherEnemyBounds = object->GetObjectBounds();

			if (enemyBounds.left <= otherEnemyBounds.left + otherEnemyBounds.width &&
				enemyBounds.left + enemyBounds.width >= otherEnemyBounds.left &&
				enemyBounds.top < otherEnemyBounds.top)
			{
				return false;
			}
		}
	}

	sf::FloatRect enemyBounds = GetObjectBounds();
	if (playerBounds.left <= enemyBounds.left + enemyBounds.width &&
		playerBounds.left + playerBounds.width >= enemyBounds.left)
	{
		cooldown = std::async(std::launch::async, [] {
			std::this_thread::sleep_for(std::chrono::seconds(3));
			});
		return true;
	}
	return false;
}
bool Enemy::FriendlyBullet()
{
	return false;
}
sf::Vector2f Enemy::GetPosition()
{
	return currentPosition;
}
bool Enemy::IsDead()
{
	return dead;
}
