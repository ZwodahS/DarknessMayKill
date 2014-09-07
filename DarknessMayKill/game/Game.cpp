#include "Game.hpp"
#include "ui/RootObject.hpp"
Game::Game()
    : renderWindow(nullptr), tw_factory(nullptr), framerate(30)
{
}

Game::~Game()
{
    if (renderWindow)
    {
        delete renderWindow;
    }
    if (tw_factory)
    {
        delete tw_factory;
    }
    if (displayManager)
    {
        delete displayManager;
    }
}

void Game::init()
{
    initUI();
    initAssets();
    initKeys();
}

void Game::initUI()
{
    coreTermSize = sf::Vector2i(51, 51);
    coreCellSize = sf::Vector2i(8, 8);
    screenMultiplier = 2;
    screenSize = sf::Vector2i(screenMultiplier * coreTermSize.x * coreCellSize.x, screenMultiplier * coreTermSize.y * coreCellSize.y);

    renderWindow = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), Title);
    renderWindow->setFramerateLimit(framerate);

    tw_factory = new zf::TiledWindowFactory();
    tw_factory->init(32);

    displayManager = new DisplayManager(*this, *tw_factory);
}

void Game::initAssets()
{
    auto errors = tw_factory->autoload(ResourcePath + "data/font_32");
    for (auto error : errors)
    {
        logger.log(error);
    }
}

void Game::initKeys()
{
    keyMap.addMapping(KeyMap::Key_Left, Action::G_Left);
    keyMap.addMapping(KeyMap::Key_Right, Action::G_Right);
    keyMap.addMapping(KeyMap::Key_Up, Action::G_Up);
    keyMap.addMapping(KeyMap::Key_Down, Action::G_Down);
}

void Game::run()
{
    bool quit(false);
    sf::Clock clock;
    auto object = displayManager->makeDisplayObject(RootObject::Type, nullptr);
    if (!object)
    {
        logger.error("Fail to initialize");
        return;
    }
    displayManager->putDisplay(*object);

    while (!quit && renderWindow->isOpen())
    {
        sf::Time delta = clock.restart();
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow->close();
                quit = true;
            }
            else if(event.type == sf::Event::TextEntered)
            {
                // strictly only handles ascii character
                if (event.text.unicode >= 32 && event.text.unicode <= 126)
                {
                    inputs.push_back(event.text.unicode);
                }
                else if (event.text.unicode == 10)
                {
                    inputs.push_back(event.text.unicode);
                }
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                // handles escape key
                if (event.key.code == sf::Keyboard::Escape)
                {
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    inputs.push_back(KeyMap::Key_Left);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    inputs.push_back(KeyMap::Key_Right);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    inputs.push_back(KeyMap::Key_Up);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    inputs.push_back(KeyMap::Key_Down);
                }
            }
        }
        update(delta);
        draw(delta);
    }
}

const sf::Vector2i& Game::getScreenSize() const
{
    return screenSize;
}

const sf::Vector2i& Game::getCoreTermSize() const
{
    return coreTermSize;
}

const sf::Vector2i& Game::getCoreCellSize() const
{
    return coreCellSize;
}

int Game::getScreenSizeMultiplier() const
{
    return screenMultiplier;
}

void Game::update(const sf::Time& delta)
{
    for (auto key : inputs)
    {
        displayManager->processKey(key);
    }
    displayManager->updateAll(delta);
    inputs.clear();
}

void Game::draw(const sf::Time& delta)
{
    renderWindow->clear(sf::Color(20, 20, 20));
    displayManager->drawAll(*renderWindow, delta);
    renderWindow->display();
}

Logger& Game::getLogger()
{
    return logger;
}
