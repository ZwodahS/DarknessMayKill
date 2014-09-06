#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <boost/format.hpp>

#include "../zf/zf_twindow.hpp"

#include "Logger.hpp"
#include "KeyMap.hpp"
#include "ui/DisplayManager.hpp"
/**
 * Game should hold all the global variable.
 */
class Game
{
//////////////////// Constants ////////////////////
public:
    static const std::string ResourcePath;
    static const std::string Version;
    static const std::string VersionName;
    static const std::string Title;
//////////////////// Core ////////////////////
public:
    Game();
    ~Game();

    void init();
    void run();

    const sf::Vector2i& getScreenSize() const;
private:
    sf::Vector2i screenSize;
    sf::Vector2i coreCellSize;
    sf::Vector2i termSize;
    int screenMultiplier;
    int framerate;
//////////////////// Assets ////////////////////
public:
    
private:
    void initAssets();
//////////////////// Logger ////////////////////
public:
    Logger& getLogger();
private:
    Logger logger;
//////////////////// KeyMapping ////////////////////
public:
    KeyMap keyMap;
private:
    void initKeys();
    std::vector<int> inputs;
//////////////////// UI ////////////////////
public:
    void initUI();
    void update(const sf::Time& delta);
    void draw(const sf::Time& delta);
private:
    sf::RenderWindow* renderWindow;
    zf::TiledWindowFactory* tw_factory;
    zf::TiledWindow* window;
    DisplayManager* displayManager;
};
#endif
