#ifndef RENDERER_X11_H
#define RENDERER_X11_H

#include "defines.h"

#if PLATFORM_LINUX

#include "window_x11.h"

class RendererX11
{
private:
    i16 width;
    i16 height;

    WindowX11* window;

public:
    RendererX11(WindowX11* window);
    ~RendererX11();

    void draw_point(i32 x, i32 y, ul32 color);
    void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, ul32 color);
    void draw_triangle(i32 x0, i32 y0, i32 x1, i32 y1, i32 x2, i32 y2, ul32 color);
};

#endif // PLATFORM_LINUX

#endif // RENDERER_X11_H