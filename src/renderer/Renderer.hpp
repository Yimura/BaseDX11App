#pragma once
#include "common.hpp"

class Renderer final
{
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
	static bool init()
	{
		return get()._init();
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
	[[nodiscard]] bool _init() const;

	[[nodiscard]] bool _loop() const;

	void _begin_frame() const;
	void _end_frame() const;
	[[nodiscard]] bool _win_message() const;
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);