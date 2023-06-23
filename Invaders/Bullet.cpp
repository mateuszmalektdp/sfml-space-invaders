#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, bool isPlayer)
{
    currentPosition.x = position.x;
    if (isPlayer == true)
    {
        object.setPosition(position.x - 2, position.y - 5);
        currentPosition.y = position.y - 10;
        friendly = true;
    }
    else
    {
        object.setPosition(position.x - 2, position.y + 5);
        currentPosition.y = position.y + 10;
        friendly = false;
    }
    object.setSize(sf::Vector2f(5.f, 15.f));
    object.setFillColor(sf::Color::Yellow);
}
Bullet::~Bullet()
{

}
void Bullet::UpdateObject(sf::RenderWindow* window)
{
    if (friendly == true)
    {
        object.move(0.f, -7.5f);
        currentPosition.y -= 7.5f;
    }
    else
    {
        object.move(0.f, 7.5f);
        currentPosition.y += 7.5f;
    }
}
void Bullet::DrawObject(sf::RenderWindow* window)
{
    window->draw(object);
}
sf::FloatRect Bullet::GetObjectBounds()
{
    return object.getGlobalBounds();
}
void Bullet::CheckCollision(vector <unique_ptr<GraphicObject>>& objectsCreated)
{
    for (auto it = objectsCreated.begin(); it != objectsCreated.end();)
    {
        auto& object = *it;
        sf::FloatRect bounds = object->GetObjectBounds();
        if (bounds.contains(GetPosition()) && object->GetObjectBounds() != GetObjectBounds())
        {
            dead = true;
            object->ObjectTagged();
        }
        it++;
    }
}
void Bullet::ObjectTagged()
{
    dead = true;
}
sf::Vector2f Bullet::GetPosition()
{
    return currentPosition;
}
bool Bullet::IsDead()
{
    if (currentPosition.y < -10.f || currentPosition.y > 910.f)
        return true;
    else return dead;
}
