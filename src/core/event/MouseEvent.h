#ifndef HEXPIP_MOUSEEVENT_H
#define HEXPIP_MOUSEEVENT_H

#include "Event.h"

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(const float x, const float y): m_x(x), m_y(y) {}

    [[nodiscard]] float GetX() const { return m_x; }
    [[nodiscard]] float GetY() const { return m_y; }

private:
    float m_x, m_y;
};

#endif //HEXPIP_MOUSEEVENT_H