#include "BaseExplorerItem.hpp"

namespace dx11
{
    BaseExplorerItem::BaseExplorerItem(std::filesystem::path&& path) :
        m_Path(path)
    {

    }

    [[nodiscard]] bool BaseExplorerItem::Exists() const
    {
        return exists(m_Path);
    }

    const std::filesystem::path& BaseExplorerItem::Path() const
    {
        return m_Path;
    }
}