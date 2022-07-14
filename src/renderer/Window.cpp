#include "common.hpp"
#include "Window.hpp"
#include "Backend.hpp"

void Window::add_callback(wndproc_callback&& callback, const std::string_view id)
{
	m_wndproc_callbacks.emplace(id, callback);
}

LRESULT Window::wnd_proc(HWND hwnd, std::uint32_t umsg, WPARAM wparam, LPARAM lparam)
{
	for (auto& callback : m_wndproc_callbacks | std::views::values)
	{
		callback(hwnd, umsg, wparam, lparam);
	}

	switch (umsg)
	{
	case WM_SIZE:
	{
		if (Backend::swap_chain() != nullptr && wparam != SIZE_MINIMIZED)
		{
			Backend::cleanup_render_target();
			Backend::swap_chain()->ResizeBuffers(
				0,
				LOWORD(lparam),
				HIWORD(lparam),
				DXGI_FORMAT_UNKNOWN,
				0);
			Backend::create_render_target();
		}
		return 0;
	}
	case WM_SYSCOMMAND:
	{
		if ((wparam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		break;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

bool Window::_create_window(const wchar_t* class_name, const wchar_t* window_name)
{
	if (m_hinstance == nullptr)
		m_hinstance = GetModuleHandle(nullptr);

	constexpr auto exe_var_size = 512;
	wchar_t exe_path[exe_var_size];
	GetModuleFileNameW(nullptr, exe_path, exe_var_size);

	m_wnd_class.style = CS_CLASSDC;
	m_wnd_class.lpfnWndProc = Window::wnd_proc;
	m_wnd_class.cbClsExtra = 0;
	m_wnd_class.cbWndExtra = 0;
	m_wnd_class.hInstance = m_hinstance;
	m_wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	m_wnd_class.lpszMenuName = nullptr;
	m_wnd_class.lpszClassName = class_name;

	if (!RegisterClass(&m_wnd_class))
	{
		if (const auto err = GetLastError(); err != ERROR_CLASS_ALREADY_EXISTS)
		{
			LOG(WARNING) << "Failed to register window class, error code [" << err << "]";

			return false;
		}
	}

	m_hwnd = CreateWindow(
		class_name, window_name,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		1280, 800,
		nullptr, nullptr,
		m_hinstance,
		nullptr);

	if (m_hwnd == nullptr)
	{
		const auto err = GetLastError();
		LOG(WARNING) << "Failed to create window, error code [" << err << "]";

		return false;
	}

	LOG(G3LOG_DEBUG) << "Window created successfully.";

	return true;
}

void Window::_destroy() const
{
	DestroyWindow(m_hwnd);
	UnregisterClass(m_wnd_class.lpszClassName, m_wnd_class.hInstance);
}

void Window::_show_window() const
{
	if (m_hwnd)
	{
		ShowWindow(m_hwnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hwnd);
	}
}
