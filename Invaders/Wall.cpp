#include "Wall.h"

Wall::Wall(int pos, sf::Texture* texture, sf::Texture* texture2, sf::Texture* texture3, sf::Texture* texture4)
{
	object.setPosition((350 * pos) + 200.f, 700.f);
	currentPosition.x = (350 * pos) + 200.f;
	currentPosition.y = 700.f;
	state[0] = texture;
	state[1] = texture2;
	state[2] = texture3;
	state[3] = texture4;
	object.setTexture(*state[health - 1]);


}
Wall::~Wall()
{

}
void Wall::DrawObject(sf::RenderWindow* window)
{
	window->draw(object);
}
sf::FloatRect Wall::GetObjectBounds()
{
	return object.getGlobalBounds();
}
void Wall::ObjectTagged()
{
	currentPosition.y += 15.f;
	object.setPosition(object.getPosition().x, object.getPosition().y + 15.f);
	--health;
	if (health > 0)
	{
		object.setTexture(*state[health - 1]);
	}
}
sf::Vector2f Wall::GetPosition()
{
	return currentPosition;
}
bool Wall::IsDead()
{
	if (health == 0)
		return true;
	else return false;
}