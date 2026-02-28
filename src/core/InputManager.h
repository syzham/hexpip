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