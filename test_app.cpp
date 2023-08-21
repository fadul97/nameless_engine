#include "test_app.h"

#include <iostream>


f32 theta = 1.0f * 1.0f;

TestApp::TestApp(RendererX11* renderer)
{
    cube = {};
    projection = {};

    near = 0.1f;
	far = 1000.0f;
	fov = 90.0f;
	aspect_ratio = (f32)600 / (f32)800;
	fov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.15149f);

    this->renderer = renderer;
}

void TestApp::init()
{
    cube.tris = 
    {
        // SOUTH
        {0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f},

        // EAST
        {1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f},

        // NORTH                                                     
		{1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f},

		// WEST                                                      
		{0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f},

		// TOP                                                       
		{0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f},

		// BOTTOM                                                    
		{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f},
    };

    projection.data[0] = aspect_ratio * fov_rad;
    projection.data[5] = fov_rad;
    projection.data[10] = far / (far - near);
    projection.data[14] = (-far * near) / (far - near);
    projection.data[11] = 1.0f;
    projection.data[15] = 0.0f;

    /*
    projection.m[0][0] = aspect_ratio * fov_rad;
    projection.m[1][1] = fov_rad;
    projection.m[2][2] = far / (far - near);
    projection.m[3][2] = (-far * near) / (far - near);
    projection.m[2][3] = 1.0f;
    projection.m[3][3] = 0.0f;
    */

    // projection = mat4_perspective(fov_rad, aspect_ratio, near, far);
}

void TestApp::update(f32 delta_time)
{
    renderer->clear_window();

    Mat4 mat_rotx;
    Mat4 mat_rotz;
    theta += 1.0f * delta_time;

    // Rotation Z
    mat_rotz.m[0][0] = cosf(theta);
    mat_rotz.m[0][1] = sinf(theta);
    mat_rotz.m[1][0] = -sinf(theta);
    mat_rotz.m[1][1] = cosf(theta);
    mat_rotz.m[2][2] = 1;
    mat_rotz.m[3][3] = 1;

    // Rotation X
    mat_rotx.m[0][0] = 1;
    mat_rotx.m[1][1] = cosf(theta * 0.5f);
    mat_rotx.m[1][2] = sinf(theta * 0.5f);
    mat_rotx.m[2][1] = -sinf(theta * 0.5f);
    mat_rotx.m[2][2] = cosf(theta * 0.5f);
    mat_rotx.m[3][3] = 1;

    for(auto tri : cube.tris)
    {
        Triangle tri_projected;
        Triangle tri_translated;
        Triangle tri_rotated_z;
        Triangle tri_rotated_zx;

        // Rotate in Z-Axis
        tri_rotated_z.p[0] =  mat4_mult_vec3(mat_rotz, tri.p[0]);
        tri_rotated_z.p[1] =  mat4_mult_vec3(mat_rotz, tri.p[1]);
        tri_rotated_z.p[2] =  mat4_mult_vec3(mat_rotz, tri.p[2]);

        // Rotate in X-Axis
        tri_rotated_zx.p[0] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[0]);
        tri_rotated_zx.p[1] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[1]);
        tri_rotated_zx.p[2] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[2]);

        tri_translated = tri_rotated_zx;
        tri_translated.p[0].z = tri_rotated_zx.p[0].z + 3.0f;
        tri_translated.p[1].z = tri_rotated_zx.p[1].z + 3.0f;
        tri_translated.p[2].z = tri_rotated_zx.p[2].z + 3.0f;
        // Vec3 vec = vec3_create(tri.p[0], tri.y, tri.z);
        tri_projected.p[0] =  mat4_mult_vec3(projection, tri_translated.p[0]);
        tri_projected.p[1] =  mat4_mult_vec3(projection, tri_translated.p[1]);
        tri_projected.p[2] =  mat4_mult_vec3(projection, tri_translated.p[2]);

        // Scale into view
        tri_projected.p[0].x += 1.0f; tri_projected.p[0].y += 1.0f;
        tri_projected.p[1].x += 1.0f; tri_projected.p[1].y += 1.0f;
        tri_projected.p[2].x += 1.0f; tri_projected.p[2].y += 1.0f;
        tri_projected.p[0].x *= 0.5f * (f32)800;
        tri_projected.p[0].y *= 0.5f * (f32)600;
        tri_projected.p[1].x *= 0.5f * (f32)800;
        tri_projected.p[1].y *= 0.5f * (f32)600;
        tri_projected.p[2].x *= 0.5f * (f32)800;
        tri_projected.p[2].y *= 0.5f * (f32)600;

        // vec3_print(tri_projected.p[0]);
        // std::cout << "\n\np[1]";
        // vec3_print(tri_projected.p[1]);
        // std::cout << "\n\np[2]";
        // vec3_print(tri_projected.p[2]);
        // std::cout << "\n\np[0]";

        renderer->draw_triangle(
            tri_projected.p[0].x, tri_projected.p[0].y,
            tri_projected.p[1].x, tri_projected.p[1].y,
            tri_projected.p[2].x, tri_projected.p[2].y,
            (66UL << 16) | (165UL << 8) | 245UL
        );
    }
}

