#include "Logger.hpp"
#include <iostream>
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::log(const std::string& message)
{
    std::cout << "[LOG]  " << message << std::endl;
}

void Logger::debug(const std::string& message)
{
    std::cout << "[DEBUG]  " << message << std::endl;
}

void Logger::error(const std::string& message)
{
    std::cout << "[ERROR]  " << message << std::endl;
}

