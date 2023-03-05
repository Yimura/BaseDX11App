#include "GUI.hpp"

namespace dx11::GUI
{
    void MainWindow()
    {
        const auto io = ImGui::GetIO();
        ImGui::SetNextWindowSize({ io.DisplaySize.x, io.DisplaySize.y }, ImGuiCond_Always);
        ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
        if (ImGui::Begin("##main", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
        {
            if (ImGui::Button("Close application"))
            {
                g_Running = false;
            }
        }
        ImGui::End();
    }
}
