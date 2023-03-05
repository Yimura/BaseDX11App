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

    private:
        Backend();

    public:
        virtual ~Backend() = default;
        Backend(const Backend&) = delete;
        Backend(Backend&&) noexcept  = delete;
        Backend& operator=(const Backend&) = delete;
        Backend& operator=(Backend&&) noexcept  = delete;
        
        static void Destroy();
        static bool Init();

    private:
        static Backend& GetInstance()
        {
            static Backend i{};

            return i;
        }

        void DestroyImpl();
        bool InitImpl();

    };
}