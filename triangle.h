#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "defines.h"

#include "app.h"
#include "engine.h"

class Triangle : public App
{
private:
    const char* m_vertex_shader_source;
    const char* m_fragment_shader_source;

    u32 m_vertex_shader;
    u32 m_fragment_shader;
    u32 m_shader_program;

    u32 m_vbo;
    u32 m_vao;

    int m_success;
    char m_info_log[512]{};

    static f32 vertices[9];
	
public:
    Triangle();

	void init() override;    
	void update(f32 delta_time) override;
	void draw() override;
	void shutdown() override;
};

#endif // TRIANGLE_H