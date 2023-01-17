#include "WindowMng.hpp"

WindowMng::WindowMng(const uint32_t p_w, const uint32_t p_h) noexcept
: _width { p_w }, _height { p_h }
{
    glfwInit();

    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> window { 
        glfwCreateWindow( _width, _height, "HelloVulkan!", nullptr, nullptr),
        deleteWindow };

    assert(window.get());

    if( window.get() )
        std::cout << "Window created succesfully" << std::endl;
    else
        std::cout << "Window creation failed" << std::endl;

    _window = std::move(window);
}

