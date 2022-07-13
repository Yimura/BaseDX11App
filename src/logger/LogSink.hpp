#pragma once
#include "common.hpp"
#include "LogColor.hpp"
#include <g3log/g3log.hpp>

struct LogSink
{
    void callback(g3::LogMessageMover log);

    static LogColor get_color(const LEVELS level);

    static std::string format_console(const g3::LogMessage& msg);
    static std::string format_file(const g3::LogMessage& msg);
};