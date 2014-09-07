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
#ifndef _GAME_UI_DISPLAYOBJECT_HPP_
#define _GAME_UI_DISPLAYOBJECT_HPP_
#include <SFML/Graphics.hpp>
class DisplayManager;
class DisplayData;
class DisplayObject
{
public:
    DisplayObject(DisplayManager& manager);
    virtual ~DisplayObject();

    DisplayManager& manager;
    /**
     * bool representing if this display object is done
     * child just have to set this to true to exit the display.
     */
    bool done;
    /**
     * Init this display object with this display data.
     * @param the data to be used.
     * @return true if success, fail otherwise.
     */
    virtual bool init(DisplayData* data) = 0; 
    /**
     * Get the return value of this object after it returns.
     * @return the displaydata. This data will be freed in DisplayManager, so create it using the new operator.
     */
    virtual DisplayData* getReturnValue() = 0;
    /**
     * Destroy the display object.
     * Called when display object is destroyed.
     */
    virtual void destroy() = 0;
    /**
     * Get the string type of this display object.
     * @return type of the display object.
     */
    virtual std::string getType() = 0;
    /**
     * Process this key.
     * @param key
     * @return true if this key is processed by this object, false for it to be passed to the parent.
     */
    virtual bool processKey(int key) = 0;
    /**
     * Notify this display that the direct child has return.
     * @param the child display
     * @param the displaydata returned by that child
     */
    virtual void childReturned(DisplayObject* object, DisplayData* data) = 0;
    /**
     * Update this display.
     * @param time passed since last update.
     */
    virtual void update(const sf::Time& delta) = 0;
    /**
     * Update this display.
     * @param time passed since last draw.
     */
    virtual void draw(const sf::Time& delta) = 0;
};
#endif
