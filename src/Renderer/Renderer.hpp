#pragma once
#include "Backend.hpp"
#include "Window.hpp"

namespace dx11
{
    class Renderer
    {
    private:
        std::unique_ptr<Backend> m_Backend;
        std::unique_ptr<Window> m_Window;

    public:
 
    };   
}