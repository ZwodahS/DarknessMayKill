#ifndef _GAME_LOGGER_HPP_
#define _GAME_LOGGER_HPP_
#include <string>
class Logger
{
public:
    Logger();
    ~Logger();

    virtual void log(const std::string& message);
    virtual void debug(const std::string& message);
    virtual void error(const std::string& message);
};
#endif
