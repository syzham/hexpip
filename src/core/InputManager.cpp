#include "InputManager.h"

void InputManager::mouseEvent(const float x, const float y)
{
    m_x = x;
    m_y = y;
    m_dx = x - m_x;
    m_dy = y - m_y;
}

float InputManager::getMouseX() const
{
    return m_x;
}

float InputManager::getMouseY() const
{
    return m_y;
}

float InputManager::getMouseDeltaX() const
{
    return m_dx;
}

float InputManager::getMouseDeltaY() const
{
    return m_dy;
}

void InputManager::setKeyDown(const int keycode, const bool isDown)
{
    m_downKeyCodes[keycode] = isDown;
}

bool InputManager::isKeyDown(const int keycode) const
{
    return m_downKeyCodes[keycode];
}

void InputManager::setMouseClick(int mouseCode, const bool isDown)
{
    mouseCode++;
    if (isDown)
        m_mouseClick = m_mouseClick | (1 << mouseCode);
    else
        m_mouseClick = m_mouseClick & ~(1 << mouseCode);

}

bool InputManager::isMouseDown(const MouseButton mouseCode) const
{
    return m_mouseClick & mouseCode;
}