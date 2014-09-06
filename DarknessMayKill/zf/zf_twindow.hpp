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
 *
 *  visit http://github.com/ZwodahS/zframework for the latest version
 */
#ifndef _ZFRAMEWORK_ZF_TWINDOW_HPP_
#define _ZFRAMEWORK_ZF_TWINDOW_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
/***
 * zf_twindow dependency :
 *      .1 zf_spritesheet.hpp
 *      .2 zf_rect.hpp
 *      .3 zf_sprite.hpp
 *      .4 zf_conversion.hpp
 */
#include "zf_spritesheet.hpp"
#include "zf_rect.hpp"
#include "zf_sprite.hpp"
#include "zf_conversion.hpp"
/**
 * twindow is fork off zf_term. Instead of having a terminal, twindow will focus on drawing directly 
 * onto the renderwindow. The main purpose of twindow is the same as zf_term, providing a curse-like 
 * library on sfml.
 *
 * zf_term map closer to ncurses implementation, while twindow just provide a way to draw tiled sprites,
 * and provide ways to draw strings onto the screen.
 *
 * unlike zf_term, twindow will NOT provide the naming convention like curses.
 *  
 * Alot of things is also changed in twindow. there will be no concept of foreground and background,
 * as least not internally.
 */
namespace zf
{
    //////////////////// Special characters ////////////////////
    extern const int NORTH_BIT, EAST_BIT, SOUTH_BIT, WEST_BIT;
    extern const int Up, Right, Down, Left;
    extern const int Border[16];
    extern const int Cross[16];
    extern const int Center_dot;
    extern const int Diagonal[2];
    extern const int Alternate[2];
    extern const int Arrow[4];
    extern const int Fill;
    extern const int TotalSpecialChar;

    /**
     * TW_Factory allow us to create TiledWindow. It also holds all the assets
     * to the special characters for us. 
     */ 
    class TiledWindow;
    class TW_Factory
    {
    public: 
        const TextureRegion emptyRegion = TextureRegion();
        TW_Factory();
        ~TW_Factory();

        /**
         * Assume square images,
         * maxRow and maxCol the number of col/row for the spritesheet.
         */
        void init(int imageSize, int maxRow = 20, int maxCol = 20);

        /**
         * Create a tile window with the specific values.
         *      windowSize : the number of cells (x, and y) in the window
         *      cellSize : the size of each size.
         *
         *      cellSize should be multiple of 4s
         *      [4, 8, 12, 16, 20, 24, 28, 32]
         *      you can experiment with other values and see how it looks.
         *      
         *      The scale of the image depends on the cellSize and the image Size.
         *      Using the default image size,
         *      4 = 0.125
         *      8 = 0.25
         *      12 = 0.375
         *      16 = 0.5
         *      20 = 0.625
         *      24 = 0.75
         *      28 = 0.875
         *      32 = 1
         */
        TiledWindow* newWindow(const sf::Vector2i& windowSize, int cellSize);

        void freeWindow(TiledWindow* window);
        
        /**
         * Pass in the path to the root directory of the root location of the fonts.
         * This will auto load the files.
         * The files will be
         *  root
         *  |_ basic : contains all the ascii characters, filename should be 32.png to 126.png
         *  |_ special : contains the special required characters, filename should be
         *     |_ border_0.png to border_15.png
         *     |_ cross_0.png to cross_0.png
         *     |_ center_dot.png
         *     |_ diagonal_1.png to diagonal_2.png
         *     |_ alternate_1.png to alternate_2.png
         *     |_ fill.png
         *
         */
        std::vector<std::string> autoload(const std::string& path);
        
        /**
         * Override the char image for this specific character.
         * You shouldn't call this directly, instead replace the image 
         * in the folder and let autoload takes care of it.
         */ 
        bool overrideCharImage(char c, const sf::Image& image);
        TextureRegion getChar(char c) const;
    
        /**
         * c value less than TotalSpecialChar will override the default
         * images. If adding new images, use c value starting from TotalSpecialChar
         *
         * As usual, don't override the default sprite here, replace
         * the file in the image folder.
         */
        bool addSpecialCharImage(int c, const sf::Image& image);
        TextureRegion getSpecialChar(int c) const;
        
    ////////////////////////////////////////////////////////////////////
    private:
        sf::Texture* texture;
        SpriteSheet spritesheet;

        int ascii_starts;
        int ascii_ends;
        int special_starts;
        int special_ends;
        /*
         * Store char 32 to 126, index-0, so 32 is stored in position 0.
         */
        std::vector<TextureRegion> characters;
        /**
         * Store the region for the extended chars.
         */
        std::vector<TextureRegion> specialCharacters;
        /**
         * The size of each cell.
         */
        int imageSize;
        /**
         * The current list of window created by this TW_Factory
         */
        std::vector<TiledWindow*> windows;

        bool inited;
        friend TiledWindow;
    };
}
#endif
