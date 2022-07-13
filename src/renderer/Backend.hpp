#pragma once
#include "common.hpp"

class Backend final
{
	ID3D11Device* m_device { nullptr };
	ID3D11DeviceContext* m_device_context { nullptr };
	IDXGISwapChain* m_swap_chain { nullptr };
	ID3D11RenderTargetView* m_render_target { nullptr };

public:
	~Backend() = default;
	Backend(const Backend&) = delete;
	Backend(Backend&&) noexcept = delete;
	Backend& operator=(const Backend&) = delete;
	Backend& operator=(Backend&&) noexcept = delete;

	static void destroy()
	{
		get()._destroy();
	}
	static bool init()
	{
		return get()._init();
	}

	static void create_render_target()
	{
		get()._create_render_target();
	}
	static void cleanup_render_target()
	{
		get()._cleanup_render_target();
	}

	static ID3D11Device* device()
	{
		return get().m_device;
	}
	static ID3D11DeviceContext* device_context()
	{
		return get().m_device_context;
	}
	static ID3D11RenderTargetView* render_target()
	{
		return get().m_render_target;
	}
	static IDXGISwapChain* swap_chain()
	{
		return get().m_swap_chain;
	}

private:
	Backend() = default;
	static Backend& get()
	{
		static Backend i{};
		return i;
	}

	void _destroy();
	[[nodiscard]] bool _init();

	[[nodiscard]] bool _create_d3d11device_and_swap_chain();

	void _create_render_target();
	void _cleanup_render_target();

};
