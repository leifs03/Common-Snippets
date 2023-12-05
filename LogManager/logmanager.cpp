/**
 * @file     logmanager.cpp
 * @project  Common Snippets
 * @brief    Singleton that handles access to the program's log file
 * @requires C++17 or above, fmt 9.1.0 or above
 * @author   leifs
 */

#include "logmanager.hpp"

#include <iostream>
#include <fmt/core.h>

LogManager::LogManager() noexcept
{
    logFilePath = /*<FILE PATH>*/;
    logFile.open(logFilePath, std::ios::trunc);
}



LogManager::~LogManager() noexcept
{
    if(logFile.is_open()) { logFile.close(); }
}



LogManager &LogManager::getInstance() noexcept
{
    static LogManager instance; // C++11 guarantees this is thread-safe
    return instance;
}



void LogManager::log(const std::string& msg, LogManager::SeverityLevel level) noexcept
{
    std::lock_guard<std::mutex> lock(logMutex);

    if(level == None || logLevel == None) { return; }
    if(static_cast<int>(level) > static_cast<int>(logLevel)) { return; }

    if(logToConsole)
    {
        std::cout << "[" << getTimestamp() << "] " << msg << std::endl;
    }

    if(logToFile && logFile.is_open())
    {
        logFile << "[" << getTimestamp() << "] " << msg << std::endl;
    }
}



void LogManager::setLogLevel(LogManager::SeverityLevel level) noexcept
{
    std::lock_guard<std::mutex> lock(logMutex);
    logLevel = level;
}



void LogManager::setLogToConsole(bool value) noexcept
{
    std::lock_guard<std::mutex> lock(logMutex);
    logToConsole = value;
}



void LogManager::setLogToFile(bool value) noexcept
{
    std::lock_guard<std::mutex> lock(logMutex);
    logToFile = value;
}



/**
 * @brief Returns a timestamp formatted at HH:MM:SS
 */
std::string LogManager::getTimestamp() noexcept
{
    std::time_t current_time = time(nullptr);
    std::tm local_time{};

#ifdef _WIN32
    localtime_s(&local_time, &current_time); // Windows safe localtime
#else
    localtime_r(&current_time, &local_time); // Non-Windows safe localtime
#endif

    return fmt::format(
            "{:02d}:{:02d}:{:02d}",
            local_time.tm_hour,
            local_time.tm_min,
            local_time.tm_sec
    );
}
