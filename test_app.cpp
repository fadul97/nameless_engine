#include "test_app.h"

#include <iostream>
#include <vector>

#include <algorithm>


// RGB888 color format: 0x00RRGGBB
#define RED_SHIFT   16
#define GREEN_SHIFT  8
#define BLUE_SHIFT   0

ul32 red = 0xFFFF0000;
ul32 green = 0xFF00FF00;
ul32 blue = 0xFF0000FF;
ul32 white = 0xFFFFFFFF;
ul32 black = 0xFF000000;
ul32 blueish = (66UL << 16) | (165UL << 8) | 245UL;

void MultiplyMatrixVector(Vec3& i, Vec3& o, Mat4 &m)
{
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        o.x /= w; o.y /= w; o.z /= w;
    }
}

ul32 adjust_brightness(ul32 color, f32 brightness) {
    u8 red = (color >> RED_SHIFT) & 0xFF;
    u8 green = (color >> GREEN_SHIFT) & 0xFF;
    u8 blue = (color >> BLUE_SHIFT) & 0xFF;

    red = (u8)(red * brightness);
    green = (u8)(green * brightness);
    blue = (u8)(blue * brightness);

    ul32 adjustedColor = (red << RED_SHIFT) | (green << GREEN_SHIFT) | (blue << BLUE_SHIFT);
    return adjustedColor;
}

TestApp::TestApp(RendererX11* renderer, char* obj_file_path)
{
    cube = {};
    projection = {};

    near = 0.1f;
	far = 1000.0f;
	fov = 90.0f;
	aspect_ratio = (f32)600 / (f32)800;
	fov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.15149f);

    this->renderer = renderer;

    theta = 0.0f;

    translation = vec3_create(0.0f, 0.0f, 0.0f);
    camera = vec3_create(0.0f, 0.0f, 0.0f);

    obj_file = obj_file_path;

    mesh_color = white;
}

void TestApp::init()
{
    // cube.tris = 
    // {
    //     // SOUTH
    //     {0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f},
    //     {0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f},

    //     // EAST
    //     {1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f},
    //     {1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f},

    //     // NORTH                                                     
	// 	{1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f},
	// 	{1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f},

	// 	// WEST                                                      
	// 	{0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f},
	// 	{0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f},

	// 	// TOP                                                       
	// 	{0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f},
	// 	{0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f},

	// 	// BOTTOM                                                    
	// 	{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f},
	// 	{1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f},
    // };

    cube.load_from_obj_file(obj_file);

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
    // std::cout << "Delta: " << delta_time << "\n";
    // std::cout << "Theta: " << theta << "\n";

    // Rotation Z
    // mat_rotz.m[0][0] = cosf(theta);
    // mat_rotz.m[0][1] = sinf(theta);
    // mat_rotz.m[1][0] = -sinf(theta);
    // mat_rotz.m[1][1] = cosf(theta);
    // mat_rotz.m[2][2] = 1;
    // mat_rotz.m[3][3] = 1;
    mat_rotz = mat4_euler_z(theta);

    // // Rotation X
    // mat_rotx.m[0][0] = 1;
    // mat_rotx.m[1][1] = cosf(theta * 0.5f);
    // mat_rotx.m[1][2] = sinf(theta * 0.5f);
    // mat_rotx.m[2][1] = -sinf(theta * 0.5f);
    // mat_rotx.m[2][2] = cosf(theta * 0.5f);
    // mat_rotx.m[3][3] = 1;
    mat_rotx = mat4_euler_x(theta);

    if(input->is_key_down(KEY_W))
        translation.y--;
    if(input->is_key_down(KEY_S))
        translation.y++;
    if(input->is_key_down(KEY_D))
        translation.x++;
    if(input->is_key_down(KEY_A))
        translation.x--;

    std::vector<Triangle> vec_triangles_to_raster; 

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

        // Offset into the screen
        tri_translated = tri_rotated_zx;
        tri_translated.p[0].z = tri_rotated_zx.p[0].z + 8.0f;
        tri_translated.p[1].z = tri_rotated_zx.p[1].z + 8.0f;
        tri_translated.p[2].z = tri_rotated_zx.p[2].z + 8.0f;

        // Adding movement
        tri_translated.p[0].x += translation.x * 2.0f * delta_time;
        tri_translated.p[1].x += translation.x * 2.0f * delta_time;
        tri_translated.p[2].x += translation.x * 2.0f * delta_time;

        tri_translated.p[0].y += translation.y * 2.0f * delta_time;
        tri_translated.p[1].y += translation.y * 2.0f * delta_time;
        tri_translated.p[2].y += translation.y * 2.0f * delta_time;

        Vec3 normal;
        Vec3 line1;
        Vec3 line2;

        line1.x = tri_translated.p[1].x - tri_translated.p[0].x;
        line1.y = tri_translated.p[1].y - tri_translated.p[0].y;
        line1.z = tri_translated.p[1].z - tri_translated.p[0].z;

        line2.x = tri_translated.p[2].x - tri_translated.p[0].x;
        line2.y = tri_translated.p[2].y - tri_translated.p[0].y;
        line2.z = tri_translated.p[2].z - tri_translated.p[0].z;

        normal = vec3_cross_product(line1, line2);
        normal = vec3_normalize(normal);

        // if(normal.z < 0)
        if(vec3_dot_product(normal, vec3_minus(tri_translated.p[0], camera)) < 0.0f)
        {
            Vec3 light_direction = vec3_create(0.0f, 0.0f, -1.0f);
            light_direction = vec3_normalize(light_direction);

            f32 dp = vec3_dot_product(normal, light_direction);
            ul32 original_color = white;
            mesh_color = adjust_brightness(original_color, dp);

            // Project triangles from 3D to 2D
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

            vec_triangles_to_raster.push_back(tri_projected);
        }
    }

    // Sort triangles from back to front
    std::sort(vec_triangles_to_raster.begin(), vec_triangles_to_raster.end(), 
        [](Triangle& t1, Triangle& t2)
        {
            f32 z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			f32 z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
        }
    );

    
    for(auto& tri_projected : vec_triangles_to_raster)
    {
        renderer->fill_triangle(
            tri_projected.p[0].x, tri_projected.p[0].y,
            tri_projected.p[1].x, tri_projected.p[1].y,
            tri_projected.p[2].x, tri_projected.p[2].y,
            mesh_color
        );

        renderer->draw_triangle(
            tri_projected.p[0].x, tri_projected.p[0].y,
            tri_projected.p[1].x, tri_projected.p[1].y,
            tri_projected.p[2].x, tri_projected.p[2].y,
            black
        );
    }
}


void TestApp::draw()
{
    // std::cout << "Drawing...\n";
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