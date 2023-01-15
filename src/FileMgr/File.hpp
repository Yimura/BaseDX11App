#pragma once
#include "BaseExplorerItem.hpp"

namespace dx11
{
    class File final : public BaseExplorerItem
    {
    public:
        File(std::filesystem::path&& path);

        File Move(std::filesystem::path newPath);
    };
}