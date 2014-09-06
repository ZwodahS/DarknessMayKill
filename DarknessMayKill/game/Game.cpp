#include "Game.hpp"

Game::Game()
    : renderWindow(nullptr), tw_factory(nullptr)
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
}

void Game::init()
{
    initUI();
    initAssets();
}

void Game::initUI()
{
    termSize = sf::Vector2i(51, 51);
    cellSize = sf::Vector2i(16, 16);
    screenSize = sf::Vector2i(termSize.x * cellSize.x, termSize.y * cellSize.y);

    renderWindow = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), Title);
    renderWindow->setFramerateLimit(framerate);

    tw_factory = new zf::TiledWindowFactory();
    tw_factory->init(32);
}

void Game::initAssets()
{
    auto errors = tw_factory->autoload(ResourcePath + "data/font_32");
    for (auto error : errors)
    {
        logger.log(error);
    }
}

void Game::run()
{
    bool quit(false);
    sf::Clock clock;

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
                }
                else if (event.text.unicode == 10)
                {
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
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
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

void Game::update(const sf::Time& delta)
{
}

void Game::draw(const sf::Time& delta)
{
    renderWindow->clear(sf::Color(20, 20, 20));
    renderWindow->display();
}
