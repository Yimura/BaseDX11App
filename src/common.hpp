#pragma once

#include <Windows.h>
#include <d3d11.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <array>
#include <format>
#include <functional>
#include <map>
#include <string_view>
#include <ranges>

#include <memory>
#include <thread>

#include <AsyncLogger/Logger.hpp>

#include "FileMgr/FileMgr.hpp"

namespace dx11
{
    using namespace std::chrono_literals;
    using namespace al;

    inline bool g_Running = true;
}