#include "common.hpp"
#include "Backend.hpp"
#include "Window.hpp"

void Backend::_destroy()
{
	_cleanup_render_target();

	if (m_swap_chain)
		m_swap_chain->Release();
	if (m_device_context)
		m_device_context->Release();
	if (m_device)
		m_device->Release();

	m_swap_chain = nullptr;
	m_device_context = nullptr;
	m_device = nullptr;
}

bool Backend::_init()
{
	if (!_create_d3d11device_and_swap_chain())
		return false;

	_create_render_target();
	return true;
}

bool Backend::_create_d3d11device_and_swap_chain()
{
	constexpr auto level_count = 4;
	constexpr D3D_FEATURE_LEVEL levels[level_count] = {
	    D3D_FEATURE_LEVEL_10_0,
	    D3D_FEATURE_LEVEL_10_1,
	    D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_11_1
	};

	DXGI_SWAP_CHAIN_DESC desc{ 0 };
	desc.Windowed = true;
	desc.BufferCount = 2;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.Width = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.OutputWindow = Window::current_window();

#if defined(DEBUG) || defined(_DEBUG)
	constexpr std::uint32_t device_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	constexpr std::uint32_t device_flags = 0;
#endif

	D3D_FEATURE_LEVEL feature_level;
	const auto result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		device_flags,
		levels,
		level_count,
		D3D11_SDK_VERSION,
		&desc,
		&m_swap_chain,
		&m_device,
		&feature_level,
		&m_device_context);

	if (FAILED(result))
	{
		LOG(FATAL) << "Failed to create D3D11 device.";

		return false;
	}

	LOG(G3LOG_DEBUG) << "Created D3D11 device with feature level : [" << feature_level << "]";

	return true;
}

void Backend::_create_render_target()
{
	ID3D11Texture2D* back_buffer;
	swap_chain()->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
	device()->CreateRenderTargetView(back_buffer, nullptr, &m_render_target);
	back_buffer->Release();
}

void Backend::_cleanup_render_target()
{
	if (m_render_target)
	{
		m_render_target->Release();
		m_render_target = nullptr;
	}
}
