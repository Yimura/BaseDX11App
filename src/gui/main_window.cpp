#include "common.hpp"
#include "gui.hpp"

void gui::main_window()
{
	const auto io = ImGui::GetIO();
	ImGui::SetNextWindowSize({ io.DisplaySize.x, io.DisplaySize.y }, ImGuiCond_Always);
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);

	ImGui::Begin("##main_window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);



	ImGui::End();
}
