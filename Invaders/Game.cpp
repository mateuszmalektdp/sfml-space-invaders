#include "Game.h"

Game::Game()
{
    this->window = nullptr;
    this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Invaders");
    this->window->setFramerateLimit(60);
}
Game::~Game()
{
    for (auto& pair : textureMap)
    {
        pair.second = nullptr;
    }
    textureMap.clear();
    delete this->window;
}
void Game::Options()
{
    Button start(this->window, "START GAME", 0);
    Button score(this->window, "HIGH SCORE", 1);
    Button exit(this->window, "EXIT GAME", 2);
    ScoreboardLoad();
    while (this->window->isOpen())
    {
        this->window->clear(sf::Color(1, 2, 50));
        HandleButtons(start, score, exit);
        DisplayButtons(start, score, exit);
        this->window->display();
    }
}

void Game::HandleButtons(Button& start, Button& score, Button& exit)
{
    sf::Event ev;
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            if (ev.mouseButton.button == sf::Mouse::Left)
            {
                if (start.CheckClick(this->window))
                {
                    this->window->clear(sf::Color(1, 2, 50));
                    GameStart();
                }
                else if (score.CheckClick(this->window))
                {
                    this->window->clear(sf::Color(1, 2, 50));
                    ScoreboardDisplay();
                }
                else if (exit.CheckClick(this->window))
                {
                    this->window->close();
                }
            }
            break;
        default:
            break;
        }
    }
}
void Game::DisplayButtons(Button& start, Button& score, Button& exit)
{

    start.DisplayButton(this->window);
    score.DisplayButton(this->window);
    exit.DisplayButton(this->window);
}
void Game::ScoreboardLoad()
{
    std::filesystem::path scorePath = std::filesystem::current_path() / "scores.txt";
    ifstream file(scorePath);
    int x = 0;
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            string name;
            int value;
            istringstream iss(line);
            if (iss >> name >> value)
            {
                fullboard.push_back(make_unique<Scoreboard>(this->window, name, x, value));
            }
            x++;
        }

        file.close();
    }

}
void Game::ScoreboardDisplay()
{
    while (this->window->isOpen())
    {
        DeveloperExit();
        this->window->clear(sf::Color(1, 2, 50));
        for (auto& obj : fullboard)
        {
            obj->PlayerDisplay(this->window);
        }
        this->window->display();
    }
}
string Game::AddToScoreboard()
{
    sf::Font font;
    if (!font.loadFromFile("Montserrat.ttf"))
    {

    }
    sf::RectangleShape newScore;
    newScore.setSize(sf::Vector2f(800.f, 200.f));
    newScore.setFillColor(sf::Color(213, 113, 20));
    newScore.setPosition(400.f, 350.f);
    newScore.setOutlineThickness(2.f);
    newScore.setOutlineColor(sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setPosition(400.f, 400.f);
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);

    std::string inputString;
    std::regex lettersOnlyRegex("^[a-zA-Z]+$");

    bool enterPressed = false;

    while (this->window->isOpen() && !enterPressed)
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !inputString.empty())
                {
                    inputString.erase(inputString.size() - 1);
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                {
                    if (std::regex_match(inputString, lettersOnlyRegex))
                        enterPressed = true;
                }
                else if (event.text.unicode < 128)
                {
                    inputString += static_cast<char>(event.text.unicode);
                }
            }
        }

        text.setString(inputString);

        window->clear(sf::Color(1, 2, 50));
        window->draw(newScore);
        window->draw(text);
        window->display();
    }

    return inputString;
}

void Game::GameStart()
{
    LoadingTextures();
    objectsCreated.push_back(make_unique<Player>(textureMap["Player_Texture"]));
    CreatingNewLevel();
    GameLoop();
}

