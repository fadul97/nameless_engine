#ifndef TEST_APP_H
#define TEST_APP_H

#include "defines.h"

#include "app.h"
#include "engine.h"
#include "mesh.h"

class TestApp : public App
{
private:
	f32 near;
	f32 far;
	f32 fov;
	f32 aspect_ratio;
	f32 fov_rad;

	RendererX11* renderer;

	f32 theta;
	Vec3 translation;

	Mat4 model;
	Vec3 camera;

	ul32 mesh_color;

	char* obj_file;

public:
    TestApp(RendererX11* renderer, char* obj_file_path);

	Mesh cube;
	Mat4 projection;

	void init() override;    
	void update(f32 delta_time) override;
	void draw() override;
	void shutdown() override;
};

#endif // TEST_APP_H