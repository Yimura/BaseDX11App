#pragma once

#include <Windows.h>
#include <d3d11.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <array>
#include <format>
#include <string_view>

#include <memory>
#include <thread>

#include <AsyncLogger/Logger.hpp>

#include "FileMgr/FileMgr.hpp"

namespace dx11
{
    using namespace std::chrono_literals;
    using namespace al;
}