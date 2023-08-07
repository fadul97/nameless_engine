#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "defines.h"

#include "app.h"
#include "engine.h"
#include "c_math.h"

class Triangle : public App
{
private:
    f32 x;
    f32 y;
    Mat4 translation;
    Mat4 rotation;
    Mat4 scale;

    const char* vertex_shader_source;
    const char* fragment_shader_source;

    u32 vertex_shader;
    u32 fragment_shader;
    u32 shader_program;

    u32 vbo;
    u32 vao;

    int success;
    char info_log[512]{};

    static f32 vertices[9];
	
public:
    Triangle();

	void init() override;    
	void update(f32 delta_time) override;
	void draw() override;
	void shutdown() override;
};

#endif // TRIANGLE_H