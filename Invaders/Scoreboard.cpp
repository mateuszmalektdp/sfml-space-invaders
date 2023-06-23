#include "Scoreboard.h"

Scoreboard::Scoreboard(sf::RenderWindow* window, string name, int place, int score)
{
    if (!font.loadFromFile("Montserrat.ttf"))
    {

    }
    username = name;
    userscore = score;
    sf::Vector2f shapePosition(100.f, 50.f), textPosition(200.f, 110.f);
    shapePosition.y += (150.f * place);
    textPosition.y += (150.f * place);

    idShape.setSize(sf::Vector2f(200.f, 120.f));
    idShape.setFillColor(sf::Color(213, 113, 20));
    idShape.setPosition(shapePosition);
    idShape.setOutlineThickness(2.f);
    idShape.setOutlineColor(sf::Color::Black);

    idText.setFont(font);
    idText.setString(to_string(place + 1));
    idText.setCharacterSize(100);
    sf::FloatRect textBounds = idText.getLocalBounds();
    idText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    idText.setPosition(sf::Vector2f(textPosition));
    idText.setFillColor(sf::Color::White);

    shapePosition.x += 250.f;
    textPosition.x += 550.f;

    nameShape.setSize(sf::Vector2f(800.f, 120.f));
    nameShape.setFillColor(sf::Color(213, 113, 20));
    nameShape.setPosition(shapePosition);
    nameShape.setOutlineThickness(2.f);
    nameShape.setOutlineColor(sf::Color::Black);

    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(100);
    textBounds = nameText.getLocalBounds();
    nameText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    nameText.setPosition(sf::Vector2f(textPosition));
    nameText.setFillColor(sf::Color::White);

    shapePosition.x += 850.f;
    textPosition.x += 600.f;

    scoreShape.setSize(sf::Vector2f(300.f, 120.f));
    scoreShape.setFillColor(sf::Color(213, 113, 20));
    scoreShape.setPosition(shapePosition);
    scoreShape.setOutlineThickness(2.f);
    scoreShape.setOutlineColor(sf::Color::Black);

    scoreText.setFont(font);
    scoreText.setString(to_string(score));
    scoreText.setCharacterSize(100);
    textBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    scoreText.setPosition(sf::Vector2f(textPosition));
    scoreText.setFillColor(sf::Color::White);
}

void Scoreboard::PlayerDisplay(sf::RenderWindow* window)
{
    window->draw(idShape);
    window->draw(idText);
    window->draw(nameShape);
    window->draw(nameText);
    window->draw(scoreShape);
    window->draw(scoreText);
}
int Scoreboard::GetScore()
{
    return userscore;
}
string Scoreboard::GetName()
{
    return username;
}
void Scoreboard::Set(int score, string name)
{
    userscore = score;
    username = name;
}
