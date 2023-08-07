#include "triangle.h"

#include <iostream>

f32 Triangle::vertices[9] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
};

Triangle::Triangle()
{
    m_vertex_shader_source = nullptr;
    m_fragment_shader_source = nullptr;

    m_vertex_shader = 0;
    m_fragment_shader = 0;
    m_shader_program = 0;

    m_vao = 0;
    m_vbo = 0;

    m_success = 0;
}

void Triangle::init()
{
    m_vertex_shader_source = "#version 330 core\n"
                             "layout (location = 0) in vec3 aPos;\n"
                             "void main()\n"
                             "{\n"
                             "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                             "}\0";

    m_fragment_shader_source = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "    FragColor = vec4(0.8f, 0.8f, 0.3f, 1.0f);\n"
                               "}\0";

    m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertex_shader, 1, &m_vertex_shader_source, nullptr);
    glCompileShader(m_vertex_shader);
    glGetShaderiv(m_vertex_shader, GL_COMPILE_STATUS, &m_success);
    if(!m_success)
    {
        glGetShaderInfoLog(m_vertex_shader, 512, nullptr, m_info_log);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n";
    }

    m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragment_shader, 1, &m_fragment_shader_source, nullptr);
    glCompileShader(m_fragment_shader);
    glGetShaderiv(m_fragment_shader, GL_COMPILE_STATUS, &m_success);
    if(!m_success)
    {
        glGetShaderInfoLog(m_fragment_shader, 512, nullptr, m_info_log);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n";
    }

    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, m_vertex_shader);
    glAttachShader(m_shader_program, m_fragment_shader);
    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &m_success);
    if(!m_success)
    {
        glGetProgramInfoLog(m_shader_program, 512, nullptr, m_info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    }

    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);

    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Triangle::update(f32 delta_time)
{

}

void Triangle::draw()
{
    glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shader_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::shutdown()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shader_program);
}