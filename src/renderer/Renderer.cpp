#include "common.hpp"
#include "Renderer.hpp"
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include "Backend.hpp"
#include "Window.hpp"

void Renderer::_destroy() const
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool Renderer::_init() const
{
	Window::add_callback(ImGui_ImplWin32_WndProcHandler, "imgui_wndproc");

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	if (!ImGui_ImplDX11_Init(Backend::device(), Backend::device_context()))
	{
		LOG(WARNING) << "ImGui_ImplDX11_Init failure...";

		return false;
	}

	if (!ImGui_ImplWin32_Init(Window::current_window()))
	{
		LOG(WARNING) << "ImGui_ImplWin32_Init failure...";

		return false;
	}

	LOG(G3LOG_DEBUG) << "ImGui initialized...";

	return true;
}

bool Renderer::_loop() const
{
	if (!_win_message())
		return false;

	_begin_frame();

	ImGui::Begin("Hello");

	if (ImGui::Button("Exit Program"))
		return false;

	ImGui::End();

	_end_frame();
	return true;
}

void Renderer::_begin_frame() const
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Renderer::_end_frame() const
{
	ImGui::Render();

	const auto render_target_view = Backend::render_target();
	Backend::device_context()->OMSetRenderTargets(1, &render_target_view, nullptr);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Backend::swap_chain()->Present(1, 0); // Present with vsync
	//g_pSwapChain->Present(0, 0); // Present without vsync
}

bool Renderer::_win_message() const
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return false;
	}
	return true;
}
