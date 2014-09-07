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
#include "MainScreen.hpp"
#include "DisplayManager.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_stringformat.hpp"
#include <iostream>
const std::string MainScreen::Type = "main";
const std::string MainScreen::OutDataType = "MS_OUT";
const int MainScreen::NumOptions = 2;
const std::string MainScreen::OptionsString[MainScreen::NumOptions] = { "Play!", "Quit!" };
const MainScreen::  Choice MainScreen::OptionsChoice[MainScreen::NumOptions] = { MainScreen::NewGame, MainScreen::Exit };

MainScreen::MainScreen(DisplayManager& manager)
    : DisplayObject(manager),selected(0), titleWindow(nullptr)
{
}

MainScreen::~MainScreen()
{
}

MainScreen::OutData::OutData(MainScreen::Choice choice)
    : DisplayData(OutDataType), choice(choice)
{
}

bool MainScreen::init(DisplayData* data)
{
    titleWindow = manager.windowFactory.newWindow(sf::Vector2i(29, 5), manager.game.getCoreCellSize() * 2);
    titleWindow->alignWindow(zf::AlignmentX::Center, zf::AlignmentY::Bottom, sf::Vector2f(manager.game.getScreenSize().x / 2, manager.game.getCoreCellSize() * 16));

    selectionWindow = manager.windowFactory.newWindow(sf::Vector2i(30, 10), manager.game.getCoreCellSize());
    selectionWindow->alignWindow(zf::AlignmentX::Center, zf::AlignmentY::Top, sf::Vector2f(manager.game.getScreenSize().x / 2, manager.game.getCoreCellSize() * 24));
    // initial draw, since the title will not change .
    titleWindow->putString(0, 1, titleWindow->windowSize.x, "Darkness may kill", zf::AlignmentX::Center);
    titleWindow->putString(0, 3, titleWindow->windowSize.x, (zf::format("%s (%s)") % Game::Version % Game::VersionName).str, zf::AlignmentX::Center);
    return true;
}

DisplayData* MainScreen::getReturnValue()
{
    return new OutData(selected == 0 ? NewGame : Exit);
}

void MainScreen::destroy()
{
    if (titleWindow)
    {
        manager.windowFactory.freeWindow(titleWindow);
    }
    if (selectionWindow)
    {
        manager.windowFactory.freeWindow(selectionWindow);
    }
}

bool MainScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::G_Up)
    {
        selected = selected <= 0 ? 0 : selected >= NumOptions ? NumOptions - 1 : selected - 1;
    }
    else if (action == Action::G_Down)
    {
        selected = selected < 0 ? 0 : selected >= NumOptions - 1 ? NumOptions - 1 : selected + 1;
    }
    else if (action == Action::G_Select)
    {
        done = true;
    }
    return true;
}

void MainScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void MainScreen::update(const sf::Time& delta)
{
}

void MainScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    titleWindow->draw(window);

    selectionWindow->clean();
    for (int i = 0; i < NumOptions; i++)
    {
        int state = colors::Mod_Base | (i == selected ? colors::Mod_Selected : 0);
        selectionWindow->putString(0, 1 + (i * 2), selectionWindow->windowSize.x, OptionsString[i], zf::AlignmentX::Center, 0, colors::Button_Text[state]);
    }
    selectionWindow->draw(window);    
}

std::string MainScreen::getType() const
{
    return Type;
}
