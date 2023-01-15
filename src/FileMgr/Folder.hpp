#pragma once
#include "BaseExplorerItem.hpp"

namespace dx11
{
    class Folder final : public BaseExplorerItem
    {
    public:
        Folder(std::filesystem::path&& folder);
    };
}