#include "Window.hpp"
#include "Renderer.hpp"

namespace dx11
{
    Window::Window(const std::string_view className,  const std::string_view windowName) :
        m_ClassName(className),
        m_WindowName(windowName),
        m_Instance(GetModuleHandle(nullptr))
    {
        m_WndClass.style = CS_CLASSDC;
        m_WndClass.lpfnWndProc = Window::WndProc;
        m_WndClass.cbClsExtra = 0;
        m_WndClass.cbWndExtra = 0;
        m_WndClass.hInstance = m_Instance;
        m_WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        m_WndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        m_WndClass.lpszMenuName = nullptr;
        m_WndClass.lpszClassName = className.data();
    }

    Window::~Window()
    {
        DestroyWindow(m_Hwnd);
        UnregisterClass(m_WndClass.lpszClassName, m_WndClass.hInstance);
    }

    bool Window::AddWndProcCallback(WndProcCallback &&callback, const std::uint32_t priority)
    {
        if (const auto result = m_WndProcCallbacks.insert({ priority, callback }).second; !result)
        {
            LOG(WARNING) << "Duplicate rendering priority given.";

            return result;
        }
        return true;
    }

    bool Window::Init()
    {
        if (!RegisterClass(&m_WndClass))
        {
            if (const auto err = GetLastError(); err != ERROR_CLASS_ALREADY_EXISTS)
            {
                LOG(WARNING) << "Failed to register window class, error code [" << err << "]";

                return false;
            }
        }

        m_Hwnd = CreateWindowA(
            m_ClassName.data(),
            m_WindowName.data(),
            WS_OVERLAPPEDWINDOW,
            100, 100,
            1280, 800,
            nullptr, nullptr,
            m_Instance,
            nullptr
        );

        if (m_Hwnd == nullptr)
        {
            LOG(WARNING) << "Failed to create window, error code [" << GetLastError() << "]";

            return false;
        }

        LOG(INFO) << "Window created successfully.";
        return true;
    }

    void Window::ShowWindow() const
    {
        if (m_Hwnd)
        {
            ::ShowWindow(m_Hwnd, SW_SHOWDEFAULT);
            UpdateWindow(m_Hwnd);
        }
    }
    
    LRESULT Window::WndProc(HWND hwnd, std::uint32_t umsg, WPARAM wparam, LPARAM lparam)
    {
        switch (umsg)
        {
        case WM_SIZE:
        {
            if (const auto swapChain = Renderer::GetBackend()->GetSwapChain(); swapChain != nullptr && wparam != SIZE_MINIMIZED)
            {
                Renderer::GetBackend()->ResetRenderTarget();
                swapChain->ResizeBuffers(
                    0,
                    LOWORD(lparam),
                    HIWORD(lparam),
                    DXGI_FORMAT_UNKNOWN,
                    0
                );
                Renderer::GetBackend()->CreateRenderTarget();
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

        for (auto& callback : m_WndProcCallbacks | std::views::values)
        {
            callback(hwnd, umsg, wparam, lparam);
        }

        return DefWindowProc(hwnd, umsg, wparam, lparam);
    }
}