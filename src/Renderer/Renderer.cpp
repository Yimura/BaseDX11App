#include "Renderer.hpp"
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>

namespace dx11
{
    bool Renderer::AddRenderCallback(RenderCallback &&callback, const std::uint32_t priority)
    {
        if (const auto result = m_RenderCallbacks.insert({ priority, callback }).second; !result)
        {
            LOG(WARNING) << "Duplicate rendering priority given.";

            return result;
        }
        return true;
    }

    bool Renderer::AddWndProcCallback(WndProcCallback &&callback, const std::uint32_t priority)
    {
        return GetInstance().m_Window->AddWndProcCallback(std::move(callback), priority);
    }

    bool Renderer::Init()
    {
        return GetInstance().InitImpl();
    }

    void Renderer::Destroy()
    {
        GetInstance().DestroyImpl();
    }

    bool Renderer::Tick()
    {
        return GetInstance().TickImpl();
    }

    bool Renderer::InitImpl()
    {
        LOG(VERBOSE) << "Creating Backend and Window instance.";
        m_Backend = std::make_unique<Backend>();
        m_Window = std::make_unique<Window>("dx11BaseApp", "Base DX11 App");
        LOG(VERBOSE) << "Instances created!";

        LOG(VERBOSE) << "Initialising Backend and Window.";
        if (!m_Window->Init())
            return false;
        if (!m_Backend->Init(m_Window->GetWindow()))
            return false;
        LOG(VERBOSE) << "Initialised.";

        LOG(VERBOSE) << "Opening window...";
        m_Window->ShowWindow();

        LOG(VERBOSE) << "Registering ImGui::WndProc callback.";
        AddWndProcCallback(ImGui_ImplWin32_WndProcHandler, 9999);
        LOG(VERBOSE) << "Registered ImGui::WndProc callback.";

        LOG(VERBOSE) << "Initialising ImGui...";
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplDX11_Init(m_Backend->GetDevice(), m_Backend->GetDeviceContext());
        ImGui_ImplWin32_Init(m_Window->GetWindow());
        LOG(VERBOSE) << "ImGui initialised.";

        return true;
    }

    void Renderer::DestroyImpl()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    void Renderer::NewFrame() const
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    bool Renderer::TickImpl() const
    {
        if (!g_Running || !HandleWinMessages())
            return false;

        NewFrame();
        for (const auto& callback : m_RenderCallbacks | std::views::values)
        {
            callback();
        }
        EndFrame();

        return true;
    }

    void Renderer::EndFrame() const
    {
        ImGui::Render();

        const auto render_target_view = GetBackend()->GetRenderTarget();
        GetBackend()->GetDeviceContext()->OMSetRenderTargets(1, &render_target_view, nullptr);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        GetBackend()->GetSwapChain()->Present(1, 0);
    }

    bool Renderer::HandleWinMessages() const
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                return false;
        }
        return true;
    }
}