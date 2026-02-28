#ifndef HEXPIP_GRAPHICS_H
#define HEXPIP_GRAPHICS_H

#include <glad/glad.h>

static const auto* kVert = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

void main() {
    vUV = aUV;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

static const auto* kFrag = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTex;
uniform vec4 uTint;

void main() {
    FragColor = texture(uTex, vUV) * uTint;
}
)";

inline float pxToNdcX(const float x_px, const int width)  { return  (x_px / static_cast<float>(width))  * 2.0f - 1.0f; }
inline float pxToNdcY(const float y_px, const int height) { return -(y_px / static_cast<float>(height)) * 2.0f + 1.0f; }

class Graphics
{
public:
    int Init(GLADloadproc id, int width, int height);
    void BeginFrame(int width, int height);
    static void EndFrame();
    void DrawSprite(float x, float y, float w, float h, GLuint textureID,
        float u0 = 0.0, float v0 = 0.0, float u1 = 1.0, float v1 = 1.0,
        float tintR=1.0, float tintG=1.0, float tintB=1.0, float tintA=1.0) const;
    void Destroy() const;
    int getWidth() const;
    int getHeight() const;
private:
    static GLuint compile(GLenum type, const char* src);
    static GLuint link(GLuint vs, GLuint fs);
    GLuint m_vao = 0, m_vbo = 0, m_prog = 0;
    GLint m_uTexLoc = -1;
    GLint m_uTintLoc = -1;
    int m_width = 0, m_height = 0;
};


#endif //HEXPIP_GRAPHICS_H