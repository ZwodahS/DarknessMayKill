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
#include "DisplayManager.hpp"
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "RootObject.hpp"
#include "MainScreen.hpp"
DisplayManager::DisplayManager(Game& game, zf::TiledWindowFactory& factory)
    : game(game), windowFactory(factory)
{
}

DisplayManager::~DisplayManager()
{
}


void DisplayManager::processKey(int key)
{
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        if ((**it).processKey(key))
        {
            break;
        }
    }
}

void DisplayManager::updateAll(const sf::Time& delta)
{
    auto display = stack.size() ? stack.back() : nullptr;
    while (display && display->done)
    {
        stack.pop_back();
        auto returnVal = display->getReturnValue();
        if (stack.size())
        {
            stack.back()->childReturned(display, returnVal);
        }
        display->destroy();
        delete display;
        delete returnVal;
        display = stack.size() ? stack.back() : nullptr;
    }
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        if (!(**it).done)
        {
            (**it).update(delta);
        }
    }
}

void DisplayManager::drawAll(sf::RenderWindow& window, const sf::Time& delta)
{
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        (**it).draw(window, delta);
    }
}

void DisplayManager::putDisplay(DisplayObject& object)
{
    stack.push_back(&object);
}

bool DisplayManager::isEmpty() const
{
    return stack.size() == 0;
}

DisplayObject* DisplayManager::makeDisplayObject(const std::string& type, DisplayData* data)
{
    DisplayObject* object = nullptr;
    if (type == RootObject::Type)
    {
        object = new RootObject(*this);
    }
    else if (type == MainScreen::Type)
    {
        object = new MainScreen(*this);
    }

    if (object && !object->init(data))
    {
        delete object;
        return nullptr;
    }
    return object;
}
