#ifndef HEXPIP_UISPRITE_H
#define HEXPIP_UISPRITE_H
#include <cstdint>

struct UISprite
{
    std::uint32_t textureID;
    float u0, v0, u1, v1;
    float r, g, b, a;
};

#endif //HEXPIP_UISPRITE_H