void TestApp::draw()
{
    // renderer->clear_window();

    // Mat4 mat_rotx;
    // Mat4 mat_rotz;
    // theta = 1.0f * 1.0f;

    // // Rotation Z
    // mat_rotz.m[0][0] = cosf(theta);
    // mat_rotz.m[0][1] = sinf(theta);
    // mat_rotz.m[1][0] = -sinf(theta);
    // mat_rotz.m[1][1] = cosf(theta);
    // mat_rotz.m[2][2] = 1;
    // mat_rotz.m[3][3] = 1;

    // // Rotation X
    // mat_rotx.m[0][0] = 1;
    // mat_rotx.m[1][1] = cosf(theta * 0.5f);
    // mat_rotx.m[1][2] = sinf(theta * 0.5f);
    // mat_rotx.m[2][1] = -sinf(theta * 0.5f);
    // mat_rotx.m[2][2] = cosf(theta * 0.5f);
    // mat_rotx.m[3][3] = 1;

    // for(auto tri : cube.tris)
    // {
    //     Triangle tri_projected;
    //     Triangle tri_translated;
    //     Triangle tri_rotated_zx;
    //     Triangle tri_rotated_z;

    //     // Rotate in Z-Axis
    //     tri_rotated_z.p[0] =  mat4_mult_vec3(mat_rotz, tri.p[0]);
    //     tri_rotated_z.p[1] =  mat4_mult_vec3(mat_rotz, tri.p[1]);
    //     tri_rotated_z.p[2] =  mat4_mult_vec3(mat_rotz, tri.p[2]);

    //     // Rotate in X-Axis
    //     tri_rotated_zx.p[0] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[0]);
    //     tri_rotated_zx.p[1] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[1]);
    //     tri_rotated_zx.p[2] =  mat4_mult_vec3(mat_rotx, tri_rotated_z.p[2]);

    //     tri_translated = tri_rotated_zx;
    //     tri_translated.p[0].z = tri.p[0].z + 3.0f;
    //     tri_translated.p[1].z = tri.p[1].z + 3.0f;
    //     tri_translated.p[2].z = tri.p[2].z + 3.0f;
    //     // Vec3 vec = vec3_create(tri.p[0], tri.y, tri.z);
    //     tri_projected.p[0] =  mat4_mult_vec3(projection, tri_translated.p[0]);
    //     tri_projected.p[1] =  mat4_mult_vec3(projection, tri_translated.p[1]);
    //     tri_projected.p[2] =  mat4_mult_vec3(projection, tri_translated.p[2]);

    //     // Scale into view
    //     tri_projected.p[0].x += 1.0f; tri_projected.p[0].y += 1.0f;
    //     tri_projected.p[1].x += 1.0f; tri_projected.p[1].y += 1.0f;
    //     tri_projected.p[2].x += 1.0f; tri_projected.p[2].y += 1.0f;
    //     tri_projected.p[0].x *= 0.5f * (f32)800;
    //     tri_projected.p[0].y *= 0.5f * (f32)600;
    //     tri_projected.p[1].x *= 0.5f * (f32)800;
    //     tri_projected.p[1].y *= 0.5f * (f32)600;
    //     tri_projected.p[2].x *= 0.5f * (f32)800;
    //     tri_projected.p[2].y *= 0.5f * (f32)600;

    //     // vec3_print(tri_projected.p[0]);
    //     // std::cout << "\n\np[1]";
    //     // vec3_print(tri_projected.p[1]);
    //     // std::cout << "\n\np[2]";
    //     // vec3_print(tri_projected.p[2]);
    //     // std::cout << "\n\np[0]";

    //     renderer->draw_triangle(
    //         tri_projected.p[0].x, tri_projected.p[0].y,
    //         tri_projected.p[1].x, tri_projected.p[1].y,
    //         tri_projected.p[2].x, tri_projected.p[2].y,
    //         (66UL << 16) | (165UL << 8) | 245UL
    //     );
    // }
}

void TestApp::shutdown()
{

}