#pragma once
#include "common.hpp"

using render_callback = std::function<void()>;

class Renderer final
{
	std::map<std::uint32_t, render_callback> m_render_callbacks;

	bool m_running = false;

public:
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) noexcept = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) noexcept = delete;

	static void destroy()
	{
		get()._destroy();
	}
	static void exit()
	{
		get().m_running = false;
	}
	static bool init()
	{
		return get()._init();
	}

	/**
	 * @brief Add a callback for your ImGui rendering, additionally give a rendering priority, higher will means more on top rendered.
	 */
	static bool add_callback(render_callback&& callback, const std::uint32_t priority)
	{
		return get()._add_callback(std::move(callback), priority);
	}
	[[nodiscard]] static bool loop()
	{
		return get()._loop();
	}

private:
	Renderer() = default;
	static Renderer& get()
	{
		static Renderer i{};

		return i;
	}

	void _destroy() const;
	[[nodiscard]] bool _init();

	[[nodiscard]] bool _add_callback(render_callback&& callback, std::uint32_t priority);
	[[nodiscard]] bool _loop() const;

	void _begin_frame() const;
	void _end_frame() const;
	[[nodiscard]] bool _win_message() const;
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);