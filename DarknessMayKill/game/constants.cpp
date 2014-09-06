#include "Game.hpp"
const std::string Game::Version = "0.0.1";
const std::string Game::VersionName = "alpha";
const std::string Game::Title = "Darkness May Kill (v"+Game::Version+" -"+Game::VersionName+")";
#ifdef APPBUNDLE
const std::string Game::ResourcePath = resourcePath() + "/";
#else
const std::string Game::ResourcePath = "";
#endif
const int KeyMap::Key_None(-1);
const int KeyMap::Key_Enter(10);
const int KeyMap::Key_Escape = 27;
const int KeyMap::Key_Up = 128 + 1;
const int KeyMap::Key_Down = 128 + 2;
const int KeyMap::Key_Left = 128 + 4;
const int KeyMap::Key_Right = 128 + 8;
