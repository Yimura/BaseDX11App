#pragma once
#include "Backend.hpp"
#include "Window.hpp"

namespace dx11
{
    using RenderCallback = std::function<void()>;

    class Renderer
    {
    private:
        std::unique_ptr<Backend> m_Backend;
        std::unique_ptr<Window> m_Window;

        inline static std::map<std::uint32_t, RenderCallback> m_RenderCallbacks;

        Renderer() = default;

    public:
        virtual ~Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) noexcept = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&&) noexcept  = delete;
        
        static bool AddRenderCallback(RenderCallback&& callback, const std::uint32_t priority);
        static bool AddWndProcCallback(WndProcCallback&& callback, const std::uint32_t priority);

        static bool Init();
        static void Destroy();

        static bool Tick();

    protected:
        friend class Backend;
        friend class Window;

        static Backend* GetBackend()
        { return GetInstance().m_Backend.get(); }
        static Window* GetWindow()
        { return GetInstance().m_Window.get(); }

    private:
        static Renderer& GetInstance()
        {
            static Renderer i{};
            return i;
        }

        bool InitImpl();
        void DestroyImpl();

        void NewFrame() const;
        bool TickImpl() const;
        void EndFrame() const;

        bool HandleWinMessages() const;
        
    };
}