/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 */
#ifndef _GAME_UI_DISPLAYMANAGER_HPP_
#define _GAME_UI_DISPLAYMANAGER_HPP_
#include <list>
#include <SFML/Graphics.hpp>
#include "../../zf/zf_twindow.hpp"
class Game;
class KeyMap;
class DisplayObject;
class DisplayData;
class DisplayManager
{
public:
    DisplayManager(Game& game, zf::TiledWindowFactory& factory);
    ~DisplayManager();

    Game& game;
    zf::TiledWindowFactory& windowFactory;

    /**
     * Pass this key to be processed by the display objects, in order.
     * @param key
     */
    void processKey(int key);
    /**
     * Update all display object
     * @param time passed since last update
     */
    void updateAll(const sf::Time& delta);
    /**
     * Draw all display object
     * @param time passed since last draw.
     */
    void drawAll(sf::RenderWindow& window, const sf::Time& delta);
    /**
     * Put a display object into the "stack"
     * @param the state object.
     */
    void putDisplay(DisplayObject& state);
    /**
     * Make a display object of this type.
     * @param typestring == to the getType() of display object.
     * @param data use to init the object.
     * @return the display object created or nullptr if the display fails to create.
     */
    DisplayObject* makeDisplayObject(const std::string& type, DisplayData* data);
    /**
     * Get the list of DisplayObject.
     * @return const ref list of the internal display stack.
     */
    const std::list<DisplayObject*>& getDisplayObjects() const;
    /**
     * Check if the display stack is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() const;
private:
    std::list<DisplayObject*> stack;
};
#endif
