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
#include "../../zf/zf_conversion.hpp"

#include "RootObject.hpp"
#include "DisplayManager.hpp"
#include "MainScreen.hpp"
#include "../Game.hpp"
#include <iostream>
const std::string RootObject::Type = "Root";
RootObject::RootObject(DisplayManager& manager)
    : DisplayObject(manager), currentChild(nullptr)
    #ifndef NODEBUG
    , fps(nullptr)
    #endif
{
}

RootObject::~RootObject()
{
}

bool RootObject::init(DisplayData* data)
{
    #ifndef NODEBUG
    fps = manager.windowFactory.newWindow(sf::Vector2i(20, 1), 8);
    fps->alignWindow(zf::AlignmentX::Left, zf::AlignmentY::Bottom, sf::Vector2f(0, manager.game.getScreenSize().y));
    #endif
    return true;
}

DisplayData* RootObject::getReturnValue()
{
    return nullptr;
}

void RootObject::destroy()
{
}

bool RootObject::processKey(int key)
{
    return true;
}

void RootObject::childReturned(DisplayObject* child, DisplayData* data)
{
    if (currentChild == child)
    {
        if (child->getType() == MainScreen::Type)
        {
            auto outdata = static_cast<MainScreen::OutData*>(data);
            if (outdata->choice == MainScreen::Choice::NewGame)
            {
            }
            else if (outdata->choice == MainScreen::Choice::Exit)
            {
                done = true;
            }
        }
        currentChild = nullptr;
    }
}

void RootObject::update(const sf::Time& delta)
{
    if (!currentChild)
    {
        currentChild = manager.makeDisplayObject(MainScreen::Type, nullptr);
        manager.putDisplay(*currentChild);
    }    
}

void RootObject::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    #ifndef NODEBUG
    fps->clean();
    fps->putString(0, 0, zf::floatToString(1.0f / delta.asSeconds(), 2));
    fps->draw(window);
    #endif
}

std::string RootObject::getType() const
{
    return Type;
}
