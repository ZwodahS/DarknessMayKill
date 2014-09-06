#include "zf_twindow.hpp"
namespace zf
{
    TW_Factory::TW_Factory()
        : imageSize(0), inited(false), texture(nullptr)
    {
    }

    TW_Factory::~TW_Factory()
    {
    }

    void TW_Factory::init(int imageSize, int maxRow, int maxCol)
    {
        if (inited)
        {
            return;
        }

        inited = true;
        this->imageSize = imageSize;
        ascii_starts = 0;
        ascii_ends = ascii_starts;

        const sf::Vector2i spritesheetSize(imageSize * maxCol, imageSize * maxRow);
        {
            texture = new sf::Texture();
            texture->create(spritesheetSize.x, spritesheetSize.y);
            spritesheet.create(texture, sf::IntRect(0, 0, spritesheetSize.x, spritesheetSize.y));
            int row = 0, col = 0;
            for (int i = 32; i < 127; i++)
            {
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                characters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
                ascii_ends++;
            }
            special_starts = ascii_ends;
            special_ends = special_starts;
            for (int i = 0; i < TotalSpecialChar; i++)
            {
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                specialCharacters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
                special_ends++;
            }
            while(row != maxRow)
            {
                // create all the spare location
                auto region = spritesheet.createRegion(sf::IntRect(col * imageSize, row * imageSize, imageSize, imageSize));
                specialCharacters.push_back(region);
                col++;
                if (col == maxCol)
                {
                    col = 0;
                    row++;
                }
            }
        }
    }

    TiledWindow* TW_Factory::newWindow(const sf::Vector2i& windowSize, int cellSize)
    {
        return nullptr;
    }

    void TW_Factory::freeWindow(TiledWindow* window)
    {
    }

    std::vector<std::string> TW_Factory::autoload(const std::string& path)
    {
        std::vector<std::string> errors;
        if (!texture)
        {
            return errors;
        }
        sf::Image image;

        /// basic ascii character
        for (int i = 32; i < 127; i++)
        {
            image.loadFromFile(path + "/basic/" + intToString(i) + ".png");
            if (!overrideCharImage(i, image))
            {
                errors.push_back(std::string("Fail to add char ") + char(i));
            }
        }
        std::vector<std::string> extendedLoadStrings;
        for (int i = 0; i < 16; i++)
        {
            extendedLoadStrings.push_back("border_" + intToString(i) + ".png");
        }
        for (int i = 0; i < 16; i++)
        {
            extendedLoadStrings.push_back("cross_" + intToString(i) + ".png");
        }
        extendedLoadStrings.push_back("center_dot.png");
        extendedLoadStrings.push_back("alternate_1.png");
        extendedLoadStrings.push_back("alternate_2.png");
        extendedLoadStrings.push_back("arrow_up.png");
        extendedLoadStrings.push_back("arrow_right.png");
        extendedLoadStrings.push_back("arrow_down.png");
        extendedLoadStrings.push_back("arrow_left.png");
        extendedLoadStrings.push_back("fill.png");
        for (int i = 0; i < extendedLoadStrings.size(); i++)
        {
            image.loadFromFile(path + "/special/" + extendedLoadStrings[i]);
            if (!addSpecialCharImage(i, image))
            {
                errors.push_back("Fail to add special char /special/" + extendedLoadStrings[i]);
            }
        } 
        return errors;
    }

    bool TW_Factory::overrideCharImage(char c, const sf::Image& image)
    {
        TextureRegion charRegion = getChar(c);
        if (charRegion.texture)
        {
            spritesheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }

    TextureRegion TW_Factory::getChar(char c) const
    {
        if ((int)c < 32 || (int)c >= 127)
        {
            return emptyRegion;
        }
        c -= 32;
        return characters.size() > c ? characters[int(c)] : emptyRegion;
    }

    bool TW_Factory::addSpecialCharImage(int c, const sf::Image& image)
    {
        TextureRegion charRegion = getSpecialChar(c);
        if (charRegion.texture)
        {
            spritesheet.addImage(image, charRegion.srcClip.left, charRegion.srcClip.top);
            return true;
        }
        return false;
    }

    TextureRegion TW_Factory::getSpecialChar(int c) const
    {
        if (specialCharacters.size() > c && c >= 0)
        {
            return specialCharacters[c];
        }
        return emptyRegion;
    }

}
