#include "Button.h"

Button::Button(sf::RenderWindow* window, string text, int option)
{
    if (!font.loadFromFile("Montserrat.ttf"))
    {

    }
    sf::Vector2f buttonPosition(300.f, 50.f), textPosition(800.f, 150.f);
    buttonPosition.y += (300.f * option);
    textPosition.y += (300.f * option);
    buttonShape.setSize(sf::Vector2f(1000.f, 200.f));
    buttonShape.setFillColor(sf::Color(33, 92, 10));
    buttonShape.setPosition(buttonPosition);
    buttonShape.setOutlineThickness(2.f);
    buttonShape.setOutlineColor(sf::Color::Black);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(100);
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    buttonText.setPosition(sf::Vector2f(textPosition));
    buttonText.setFillColor(sf::Color::White);

}

void Button::DisplayButton(sf::RenderWindow* window)
{
    window->draw(buttonShape);
    window->draw(buttonText);

}
bool Button::CheckClick(sf::RenderWindow* window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::FloatRect buttonBounds = buttonShape.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}