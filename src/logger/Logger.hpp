#pragma once
#include "common.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include "LogSink.hpp"

#define ADD_COLOR_TO_STREAM(color) "\x1b[" << int(color) << "m"
#define RESET_STREAM_COLOR "\x1b[0m"
#define HEX_TO_UP(value) "0x" << std::hex << std::uppercase << DWORD64(value) << std::dec << std::nouppercase

class Logger final
{
    friend struct LogSink;

    std::filesystem::path m_file;
    std::ofstream m_file_out;

    std::unique_ptr<g3::LogWorker> m_worker;

public:
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    static void destroy()
    {
        get()._destroy();
    }
    static void init(const std::filesystem::path& file)
    {
        get()._init(file);
    }

private:
    Logger() = default;
    static Logger& get()
    {
        static Logger i{};
        return i;
    }

    void _destroy();
    void _init(const std::filesystem::path& file);

    void destroy_g3();
    void init_g3();

    void close_outstreams();
    void open_outstreams();


};