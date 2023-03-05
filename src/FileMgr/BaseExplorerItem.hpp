#pragma once
#include <filesystem>

namespace dx11
{
    class BaseExplorerItem
    {
    public:
        BaseExplorerItem(std::filesystem::path&& path);

        [[nodiscard]] bool Exists() const;
        const std::filesystem::path& Path() const;

    protected:
        const std::filesystem::path m_Path;

    };
}