#include "common.hpp"
#include "gui.hpp"
#include "renderer/Renderer.hpp"
#include <imgui.h>

void gui::main_window()
{
	const auto io = ImGui::GetIO();
	ImGui::SetNextWindowSize({ io.DisplaySize.x, io.DisplaySize.y }, ImGuiCond_Always);
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);

	ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Exit Program"))
		Renderer::exit();

	ImGui::End();
}
