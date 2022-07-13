#include "common.hpp"
#include "Logger.hpp"

void Logger::_destroy()
{
    destroy_g3();
    close_outstreams();
}

void Logger::_init(const std::filesystem::path& file)
{
    m_file = file;

    open_outstreams();
    init_g3();
}

void Logger::destroy_g3()
{
    m_worker->removeAllSinks();
    m_worker.reset();
}

void Logger::init_g3()
{
    m_worker = g3::LogWorker::createLogWorker();
    m_worker->addSink(std::make_unique<LogSink>(), &LogSink::callback);
    g3::initializeLogging(m_worker.get());
}

void Logger::close_outstreams()
{
    m_file_out.close();
}

void Logger::open_outstreams()
{
    m_file_out.open(m_file, std::ios::out | std::ios::trunc);
}