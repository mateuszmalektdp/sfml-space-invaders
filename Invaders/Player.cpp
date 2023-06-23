#include "Player.h"

Player::Player(sf::Texture* texture)
{
    object.setPosition(750.f, 820.f);
    currentPosition.x = 800.f;
    currentPosition.y = 820.f;
    object.setTexture(*texture);
}
Player::~Player()
{

}
sf::FloatRect Player::GetObjectBounds()
{
    return object.getGlobalBounds();
}
void Player::DrawObject(sf::RenderWindow* window)
{
    window->draw(object);
}
void Player::UpdateObject(sf::RenderWindow* window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        object.move(-5.f, 0.f);
        currentPosition.x -= 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        object.move(5.f, 0.f);
        currentPosition.x += 5.f;
    }
}
void Player::ObjectTagged()
{
    score -= 25;
    --health;
}
bool Player::ShootTheBullet(vector<unique_ptr<GraphicObject>>& objectsCreated)
{
    static std::future<void> cooldown;

    if (cooldown.valid() && cooldown.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
    {
        return false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        cooldown = std::async(std::launch::async, [] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            });
        return true;
    }
    return false;
}
sf::Vector2f Player::GetPosition()
{
    return currentPosition;
}
bool Player::FriendlyBullet()
{
    return true;
}
bool Player::IsDead()
{
    if (health == 0)
        return true;
    else return false;
}
int Player::GetPlayerScore()
{
    return score;
}
void Player::DisplayStatistics(sf::RenderWindow* window)
{
    sf::Font font;
    if (!font.loadFromFile("Montserrat.ttf"))
    {
        return;
    }

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(25);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(15.f, 15.f);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(15.f, 50.f);

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(25);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(15.f, 85.f);

    livesText.setString("Lives: " + std::to_string(health));
    scoreText.setString("Score: " + std::to_string(score));
    levelText.setString("Level: " + std::to_string(level));

    window->draw(livesText);
    window->draw(scoreText);
    window->draw(levelText);

}
void Player::IncreaseScore(int add)
{
    score += add;
}
void Player::IncreaseLevel()
{
    level++;
}