#ifndef HEXPIP_UIBUTTON_H
#define HEXPIP_UIBUTTON_H
#include <functional>

struct UIButton
{
    std::function<void()> onClick;
};

#endif //HEXPIP_UIBUTTON_H