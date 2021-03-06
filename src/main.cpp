#include "common.hpp"

#include "gui/gui.hpp"
#include "logger/Logger.hpp"
#include "renderer/Backend.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Window.hpp"

int main()
{
	Logger::init("./cout.log");

	if (!Window::create_window(L"base_dx11_app", L"BaseDX11App"))
		return 1;
	if (!Backend::init())
		return 1;
	Window::show_window();
	if (!Renderer::init())
		return 1;

	Renderer::add_callback(gui::main_window, 9999);

	while (Renderer::loop())
	{
		
	}

	Renderer::destroy();
	Backend::destroy();
	Window::destroy();

	LOG(INFO) << "Farewell...";
	Logger::destroy();

	return 0;
}