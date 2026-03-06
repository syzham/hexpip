#ifndef HEXPIP_INPUTMANAGER_H
#define HEXPIP_INPUTMANAGER_H

enum MouseButton
{
    Mouse1 = 1 << 1,
    Mouse2 = 1 << 2,
    Mouse3 = 1 << 3,
    Mouse4 = 1 << 4,
    Mouse5 = 1 << 5
};

namespace KeyCode {
#ifdef _WIN32
    constexpr int ESC = 1;
    constexpr int ENTER = 28;
    constexpr int SPACE = 57;
    constexpr int BACKSPACE = 14;
    constexpr int TAB = 15;
    constexpr int LEFT = 331;
    constexpr int UP = 328;
    constexpr int RIGHT = 333;
    constexpr int DOWN = 336;
#else
    constexpr int ESC = 53;
    constexpr int ENTER = 36;
    constexpr int SPACE = 49;
    constexpr int BACKSPACE = 51;
    constexpr int TAB = 48;
    constexpr int LEFT = 123;
    constexpr int UP = 126;
    constexpr int RIGHT = 124;
    constexpr int DOWN = 125;
#endif
}

class InputManager {
public:
    void mouseEvent(float x, float y);

    [[nodiscard]] float getMouseX() const;
    [[nodiscard]] float getMouseY() const;
    [[nodiscard]] float getMouseDeltaX() const;
    [[nodiscard]] float getMouseDeltaY() const;

    [[nodiscard]] bool isKeyDown(int keycode) const;
    void setKeyDown(int keycode, bool isDown);

    void setMouseClick(int mouseCode, bool isDown);
    [[nodiscard]] bool isMouseDown(MouseButton mouseCode) const;
private:
    bool m_downKeyCodes[256] = {false};
    int m_mouseClick = 0;
    int m_lastKeyPressed = -1;
    float m_x = 0, m_y = 0, m_dx = 0, m_dy = 0;
};


#endif //HEXPIP_INPUTMANAGER_H