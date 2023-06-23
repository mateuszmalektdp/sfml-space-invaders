#pragma once

#ifndef GameClass
#define GameClass

#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Button.h"
#include "Scoreboard.h"
#include <fstream>
#include <ranges>
#include <algorithm>
#include <regex>

using namespace std;

class Game {

private:

    vector <unique_ptr<GraphicObject>> objectsCreated;
    unordered_map<string, sf::Texture*> textureMap;
    sf::RenderWindow* window;
    sf::Event ev;
    int enemiesLeft;
    bool endOfLevel;
    bool endOfGame;
    vector <unique_ptr<Scoreboard>> fullboard;

public:
    Game();
    ~Game();
    void Options();
    void HandleButtons(Button& start, Button& score, Button& exit);
    void DisplayButtons(Button& start, Button& score, Button& exit);

    void GameStart();
    void CreatingNewLevel();
    void LoadingTextures();
    void ScoreboardDisplay();
    void ScoreboardLoad();
    string AddToScoreboard();

    void GameLoop();
    void DeveloperExit();
    void UpdateGameObjects();
    void RenderGameObjects();
    void IsAtTheBottom();
    void GameOver(int score);
    void ReloadScoreboard();

};
#endif