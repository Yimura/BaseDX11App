#include "common.hpp"
#include "gui.hpp"
#include "renderer/Renderer.hpp"
#include <imgui.h>

void gui::main_window()
{
	ImGui::Begin("Hello");

	if (ImGui::Button("Exit Program"))
		Renderer::exit();

	ImGui::End();
}
