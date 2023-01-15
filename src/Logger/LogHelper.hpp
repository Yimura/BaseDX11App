#pragma once
#include "common.hpp"

namespace dx11
{
    using namespace al;

    #define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase

    class LogHelper
    {
    public:
        LogHelper(const std::filesystem::path outPath);
        ~LogHelper();

        static void Cout(LogMessagePtr message);
        static void FileOut(LogMessagePtr message);

    private:
        static int GetLevelColor(const eLogLevel level);
        static const char* GetLevelString(const eLogLevel level);

    private:
        inline static std::filesystem::path m_FilePath;
        inline static std::ofstream m_FileOut;

    };
}