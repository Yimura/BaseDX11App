#include "common.hpp"
#include "GUI/GUI.hpp"
#include "Logger/LogHelper.hpp"
#include "Renderer/Renderer.hpp"

using namespace al;

int main()
{
    using namespace dx11;
    FileMgr::Init("./");

    auto logger = LogHelper(
        FileMgr::GetProjectFile("./cout.log").Path());
    LOG(VERBOSE) << "File manager and Logger are ready to be used.";

    if (!Renderer::Init())
    {
        LOG(FATAL) << "Failure while initialising Renderer!";

        return 1;
    }
    Renderer::AddRenderCallback(GUI::MainWindow, 9999);

    while (g_Running && Renderer::Tick());
    
    Renderer::Destroy();

    return 0;
}