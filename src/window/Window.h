#ifndef HEXPIP_WINDOW_H
#define HEXPIP_WINDOW_H

#include "graphics/Graphics.h"

class InputManager;
class GLFWwindow;

class Window
{
public:
    Window(int width, int height, const char* title, InputManager& inputManager);
    int InitWindow();
    [[nodiscard]] bool IsRunning() const;
    void DestroyWindow() const;
    void BeginFrame();
    void EndFrame();
    Graphics& GetGraphics();

private:
    GLFWwindow* m_window{};
    Graphics m_graphics{};
    InputManager& m_inputManager;
    int m_width, m_height;
    const char* m_title;
};


#endif //HEXPIP_WINDOW_H