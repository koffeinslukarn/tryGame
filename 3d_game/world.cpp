#include "world.h"
#include <iostream>

static GLuint compileShader(GLenum type, const char* src)
{
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);

    int ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[1024];
        glGetShaderInfoLog(s, 1024, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << "\n";
    }
    return s;
}

static GLuint createProgram(const char* vsSrc, const char* fsSrc)
{
    const GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc);
    const GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);

    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    int ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[1024];
        glGetProgramInfoLog(p, 1024, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}

World::World()
{
    // Minimal shaders
    const char* vs = R"GLSL(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() { gl_Position = vec4(aPos, 1.0); }
    )GLSL";

    const auto fs = R"GLSL(
        #version 330 core
        out vec4 FragColor;
        void main() { FragColor = vec4(1.0, 0.0, 0.0, 1.0); } // red objet,
        // between 0 and 1 to change colour
    )GLSL";

    m_program = createProgram(vs, fs);

    // Två punkter = ett streck
    const float lineVerts[] = {
        -0.6f, -0.4f, 0.0f,  // vänster
        0.6f, -0.4f, 0.0f,  // höger
        0.0f,  0.6f, 0.0f   // toppen
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVerts), lineVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

World::~World()
{
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_program) glDeleteProgram(m_program);
}

void World::draw() const
{
    glUseProgram(m_program);

    // Linjetjocklek (OBS: funkar olika bra på olika drivers)
    glLineWidth(2.0f);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
