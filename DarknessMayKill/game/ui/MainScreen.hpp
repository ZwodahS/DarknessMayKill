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
#ifndef _GAME_UI_MAINSCREEN_HPP_
#define _GAME_UI_MAINSCREEN_HPP_
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "../../zf/zf_twindow.hpp"
#include <vector>
class MainScreen : public DisplayObject
{
public:
    static const std::string Type;

    static const std::string OutDataType;
    enum Choice
    {
        NewGame,
        Exit,
    };
    class OutData : public DisplayData
    {
    public:
        OutData(Choice choice);

        Choice choice;
    };
    
    MainScreen(DisplayManager& manager);
    ~MainScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(sf::RenderWindow& window, const sf::Time& delta);
    virtual std::string getType() const;

    static const int NumOptions;
    static const std::string OptionsString[2];
    static const Choice OptionsChoice[2];

    int selected;
private:
    zf::TiledWindow* titleWindow;
    zf::TiledWindow* selectionWindow;
};
#endif
