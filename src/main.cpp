#include "common.hpp"
#include "Logger/LogHelper.hpp"

using namespace al;

int main()
{
    using namespace dx11;
    FileMgr::Init("./");

    auto logger = LogHelper(
        FileMgr::GetProjectFile("./cout.log").Path());
    LOG(DEBUG) << "File manager and Logger are ready to be used.";

    return 0;
}