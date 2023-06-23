#pragma once
#ifndef ButtonClass
#define ButtonClass

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Button
{
    sf::RenderWindow* window;
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
public:
    Button(sf::RenderWindow* window, string text, int option);
    void DisplayButton(sf::RenderWindow* window);
    bool CheckClick(sf::RenderWindow* window);
};

#endif