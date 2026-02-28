#include "Window.h"

#include "core/InputManager.h"
#include <glfw/glfw3.h>
#include <iostream>

Window::Window(const int width, const int height, const char* title, InputManager& inputManager)
    : m_inputManager(inputManager), m_width(width), m_height(height), m_title(title)
{
}

int Window::InitWindow()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (!m_window) {
        std::cout << "Failed to initialise Window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, const int w, const int h){
        glViewport(0, 0, w, h);
    });

    m_graphics.Init(reinterpret_cast<GLADloadproc>(glfwGetProcAddress), m_width, m_height);
    glfwSetWindowUserPointer(m_window, this);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, const int scancode, const int action, int mods)
    {
        const auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        switch (action)
        {
            case GLFW_PRESS:
                self->m_inputManager.setKeyDown(scancode, true);
                break;
            case GLFW_RELEASE:
                self->m_inputManager.setKeyDown(scancode, false);
                break;
            default:
                break;
        }
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, const double xpos, const double ypos)
    {
        const auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        self->m_inputManager.mouseEvent(static_cast<float>(xpos), static_cast<float>(ypos));
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, const int button, const int action, int mods)
    {
        const auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        switch (action)
        {
            case GLFW_PRESS:
                self->m_inputManager.setMouseClick(button, true);
                break;
            case GLFW_RELEASE:
                self->m_inputManager.setMouseClick(button, false);
                break;
            default:
                break;
        }

    });
    return 0;
}

bool Window::IsRunning() const
{
    return !glfwWindowShouldClose(m_window);
}

void Window::BeginFrame()
{
    glfwPollEvents();
    glfwGetWindowSize(m_window, &m_width, &m_height);
    m_graphics.BeginFrame(m_width, m_height);
}

void Window::EndFrame()
{
  m_graphics.EndFrame();
  glfwSwapBuffers(m_window);
}

Graphics& Window::GetGraphics()
{
  return m_graphics;
}

void Window::DestroyWindow() const
{
    m_graphics.Destroy();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
