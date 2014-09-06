#include "Game.hpp"
const std::string Game::Version = "0.0.1";
const std::string Game::VersionName = "alpha";
const std::string Game::Title = "Darkness May Kill (v"+Game::Version+" -"+Game::VersionName+")";
#ifdef APPBUNDLE
const std::string Game::ResourcePath = resourcePath() + "/";
#else
const std::string Game::ResourcePath = "";
#endif
