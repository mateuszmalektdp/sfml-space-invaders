#pragma once
#ifndef ScoreboardClass
#define ScoreboardClass

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Scoreboard
{
    sf::RenderWindow* window;
    sf::RectangleShape idShape, nameShape, scoreShape;
    sf::Text idText, nameText, scoreText;
    sf::Font font;
    string username;
    int userscore;
public:
    Scoreboard(sf::RenderWindow* window, string name, int place, int score);
    void PlayerDisplay(sf::RenderWindow* window);
    int GetScore();
    string GetName();
    void Set(int score, string name);
};

#endif