void Game::LoadingTextures()
{
    struct textureData
    {
        std::string fileName;
        std::string textureName;
    };

    std::vector<textureData> textures = {
        {"Player.jpg", "Player_Texture"},
        {"Enemy.jpg", "Enemy_Texture"},
        {"Wall.jpg", "Wall_Texture"},
        {"Wall_2.jpg", "Wall2_Texture"},
        {"Wall_3.jpg", "Wall3_Texture"},
        {"Wall_4.jpg", "Wall4_Texture"},
    };

    for (const auto& textureData : textures)
    {
        std::filesystem::path imagePath = std::filesystem::current_path() / "textures" / textureData.fileName;
        sf::Texture* texture = new sf::Texture;
        if (texture->loadFromFile(imagePath.string()))
        {
            textureMap[textureData.textureName] = texture;
        }
    }
}
void Game::CreatingNewLevel()
{
    for (int i = 0; i < 4; i++)
        objectsCreated.push_back(make_unique<Wall>(i, textureMap["Wall_Texture"], textureMap["Wall2_Texture"], textureMap["Wall3_Texture"], textureMap["Wall4_Texture"]));
    for (int j = 0; j < 40; j++)
        objectsCreated.push_back(make_unique<Enemy>(j, textureMap["Enemy_Texture"]));
    this->window->clear(sf::Color(1, 2, 50));
    dynamic_cast<Player*>(objectsCreated[0].get())->IncreaseLevel();

    enemiesLeft = 40;
    endOfGame = false;
    endOfLevel = false;
    for (const auto& object : objectsCreated)
    {
        object->DrawObject(this->window);
    }
    this->window->display();
}
void Game::GameLoop()
{
    int score;
    while (this->window->isOpen() && endOfGame == false)
    {
        if (dynamic_cast<Player*>(objectsCreated[0].get()) != nullptr)
            score = dynamic_cast<Player*>(objectsCreated[0].get())->GetPlayerScore();
        DeveloperExit();
        UpdateGameObjects();
        RenderGameObjects();
        if (endOfLevel == true)
        {
            for (auto it = objectsCreated.begin() + 1; it != objectsCreated.end();)
                it = objectsCreated.erase(it);
            dynamic_cast<Player*>(objectsCreated[0].get())->IncreaseScore(100);
            CreatingNewLevel();
        }
    }
    GameOver(score);
}

void Game::DeveloperExit()
{
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}
void Game::UpdateGameObjects()
{
    for (auto it = objectsCreated.begin(); it != objectsCreated.end();)
    {
        auto& object = *it;
        if (dynamic_cast<DynamicObject*>(object.get()))
        {
            DynamicObject* dynamicObject = dynamic_cast<DynamicObject*>(object.get());
            dynamicObject->UpdateObject(this->window);
            if (dynamic_cast<ShootingObject*>(object.get()))
            {
                ShootingObject* shootingObject = dynamic_cast<ShootingObject*>(object.get());
                bool shot = shootingObject->ShootTheBullet(objectsCreated);
                if (shot == true)
                {
                    objectsCreated.push_back(make_unique<Bullet>(shootingObject->GetPosition(), shootingObject->FriendlyBullet()));
                }
            }
            else
            {
                Bullet* bullet = dynamic_cast<Bullet*>(object.get());
                bullet->CheckCollision(objectsCreated);
            }
        }

        IsAtTheBottom();
        if (object->IsDead() == true)
        {
            if (dynamic_cast<Enemy*>(object.get()))
            {
                dynamic_cast<Player*>(objectsCreated[0].get())->IncreaseScore(10);
                enemiesLeft -= 1;
                if (enemiesLeft == 0)
                {
                    endOfLevel = true;
                }
            }

            if (dynamic_cast<Player*>(object.get()) != nullptr)
                endOfGame = true;
            it = objectsCreated.erase(it);
        }
        else
            it++;
    }

}
void Game::RenderGameObjects()
{
    this->window->clear(sf::Color(1, 2, 50));
    for (const auto& object : objectsCreated)
        object->DrawObject(this->window);

    if (endOfGame == false)
        dynamic_cast<Player*>(objectsCreated[0].get())->DisplayStatistics(this->window);

    this->window->display();
}
void Game::IsAtTheBottom()
{
    bool bottomCheck = false;
    for (const auto& object : objectsCreated)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(object.get());
        if (enemy != nullptr && enemy->GetPosition().y == 540.f)
        {
            bottomCheck = true;
            break;
        }
    }
    for (const auto& object : objectsCreated)
    {
        if (dynamic_cast<Enemy*>(object.get()))
        {
            Enemy* bottom = dynamic_cast<Enemy*>(object.get());
            bottom->BottomSet(bottomCheck);
        }
    }
}
void Game::GameOver(int score)
{
    for (auto it = objectsCreated.begin(); it != objectsCreated.end();)
        it = objectsCreated.erase(it);

    auto minScore = std::ranges::min_element(fullboard, [](const auto& obj1, const auto& obj2)
        {
            return obj1->GetScore() < obj2->GetScore();
        });
    if (minScore != fullboard.end() && score > (*minScore)->GetScore())
    {
        string name = AddToScoreboard();
        (*minScore)->Set(score, name);

    }
    std::ranges::sort(fullboard, [](const auto& obj1, const auto& obj2)
        {
            return obj1->GetScore() > obj2->GetScore();
        });
    ReloadScoreboard();

}
void Game::ReloadScoreboard()
{
    std::filesystem::path scorePath = std::filesystem::current_path() / "scores.txt";
    std::ofstream file(scorePath);
    if (!file.is_open())
    {
        std::cout << "Failed to open file for writing: " << scorePath << std::endl;
        return;
    }

    for (const auto& entry : fullboard)
    {
        file << entry->GetName() << " " << entry->GetScore() << std::endl;
    }

    file.close();
    ScoreboardLoad();
}