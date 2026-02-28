#include "Graphics.h"

#include <string>

int Graphics::Init(const GLADloadproc id, const int width, const int height)
{
    if (!gladLoadGLLoader(id)) {
        return 1;
    }

    const GLuint vs = compile(GL_VERTEX_SHADER,   kVert);
    const GLuint fs = compile(GL_FRAGMENT_SHADER, kFrag);
    m_prog = link(vs, fs);

    m_vao = m_vbo = 0;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, reinterpret_cast<void *>(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glUseProgram(m_prog);
    m_uTexLoc  = glGetUniformLocation(m_prog, "uTex");
    m_uTintLoc = glGetUniformLocation(m_prog, "uTint");

    m_width = width;
    m_height = height;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    return 0;
}

void Graphics::BeginFrame(const int width, const int height)
{
    m_width = width;
    m_height = height;

    glClearColor(0.08f, 0.08f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_prog);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void Graphics::EndFrame() {}

void Graphics::Destroy() const
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_prog);
}


GLuint Graphics::compile(const GLenum type, const char* src) {
    const GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len=0; glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetShaderInfoLog(s, len, nullptr, log.data());
        std::fprintf(stderr, "Shader compile error:\n%s\n", log.c_str());
        std::exit(1);
    }
    return s;
}


GLuint Graphics::link(const GLuint vs, const GLuint fs) {
    const GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    GLint ok = 0; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len=0; glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(p, len, nullptr, log.data());
        std::fprintf(stderr, "Program link error:\n%s\n", log.c_str());
        std::exit(1);
    }
    glDetachShader(p, vs);
    glDetachShader(p, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}

void Graphics::DrawSprite(const float x, const float y, const float w, const float h, const GLuint textureID,
                            const float u0, const float v0, const float u1, const float v1,
                            const float tintR, const float tintG, const float tintB, const float tintA) const {
    const float x0 = pxToNdcX(x,     m_width);
    const float y0 = pxToNdcY(y,     m_height);
    const float x1 = pxToNdcX(x + w, m_width);
    const float y1 = pxToNdcY(y + h, m_height);

    const float verts[6 * 4] = {
        x0, y0,     u0, v0,
        x1, y0,     u1, v0,
        x1, y1,     u1, v1,

        x0, y0,     u0, v0,
        x1, y1,     u1, v1,
        x0, y1,     u0, v1,
    };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (m_uTexLoc >= 0) glUniform1i(m_uTexLoc, 0);
    if (m_uTintLoc >= 0) glUniform4f(m_uTintLoc, tintR, tintG, tintB, tintA);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int Graphics::getHeight() const {
    return m_height;
}

int Graphics::getWidth() const {
    return m_width;
}