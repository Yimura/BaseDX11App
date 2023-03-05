#include "Folder.hpp"
#include "FileMgr.hpp"

namespace dx11
{
    Folder::Folder(std::filesystem::path&& path) :
        BaseExplorerItem(std::move(path))
    {

    }
}