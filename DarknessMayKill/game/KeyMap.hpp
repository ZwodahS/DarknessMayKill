#ifndef _GAME_KEYMAP_HPP_
#define _GAME_KEYMAP_HPP_
#include <map>
#include <string>
#include <stdlib.h>
enum class Action
{
    G_None,
    G_Up,
    G_Left,
    G_Right,
    G_Down,

    G_Select,
    G_Cancel,
};

namespace actions
{
    static const Action NavigationAction[4] = { Action::G_Up, Action::G_Down, Action::G_Left, Action::G_Right };
}

class KeyMap
{
public:
    static const int Key_None;
    static const int Key_Enter;
    static const int Key_Escape;
    static const int Key_Up;
    static const int Key_Down;
    static const int Key_Left;
    static const int Key_Right;

    KeyMap();
    ~KeyMap();
    void addMapping(int c, Action key);
    Action getMapping(int c) const;
    int getKey(Action action) const;
private:
    std::map<int, Action> mappings;
};
#endif
