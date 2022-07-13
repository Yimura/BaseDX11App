#pragma once
#include "common.hpp"

using wndproc_callback = std::function<LRESULT CALLBACK(HWND, std::uint32_t, WPARAM, LPARAM)>;

class Window final
{
	HINSTANCE m_hinstance{};
	HWND m_hwnd{};
	WNDCLASS m_wnd_class{ 0 };

public:
	~Window() = default;
	Window(const Window&) = delete;
	Window(Window&&) noexcept = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) noexcept = delete;

	static void add_callback(wndproc_callback&& callback, const std::string_view id);
	static bool create_window(const wchar_t* class_name, const wchar_t* window_name)
	{
		return get()._create_window(class_name, window_name);
	}
	static HWND& current_window()
	{
		return get().m_hwnd;
	}
	static void destroy()
	{
		get()._destroy();
	}
	static void show_window()
	{
		get()._show_window();
	}

	static LRESULT CALLBACK wnd_proc(HWND hwnd, std::uint32_t umsg, WPARAM wparam, LPARAM lparam);
	inline static std::map<const std::string_view, wndproc_callback> m_wndproc_callbacks;

private:
	Window() = default;
	static Window& get()
	{
		static Window i{};
		return i;
	}

	bool _create_window(const wchar_t* class_name, const wchar_t* window_name);
	void _destroy() const;
	void _show_window() const;
};
