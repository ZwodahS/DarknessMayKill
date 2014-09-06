#include "KeyMap.hpp"
#include <iostream>
KeyMap::KeyMap()
{
}

KeyMap::~KeyMap()
{
}

void KeyMap::addMapping(int c, Action key)
{
    mappings[c] = key;
}

Action KeyMap::getMapping(int c) const
{
    auto result = mappings.find(c);
    return result == mappings.end() ? Action::G_None : (*result).second;
}

int KeyMap::getKey(Action action) const
{
    for (auto it = mappings.begin(); it != mappings.end(); it++)
    {
        if ((*it).second == action)
        {
            return (*it).first;
        }
    }
    return -1;
}
