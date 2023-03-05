#pragma once
#include "common.hpp"

namespace dx11
{
    class Backend final
    {
    private:
        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;
        IDXGISwapChain* m_SwapChain;
        ID3D11RenderTargetView* m_RenderTarget;

    public:
        Backend();
        virtual ~Backend() = default;

        Backend(const Backend&) = delete;
        Backend(Backend&&) noexcept  = delete;
        Backend& operator=(const Backend&) = delete;
        Backend& operator=(Backend&&) noexcept  = delete;
        
        void Destroy();
        bool Init(HWND window);

        ID3D11Device* GetDevice() const
        { return m_Device; }
        ID3D11DeviceContext* GetDeviceContext() const
        { return m_DeviceContext; }
        IDXGISwapChain* GetSwapChain() const
        { return m_SwapChain; }

    private:

    };
}