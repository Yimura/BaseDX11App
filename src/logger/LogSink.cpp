#include "common.hpp"
#include "Logger.hpp"
#include "LogSink.hpp"

void LogSink::callback(g3::LogMessageMover log)
{
    std::cout << log.get().toString(LogSink::format_console) << std::flush;

    if (auto& file = Logger::get().m_file_out; file.is_open())
        file << log.get().toString(LogSink::format_file) << std::flush;
}

LogColor LogSink::get_color(const LEVELS level)
{
    switch (level.value)
    {
    case g3::kDebugValue:
        return LogColor::BLUE;
    case g3::kInfoValue:
        return LogColor::GREEN;
    case g3::kWarningValue:
        return LogColor::YELLOW;
    }
    return g3::internal::wasFatal(level) ? LogColor::RED : LogColor::WHITE;
}

std::string LogSink::format_console(const g3::LogMessage& msg)
{
    LogColor color = LogSink::get_color(msg._level);
    std::stringstream out;

    out
        << "[" << msg.timestamp("%H:%M:%S") << "]"
        << ADD_COLOR_TO_STREAM(color)
        << "[" << msg.level() << "/"
        << msg.file() << ":" << msg.line() << "]"
        << RESET_STREAM_COLOR
        << ": ";

    return out.str();
}

std::string LogSink::format_file(const g3::LogMessage& msg)
{
    std::stringstream out;

    out
        << "[" << msg.timestamp("%H:%M:%S") << "]"
        << "[" << msg.level() << "/"
        << msg.file() << ":" << msg.line() << "]"
        << ": ";

    return out.str();
}