#include "LogHelper.hpp"
#include <array>
#include <filesystem>
#include <iostream>

namespace dx11
{
#define ADD_COLOR_TO_STREAM(color) "\x1b[" << int(color) << "m"
#define RESET_STREAM_COLOR "\x1b[0m"

    LogHelper::LogHelper(const std::filesystem::path outPath)
    {
        LogHelper::m_FilePath = outPath;
        LogHelper::m_FileOut = std::ofstream(m_FilePath, std::ios::binary | std::ios::trunc);

        Logger::Init();
        Logger::AddSink(LogHelper::Cout);
        Logger::AddSink(LogHelper::FileOut);
    }

    LogHelper::~LogHelper()
    {
        Logger::Destroy();
    }

    void LogHelper::Cout(LogMessagePtr message)
    {
        const auto timestamp = std::format("{0:%H:%M:%S}", message->Timestamp());
        const auto& location = message->Location();
        const auto level = message->Level();

        const auto file = std::filesystem::path(location.file_name()).filename().string();

        std::cout
            << "[" << timestamp << "]"
            << ADD_COLOR_TO_STREAM(GetLevelColor(level))
            << "[" << GetLevelString(level) << "/" << file << ":" << location.line() << "] "
            << RESET_STREAM_COLOR
            << message->Message()
            << std::flush;
    }

    void LogHelper::FileOut(LogMessagePtr message)
    {
        if (!m_FileOut.is_open())
            return;
        
        const auto timestamp = std::format("{0:%H:%M:%S}", message->Timestamp());
        const auto& location = message->Location();
        const auto level = message->Level();

        const auto file = std::filesystem::path(location.file_name()).filename().string();

        m_FileOut
            << "[" << timestamp << "]"
            << "[" << GetLevelString(level) << "/" << file << ":" << location.line() << "] "
            << message->Message()
            << std::flush;
    }

    int LogHelper::GetLevelColor(const eLogLevel level)
    {
        constexpr std::array<int, 4> levelColors = {{
            34,
            32,
            33,
            31
        }};

        return levelColors[level];
    }

    const char* LogHelper::GetLevelString(const eLogLevel level)
    {
        constexpr std::array<const char*, 4> levelStrings = {{
            { "DEBUG" },
            { "INFO" },
            { "WARN" },
            { "ERROR" }
        }};

        return levelStrings[level];
    }
}