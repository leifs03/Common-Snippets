/**
 * @file     logmanager.hpp
 * @project  Common Snippets
 * @brief    Singleton that handles access to the program's log file
 * @requires C++17 or above, fmt 9.1.0 or above
 * @author   leifs
 */

#ifndef SNIPPETS_LOGMANAGER_HPP
#define SNIPPETS_LOGMANAGER_HPP

#include <string>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <fmt/core.h>

class LogManager
{
public:
    /**
     * @brief Gets a reference to the LogManager
     * @return Reference to the LogManager singleton instance
     */
    static LogManager& getInstance() noexcept;

    enum SeverityLevel
    {
        None,
        Error,
        Warning,
        Info,
        Debug,
    };

    /**
     * @brief Logs a message at a given level.
     * @param msg Message to log.
     * @param level From the LogManager::SeverityLevel enum.
     */
    void log(const std::string& msg, SeverityLevel level) noexcept;

    void setLogLevel(SeverityLevel level) noexcept;
    void setLogToConsole(bool value) noexcept;
    void setLogToFile(bool value) noexcept;

    /**
     * @brief Logs a message with file, line, and function info at a given level.
     * @param msg Message to log.
     * @param level From the LogManager::SeverityLevel enum.
     */
#define LOG_WITH_INFO(msg, level) \
    LogManager::getInstance().log(\
    fmt::format("{}:{}:{} - {}", __FILE__, __LINE__, __func__, msg), level);


private:
    LogManager() noexcept;
    ~LogManager() noexcept;

    bool logToConsole = false;
    bool logToFile = true;
    SeverityLevel logLevel = Warning;

    std::filesystem::path logFilePath;
    std::ofstream logFile;

    std::mutex logMutex;

    /**
     * @brief Returns a timestamp formatted at HH:MM:SS
     */
    static std::string getTimestamp() noexcept;

public:
    // Delete the copy and move operators.
    LogManager(const LogManager&) = delete;
    LogManager(LogManager&&) = delete;
    LogManager& operator=(const LogManager&) = delete;
    LogManager& operator=(LogManager&&) = delete;
};

#endif //SNIPPETS_LOGMANAGER_HPP
