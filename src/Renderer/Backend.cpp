#include "Backend.hpp"

namespace dx11
{
    Backend::Backend() :
        m_Device(nullptr),
        m_DeviceContext(nullptr),
        m_SwapChain(nullptr),
        m_RenderTarget(nullptr)
    {
        
    }

    void Backend::Destroy()
    {
        if (m_RenderTarget)
        {
            m_RenderTarget->Release();
        }

        if (m_SwapChain)
        {
            m_SwapChain->Release();
        }

        if (m_DeviceContext)
        {
            m_DeviceContext->Release();
        }

        if (m_Device)
        {
            m_Device->Release();
        }

        m_RenderTarget = nullptr;
        m_SwapChain = nullptr;
        m_DeviceContext = nullptr;
        m_Device = nullptr;
    }

    bool Backend::Init(HWND window)
    {
        LOG(VERBOSE) << "Initialising DX11 backend";

        constexpr auto levelCount = 4;
        constexpr D3D_FEATURE_LEVEL levels[levelCount] = {
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
        desc.OutputWindow = window;

#if defined(DEBUG) || defined(_DEBUG)
        constexpr std::uint32_t deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
        constexpr std::uint32_t deviceFlags = 0;
#endif

        D3D_FEATURE_LEVEL featureLevel;
        const auto result = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            deviceFlags,
            levels,
            levelCount,
            D3D11_SDK_VERSION,
            &desc,
            &m_SwapChain,
            &m_Device,
            &featureLevel,
            &m_DeviceContext);

        if (FAILED(result))
        {
            LOG(FATAL) << "Failed to create D3D11 device and swapchain.";

            return false;
        }

        LOG(VERBOSE) << "Created D3D11 device with feature level : [" << featureLevel << "]";

        ID3D11Texture2D* backBuffer;
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTarget);
        backBuffer->Release();

        LOG(VERBOSE) << "Created back buffer";
        LOG(INFO) << "DX11 backend ready";

        return true;
    }
}