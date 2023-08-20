#include "triangle.h"

#include <iostream>

f32 Triangle::vertices[9] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
};

Triangle::Triangle()
{
    x = 0.0f;
    y = 0.0f;

    translation = mat4_identity();
    rotation = mat4_identity();
    scale = mat4_identity();

    vertex_shader_source = nullptr;
    fragment_shader_source = nullptr;

    vertex_shader = 0;
    fragment_shader = 0;
    shader_program = 0;

    vao = 0;
    vbo = 0;

    success = 0;
}

void Triangle::init()
{
    /*
    vertex_shader_source = "#version 330 core\n"
                             "layout (location = 0) in vec3 aPos;\n"
                             "uniform mat4 translation;"
                             "uniform mat4 rotation;"
                             "uniform mat4 scale;"
                             "void main()\n"
                             "{\n"
                             "   gl_Position = translation * vec4(aPos, 1.0);\n"
                             "}\0";

    fragment_shader_source = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "    FragColor = vec4(0.8f, 0.8f, 0.3f, 1.0f);\n"
                               "}\0";

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n";
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n";
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    */
}

void Triangle::update(f32 delta_time)
{
    /*
    translation = mat4_identity();

    f32 speed = 0.01f;

    if(input->is_key_down(KEY_W))
        y += speed * delta_time;
    if(input->is_key_down(KEY_S))
        y -= speed * delta_time;
    if(input->is_key_down(KEY_D))
        x += speed * delta_time;
    if(input->is_key_down(KEY_A))
        x -= speed * delta_time;
    
    translation = mat4_translate(translation, vec3_create(x, y, 0.0f));
    */
}

void Triangle::draw()
{
    /*
    glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    u32 transformLoc = glGetUniformLocation(shader_program, "translation");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, translation.data);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */
}

void Triangle::shutdown()
{
    /*
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
    */
}