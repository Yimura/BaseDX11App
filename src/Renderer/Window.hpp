#pragma once

namespace dx11
{
    using WndProcCallback = std::function<LRESULT(HWND hwnd, std::uint32_t umsg, WPARAM wparam, LPARAM lparam)>;
    class Window
    {
    private:
        const std::string_view m_ClassName;
        const std::string_view m_WindowName;
        HINSTANCE m_Instance{ nullptr };
        HWND m_Hwnd{ nullptr };
        WNDCLASS m_WndClass{ 0 };

        inline static std::map<std::uint32_t, WndProcCallback> m_WndProcCallbacks;

    public:
        Window(const std::string_view className,  const std::string_view windowName);
        ~Window();

        bool AddWndProcCallback(WndProcCallback &&callback, const std::uint32_t priority);

        bool Init();
        HWND GetWindow() const
        { return m_Hwnd; }
        void ShowWindow() const;

    private:
        static LRESULT CALLBACK WndProc(HWND hwnd, std::uint32_t umsg, WPARAM wparam, LPARAM lparam);
        

    };
}